import numpy as np

class EKF(object):

    def __init__(self, Q, R, motion_model, observation_model, G, H, x0, init_cov):
        # process and measurement noise
        self.Q = Q
        self.R = R

        # motion model
        self.motion = motion_model

        # jacobian of the motion model
        self.G = G

        # observation model
        self.observation = observation_model

        # jacobian of the observation model
        self.H = H

        # intial state
        self.x = x0

        # initial covariance
        self.cov = init_cov

    def predict(self, u):

        # predict using the motion model
        self.x = self.motion(self.x, u)

        # update covariance
        self.cov = np.matmul(self.G(self.x, u), np.matmul(self.cov, self.G(self.x, u).T)) + self.R

    def correct(self, z):

        # compute Kalman gain
        K = np.matmul(np.matmul(self.cov, self.H(self.x).T), np.linalg.inv(np.matmul(self.H(self.x), np.matmul(self.cov, self.H(self.x).T)) + self.Q))

        # corrected mean
        self.x = self.x + np.matmul(K, z - self.observation(self.x))

        # update covariance
        self.cov = np.matmul(np.eye(self.cov.shape[0]) - np.matmul(K, self.H(self.x)), self.cov)
