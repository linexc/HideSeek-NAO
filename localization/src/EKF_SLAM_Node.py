#!/usr/bin/env python

from math import *
import numpy as np
import rospy
from apriltag_ros.msg import AprilTagDetectionArray
from geometry_msgs.msg import Pose2D
from rospy.numpy_msg import numpy_msg

from rospy_tutorials.msg import Floats

import matplotlib.pyplot as plt
from matplotlib.patches import Ellipse


class EKFSLAMNode(object):

    # ---------------------------------------------------------------------
    # ---------------------- initialization -------------------------------
    # ---------------------------------------------------------------------

    def __init__(self):
        # Initialize visualization
        self.visualize = True
        self.init_plot = 1
        self.timer = 0
        self.lm_plot = []
        self.lm_plot_cov = []
        self.robot_pos_cov = []

        # initialize subscribers
        self.tags_detected = []
        self.odometry = []
        self.init_subscribers()

        # initialize publishers
        self.publishers = {}
        self.init_publishers()

        # initialize Kalman Angle
        self.KalmanAngle = 0

        # set number of landmarks
        self.n_landmarks = 2

        # initialize state
        self.x = np.zeros(3 + 2 * self.n_landmarks)

        # mapping matrix from low dimensional space to high dimensional space
        self.F = np.zeros((3, 3 + 2 * self.n_landmarks))
        self.F[0:3, 0:3] = np.eye(3)

        # initialize linearized motion model (low dimensional)
        self.G = np.zeros((3, 3))

        # intialize covariance matrix (robot pose: certain, landmark positions: uncertain)
        diag = [0.0] * 3
        for i in range(2 * self.n_landmarks):
            diag.append(10000)

        self.cov = np.diag(diag)

        # landmark ID's
        self.landmark_ID = []

        # process noise (motion_model)
        self.R_motion = np.matmul(self.F.T, np.matmul(np.diag([0.00005, 0.00005, 0.0002]), self.F))

        # measurement noise (single observation)
        self.Q_meas = np.diag([0.001, 0.002])

    def init_subscribers(self):
        self.tags_detected = rospy.Subscriber("~/tag_detections", AprilTagDetectionArray, self.correct)
        # self.odometry = rospy.Subscriber("~/odometry_data", odom, self.predict)
        # self.pitch = rospy.Subscriber("~/pitch_angle", Float64, self.update_pitch)

    def init_publishers(self):
        """ initialize ROS publishers and stores them in a dictionary"""
        # position of segway in world frame
        self.publishers["robot_pose"] = rospy.Publisher("~robot_pose", Pose2D, queue_size=1)
        self.publishers["covariance"] = rospy.Publisher("~covariance", numpy_msg(Floats), queue_size=1)
        self.publishers["state"] = rospy.Publisher("~state", numpy_msg(Floats), queue_size=1)

    def update_pitch(self, msg):
        self.KalmanAngle = msg.data

    # ---------------------------------------------------------------------
    # ---------------------- prediction step-------------------------------
    # ---------------------------------------------------------------------

    def predict(self, odom):
        # callback function of the stepper motors --> Use odometry data as input of the motion model
        # read message
        u = odom

        # integrate system dynamics
        delta = (u[0] + u[1])/2
        yaw_odom = (u[1] - u[0]) / 0.12  # Todo: check wheelbase
        x_p = self.x[0:3] + np.array([cos(self.x[2]) * delta, sin(self.x[2]) * delta, yaw_odom])

        # linearize motion model
        self.G[0, 2] = -sin(self.x[2]) * delta
        self.G[1, 2] = cos(self.x[2]) * delta

        # map linearized motion model to high dimensional space
        lin_motion = np.eye(3 + 2 * self.n_landmarks) + np.matmul(self.F.T, np.matmul(self.G, self.F))

        self.cov = np.matmul(lin_motion, np.matmul(self.cov, lin_motion.T)) + self.R_motion
        self.x[0:3] = x_p

    # ---------------------------------------------------------------------
    # ---------------------- correction step ------------------------------
    # ---------------------------------------------------------------------

    def correct(self, msg):
        # test for proof of concept
        self.predict([0.0003, 0.0003])

        # callback function of the April Tag detection algorithm
        # april tag msg contains header and detections (<-- AprilTagDetectionArray)
        # n_tags_detected = len(msg.detections)
        for i, tag in enumerate(msg.detections):
            # convert landmark to segway frame
            landmark_pos = self.convert_cam_pos_to_segway_pos(tag.pose.pose.pose.position)

            # if landmark never seen before, initialize landmark position with expected position
            if int(tag.id[0]) not in self.landmark_ID:
                self.landmark_ID.append(int(tag.id[0]))
                j = self.landmark_ID.index(int(tag.id[0]))
                self.x[(3 + 2 * j):(3 + 2 * j + 2)] = self.x[0:2] + landmark_pos

            # get landmark index and landmark pose
            j = self.landmark_ID.index(int(tag.id[0]))

            # map position to distance and angle
            z_meas = np.array([sqrt(np.inner(landmark_pos, landmark_pos)), atan2(landmark_pos[1], landmark_pos[0])])

            # use observation model
            z_hat = np.zeros(2)
            delta = np.array([self.x[3 + 2 * j] - self.x[0], self.x[3 + 2 * j + 1] - self.x[1]])
            z_hat[0] = sqrt(np.inner(delta, delta))
            z_hat[1] = atan2(delta[1], delta[0])

            # get H matrix for a single landmark
            H = self.H_single_landmark(j)
            # compute Kalman gain
            K = np.matmul(self.cov, np.matmul(H.T, np.linalg.inv(np.matmul(H, np.matmul(self.cov, H.T)) + self.Q_meas)))
            # correct state
            self.x += K.dot(z_meas - z_hat)
            self.cov = np.matmul(np.eye(3 + 2 * self.n_landmarks) - np.matmul(K, H), self.cov)

        # publish robots pose
        x_pub = Pose2D()
        x_pub.x = self.x[0]
        x_pub.y = self.x[1]
        x_pub.theta = self.x[2]

        if self.visualize and self.timer == 20:
            self.visualize_positions()
            self.timer = 0

        self.timer += 1

        self.publishers["robot_pose"].publish(x_pub)

        # pusblish covariance matrix
        self.publishers["covariance"].publish(self.cov.reshape(np.power(3 + 2*self.n_landmarks, 2)))
        self.publishers["state"].publish(self.x)

    def H_single_landmark(self, j):
        # distance segway obstacle
        delta = np.array([self.x[3 + 2 * j] - self.x[0], self.x[3 + 2 * j + 1] - self.x[1]])

        # mapping matrix from low dimensional to high dimensional space
        F = np.zeros((5, 3 + 2 * self.n_landmarks))
        F[0:3, 0:3] = np.eye(3)
        F[3:5, (3 + 2 * j):(3 + 2 * j + 2)] = np.eye(2)

        # compute jacobian of observation model
        q = np.inner(delta, delta)
        if q == 0:
            q = 1
        # this function is different from the observation function in the robot mapping class
        H = (1/q) * np.array([[-sqrt(q)*delta[0], -sqrt(q)*delta[1], 0, sqrt(q)*delta[0], sqrt(q)*delta[1]],
                              [delta[1], -delta[0], 0, -delta[1], delta[0]]])

        return np.matmul(H, F)

    def convert_cam_pos_to_segway_pos(self, position):
        wheelbase = 0.12
        rot_mat = np.array([[0, -sin(self.KalmanAngle), cos(self.KalmanAngle)],
                            [1, 0, 0],
                            [0, -cos(self.KalmanAngle), -sin(self.KalmanAngle)]])
        cam_pos = np.array([sin(self.KalmanAngle) * wheelbase, 0, cos(self.KalmanAngle) * wheelbase])
        lm_pos_cam = np.array([position.x, position.y, position.z])
        lm_segway = cam_pos + rot_mat.dot(lm_pos_cam)
        return lm_segway[0:2]

    def visualize_positions(self):
        if self.init_plot == 1:
            plt.ion()
            self.ax = plt.figure().add_subplot(111)
            self.pos_robot, = plt.plot(self.x[0], self.x[1], 'ro', markersize=10)
            self.robot_pos_cov = self.draw_covariance_ellipse(self.x[0:2], self.x[2],
                                                              self.cov[0:2, 0:2], self.ax)

            for j in range(self.n_landmarks):
                pos_lm = self.x[(3 + 2 * j):(3 + 2 * j + 2)]
                # plot position of landmarks
                lm, = plt.plot(pos_lm[0], pos_lm[1], 'bo')
                self.lm_plot.append(lm)
                self.lm_plot_cov.append(self.draw_covariance_ellipse(pos_lm, 0, np.zeros((2, 2)), self.ax))

            self.init_plot = 0
            plt.xlim((-1, 1))
            plt.grid(color='gray', linestyle='-', linewidth=1)
            plt.ylim((-1, 1))

        self.pos_robot.set_xdata(self.x[0])
        self.pos_robot.set_ydata(self.x[1])
        try:
            self.robot_pos_cov.remove()
        except ValueError:
            pass
        self.robot_pos_cov = self.draw_covariance_ellipse(self.x[0:2], self.x[2], self.cov[0:2, 0:2], self.ax)

        for jj in range(self.n_landmarks):
            lm_ = self.lm_plot[jj]
            lm_.set_xdata(self.x[3 + 2 * jj])
            lm_.set_ydata(self.x[3 + 2 * jj + 1])
            cov_lm = self.cov[(3 + 2 * jj):(3 + 2 * jj + 2), (3 + 2 * jj):(3 + 2 * jj + 2)]
            try:
                self.lm_plot_cov[jj].remove()
            except ValueError:
                pass
            self.lm_plot_cov[jj] = self.draw_covariance_ellipse(self.x[(3 + 2 * jj):(3 + 2 * jj+2)], 0, cov_lm, self.ax)
        plt.draw()
        plt.pause(0.0000000001)

    def draw_covariance_ellipse(self, pos, yaw, cov, ax):
        lambda1 = (cov[0, 0] + cov[1, 1]) / 2 + sqrt(np.power((cov[0, 0] - cov[1, 1]) / 2, 2) + np.power(cov[0, 1], 2))
        lambda2 = (cov[0, 0] + cov[1, 1]) / 2 - sqrt(np.power((cov[0, 0] - cov[1, 1]) / 2, 2) + np.power(cov[0, 1], 2))
        try:
            elps = Ellipse(pos, 2 * sqrt(lambda1), 2 * sqrt(lambda2), yaw, alpha=0.5, facecolor='pink', edgecolor='black')
            ax.add_patch(elps)
            return elps
        except ValueError:
            pass

def main():
    """Starts the EKF SLAM Node"""
    rospy.init_node("EKF_SLAM_Node")
    EKFSLAMNode()
    rospy.spin()


if __name__ == "__main__":
    main()





