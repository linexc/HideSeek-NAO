#!/usr/bin/env python

# This file is a service server to let NAO walk according to its polar system.
# This server is used in navigation part.

import rospy
import time
import sys
import motion
from naoqi import ALProxy
from std_srvs.srv import *
from detect_aruco.srv import walk_polar

IP = "10.152.246.74"

def StiffnessOn(proxy):
    pNames = "Body"
    pStiffnessLists = 1.0
    pTimeLists = 1.0
    proxy.stiffnessInterpolation (pNames, pStiffnessLists, pTimeLists)

def walk_func(walkX, walkY, walkTheta):
    postureProxy = ALProxy("ALRobotPosture", IP, 9559)
    StiffnessOn(motionProxy)
    print("Begin walking!!!!")
    time.sleep(1.5)
    postureProxy.goToPosture("StandInit", 0.5)
    motionProxy.setMotionConfig([["ENABLE_FOOT_CONTACT_PROTECTION", True]])
    print("Now walking to: ", walkX, walkY, walkTheta)
    motionProxy.post.moveTo(walkX, walkY, walkTheta)

def walk_polar_Callback(req):
    walk_x= req.x
    walk_y = req.y
    walk_theta = req.theta
    walk_func(0.1, 0.1, walk_theta)
    walk_func(math.sqrt(walk_x*walk_x+walk_y*walk_y),0, 0)
    return True

if __name__ == '__main__':
    motionProxy = ALProxy("ALMotion",IP, 9559)   
    rospy.init_node('walk_polar')
    rospy.Service('WalkPolar', walk_polar, walk_polar_Callback)
    rospy.spin()
