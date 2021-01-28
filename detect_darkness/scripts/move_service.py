#!/usr/bin/env python
import rospy
import time
import motion
import numpy as np
import almath
import sys
from naoqi import ALProxy
from detect_darkness.srv import *
import tf

motionProxy = 0
postureProxy =0 
re = 0

def my_callback(req):
    # Send NAO to Pose Init
    postureProxy.goToPosture("StandInit", 0.5)
    # Deactivate the foot contact protection
    proxy.setMotionConfig([["ENABLE_FOOT_CONTACT_PROTECTION", False]])
    # Example showing the moveTo command
    # The units for this command are meters and radians

    x  = req.x
    y  = req.y
    theta  = req.angle

    for (i=1)
    motionProxy.moveTo(x[0], y, theta)
    # Will block until move Task is finished

    # If moveTo() method does nothing on the robot,
    # read the section about walk protection in the
    # Locomotion control overview page.
def myServerFunction():
    rospy.init_node('move_forward_server')
    rospy.Service("move_forward_server",move_direction, my_callback)
    return re
    rospy.spin()

if __name__ == '__main__':
    
    #robotIP=str(sys.argv[1])
    robotIP="127.0.0.1"
    #PORT=int(sys.argv[2])
    PORT= 9559
    try:
        motionProxy = ALProxy("ALMotion", robotIP, PORT)
        postureProxy = ALProxy("ALRobotPosture", robotIP, PORT)
        proxy= ALProxy("ALMotion", robotIP, PORT)
        myServerFunction()
    except rospy.ROSInternalException:
        pass


