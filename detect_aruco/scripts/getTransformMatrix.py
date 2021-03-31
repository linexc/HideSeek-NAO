## this python file is aiming at geting the transformation matrix according to information of one marker
#the input is translation vector(x,y,z) and rotation vector(R,P,Y) of a marker
#the output is the transform matrix form marker frame to FRAME_ROBOT frame, the shape of matrix is 4*4

import rospy
import tf
import time
import motion
import cv2
import numpy as np
import almath
import sys
from naoqi import ALProxy

import argparse
from geometry_msgs.msg import Twist
from geometry_msgs.msg import Pose2D

from detect_aruco.srv import localization


IP = "10.152.246.74"

def localization_single(req):
    
    translation_opt2marker = np.array([[req.x], [req.y], [req.z]])
    rotationRPY_opt2marker = np.array([[req.R], [req.P], [req.Y]])
    rotationMat_opt2marker = cv2.Rodrigues(rotationRPY_opt2marker)
    
    transform_opt2marker = np.identity(4)
    transform_opt2marker[0:3,0:3] = rotationMat_opt2marker[0]

    for i in range(3):
        transform_opt2marker[i,3] = translation_opt2marker[i]

    transform_marker2opt = np.linalg.inv(transform_opt2marker)
    transform_opt2cam = np.zeros((4,4))
    transform_opt2cam[0,1] = -1
    transform_opt2cam[1,2] = -1
    transform_opt2cam[2,0] = 1
    transform_opt2cam[3,3] = 1
    transform_marker2cam = transform_marker2opt.dot(transform_opt2cam)
 
    result = motionProxy.getTransform('CameraTop', 2, True) #{FRAME_TORSO = 0, FRAME_WORLD = 1, FRAME_ROBOT = 2}.
    print(result)
    result_np = np.arange(16.0) #array([0,1,2,...15])
    for i in range(0, 16):
        result_np[i] =  result[i]
    transform_base2cam = np.reshape(result, (4, 4))
    transform_cam2base = np.linalg.inv(transform_base2cam)
    tansform_marker2base = transform_marker2cam.dot(transform_cam2base)
    
    return tansform_marker2base


def mappingSubscribe():
    rospy.Service("getTrans",localization,localization_single) 

if __name__ == '__main__':
    motionProxy = ALProxy("ALMotion", IP, 9559)
    rospy.init_node('getTrans')
    mappingSubscribe()
    rospy.spin()
