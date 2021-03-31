#!/usr/bin/env python

# This file is a service server decide if NAO should move forward and continue to find the dark spot.

import rospy
import time
import motion
import numpy as np
import almath as m
import sys
import math
from naoqi import ALProxy
from detect_walk.srv import srv1
import tf


NAME = 'if_hide'
 
def Changereply(req):
    if req.next_step:
        command = 1
        print("continue to find the darkspot")
    else:
        command =0
        print("start to hide")
    return command; 
 
def rossrv_creat():
    rospy.init_node(NAME)
    rospy.Service('if_hide', srv1, Changereply)
    print("server is waiting!")
 
if __name__ == '__main__':
    print('Brain is waiting')
    try:
        rossrv_creat()
    except rospy.ROSInternalException:
		pass
    rospy.spin()
