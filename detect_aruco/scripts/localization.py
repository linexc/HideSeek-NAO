#!/usr/bin/env python

#   Service localization: get the current 2D position(x,y,theta) of NAO in global map
#   This service works as the localization of navigation part for path planning
#   
#   If this service is called, NAO will shake its head to find the Arucomarkers.
#   Arucomarkers with id=1,2,3,4 work for localization. 
#   If NAO see those markers, it will compute the current position in global map and return it.

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

#set the position information as a unreasonable value
naox = 999
naoy = 999
naotheta = 999

flagshake = True #for shaking head
IP = "10.152.246.74"

# the parameters are tvecs and rvecs
def localization_single(x,y,z,R,P,Y):
    
    translation_opt2marker = np.array([[x], [y], [z]])
    rotationRPY_opt2marker = np.array([[R], [P], [Y]])
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
    # the transformation matrix from marker to robot is published.
    return tansform_marker2base

#compute the 2D position of NAO
def naolocalization(data):

    #If NAO stop shake its head, it will get the data of markers and then compute the 2D position
    if (flagshake == True):
        global naox,naoy,naotheta

        for i in range(len(data.id)):  
	    #the marker with id = 1,2,3,4 is used as localization marker
            if data.id[i]<5:
                x = data.geoInfo[i].linear.x 
                y = data.geoInfo[i].linear.y 
                z = data.geoInfo[i].linear.z 
                R = data.geoInfo[i].angular.x
                P = data.geoInfo[i].angular.y 
                Y = data.geoInfo[i].angular.z
		#this function is used for frame transform
                transform_marker2base = np.array([x,y,z,R,P,Y])
                rotation_marker2base = transform_marker2base.reshape(2,3)
                translation_marker2base = np.zeros((3,1))
                for j in range(3):
                    translation_marker2base[j] = transform_marker2base[j,3]
		#because different marker is located in different position in global map, we need to deal with it individually
                if data.id[i] == 1:
                    world_x[i] = translation_marker2base[1]
                    world_y[i] = translation_marker2base[0]
                    rotation_modify = np.array([[0.0,1.0,0.0],[1.0, 0.0, 0.0],[0.0, 0.0, -1.0]])
                elif data.id[i] == 2:
                    world_x[i] = translation_marker2base[1]
                    world_y[i] = translation_marker2base[0]+0.5
                    rotation_modify = np.array([[0.0,1.0,0.0],[1.0, 0.0, 0.0],[0.0, 0.0, -1.0]])
                elif data.id[i] == 3:
                    world_x[i] = translation_marker2base[1]
                    world_y[i] = translation_marker2base[0]+1
                    rotation_modify = np.array([[0.0,1.0,0.0],[1.0, 0.0, 0.0],[0.0, 0.0, -1.0]])
                else:
                    world_x[i] = translation_marker2base[1]+0.6
                    world_y[i] = translation_marker2base[0]
                    rotation_modify = np.array([[0.0,1.0,0.0],[1.0, 0.0, 0.0],[0.0, 0.0, -1.0]])

                rotationMat_theta =  rotation_modify.dot(rotation_marker2base)
		#the sign of theta need to be considered
                if rotationMat_theta[0,1]<=0:
                    world_theta[i] = np.arccos(rotationMat_theta[0,0])
                else:
                    world_theta[i] = -np.arccos(rotationMat_theta[0,0])     
	#if at least one localization marker is detected, we can know the current position of NAO. We add a constant bias here beacuse of inevitable errors
        if local_num>=1:
            naox = np.mean(world_x)
            naoy = np.mean(world_y)
            naotheta = world_theta[0]
            return localizationResponse(X)


def rockhead(req):
    # the flagshake is aiming at looking for different aruco markers in the map. 
    global flagshake

    #shake the head to search for localization and obstacle marker
    isEnabled  = True
    motionProxy.wbEnable(isEnabled) #Enables Whole Body Balancer
    
    #set the flagshake as false to stop getting data and computing, because the motion of head will influence the accurancy of data
    flagshake = False
    names      = "HeadYaw"
    angleLists = [-30.0]
    timeLists  = [3.0]
    isAbsolute = True
    angleLists = [angle*almath.TO_RAD for angle in angleLists]
    motionProxy.angleInterpolation(names, angleLists, timeLists, isAbsolute)
    time.sleep(1)
    #set the flagshake as true to start getting information and computing
    flagshake = True
    time.sleep(1)

    flagshake = False
    names      = "HeadPitch"
    angleLists = [10.0]
    timeLists  = [6.0]
    isAbsolute = True
    angleLists = [angle*almath.TO_RAD for angle in angleLists]
    motionProxy.angleInterpolation(names, angleLists, timeLists, isAbsolute)
    time.sleep(1)
    flagshake = True
    time.sleep(1)

    flagshake = False
    names      = "HeadYaw"
    angleLists = [0.0]
    timeLists  = [3.0]
    isAbsolute = True
    angleLists = [angle*almath.TO_RAD for angle in angleLists]
    motionProxy.angleInterpolation(names, angleLists, timeLists, isAbsolute)
    time.sleep(1)
    flagshake = True
    time.sleep(1)

    flagshake = False
    names      = "HeadYaw"
    angleLists = [30.0]
    timeLists  = [3.0]
    isAbsolute = True
    angleLists = [angle*almath.TO_RAD for angle in angleLists]
    motionProxy.angleInterpolation(names, angleLists, timeLists, isAbsolute)
    time.sleep(1)
    flagshake = True
    time.sleep(1)

    flagshake = False
    names      = "HeadPitch"
    angleLists = [-20.0]
    timeLists  = [6.0]
    isAbsolute = True
    angleLists = [angle*almath.TO_RAD for angle in angleLists]
    motionProxy.angleInterpolation(names, angleLists, timeLists, isAbsolute)
    time.sleep(1)
    flagshake = True
    time.sleep(1)

    flagshake = False
    names      = "HeadYaw"
    angleLists = [0.0]
    timeLists  = [3.0]
    isAbsolute = True
    angleLists = [angle*almath.TO_RAD for angle in angleLists]
    motionProxy.angleInterpolation(names, angleLists, timeLists, isAbsolute)
    time.sleep(1)
    flagshake = True
    time.sleep(1)
    flagshake = False
    isEnabled  = False
    motionProxy.wbEnable(isEnabled)
    
    return [naox,naoy,naotheta] # return the current location 

def mappingSubscribe():
    rospy.Service("localization",localization,naolocalization) 

if __name__ == '__main__':
    motionProxy = ALProxy("ALMotion", IP, 9559)
    rospy.init_node('newlocalization')
    mappingSubscribe()
    rospy.spin()
			
		
