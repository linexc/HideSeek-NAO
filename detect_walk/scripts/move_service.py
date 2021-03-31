#!/usr/bin/env python

# This file is a service server to let NAO walk according to its polar system.
# This server is used in detect darkspot

import rospy
import time
import motion
import numpy as np
import almath
import math
import sys
from naoqi import ALProxy
from detect_walk.srv import *
import tf

IP = "10.152.246.74"

def excute(req):
	
	motionProxy = ALProxy("ALMotion", IP, PORT)
	postureProxy = ALProxy("ALRobotPosture", IP, PORT)
	# when walking is done, this command will be feedback.
	command = 1  
	
	pNames = "Body"
	pStiffnessLists = 1.0
	pTimeLists = 1.0
	motionProxy.stiffnessInterpolation(pNames, pStiffnessLists, pTimeLists)
    
	motionProxy.wakeUp()
	time.sleep(1.5)
	postureProxy.goToPosture("StandInit", 0.5)
	motionProxy.setExternalCollisionProtectionEnabled( "All", True )
	motionProxy.setMoveArmsEnabled(True, True)
	motionProxy.setMotionConfig([["ENABLE_FOOT_CONTACT_PROTECTION", True]])
	theta  = req.angle
	#to turn the NAO to walking direction and then move forwards
	motionProxy.post.moveTo(0.1,0.1, theta)
	motionProxy.post.moveTo(0.5,0, 0)
	motionProxy.waitUntilMoveIsFinished()
	print("the move is done")
	return command

if __name__ == '__main__':
	rospy.init_node('walker')

	PORT= 9559
	try:
		print("the nao is active")
		rospy.Service("walkerServer",walkdirection,excute)

	except rospy.ROSInternalException:
		pass

	rospy.spin()


