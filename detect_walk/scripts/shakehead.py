#!/usr/bin/env python
#import roslib

import math
import time
import rospy
from naoqi import ALProxy
from std_msgs.msg import Bool
import cv2
import sys
import numpy as np
#from cv_bridge import CvBridge, CvBridgeError
import imutils


# class scan_node():
#     def __init__(self, num):
#         self.init_subscribers()
#         self.init_publishers()
#         self.PORT = 9559
#         self.robotIP = "10.152.246.74"
#         self.bridge = CvBridge()
#         self.alpha = 0
#         self.image_sub = rospy.Subscriber("nao_robot/camera/top/camera/image_raw", Image, self.callback(num))

#     def init_subscribers(self):
#          pass

#     def init_publishers(self):
#         pass

#     #Taking Picture for analyzation
#     def callback(self, data):
#         try:
#             cv_image = self.bridge.imgmsg_to_cv2(data, "bgr8")
#         except CvBridgeError as e:
#             print(e)

#         cv2.imshow("Top camera", cv_image)
#         cv2.waitKey(1)

#         graypic = cv2.cvtColor(cv_image, cv2.COLOR_BGR2GRAY)
#         cv2.imshow("Gray", graypic)
#         cv2.waitKey(1)


#         blurred = cv2.GaussianBlur(graypic, (5, 5), 0)
#         cv2.imshow("Blurr", blurred)
#         cv2.waitKey(1)


#         #Threshold binary_inverse for contour detection of white blurbs
#         MaxVal = 255
#         thresh = 60
#         darkspots = cv2.threshold(blurred, thresh, MaxVal, 1)
#         cv2.imshow("blackwhite", darkspots)
#         cv2.waitKey(1)


#         contours = cv2.findContour(darkspots, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
#         cnts = imutils.grab_contours(contours)


#         #computes the center of the biggest contour
#         c = max(contours, key = cv2.contourArea)
#         M = cv2.moments(c)
#         cX = int(M["m10"] / M["m00"])
#         cY = int(M["m01"] / M["m00"])

#         y = sqrt(1-(cX)^2)
#         self.alpha = mpmath.cot(cX/y)


#         # saves the Picture as "Analysis" in the working folder
#         #pic_name = "Analysis" + str(num)
#         #cv2.imwrite(pic_name, darkspots)

#     #move in direction of darkest point
#     def move(self):

#         x = 0.5
#         y = 0
#         theta = self.alpha * math.pi/180
#         motionProxy.moveTo(x, y, theta)

#         motionProxy.rest()

#     #headmovement
#     def turnleft(self):
#         print("Calling ALProxy ... ")
#         motionProxy = ALProxy("ALMotion", self.robotIP, self.PORT)
#         postureProxy = ALProxy("ALRobotPosture", self.robotIP, self.PORT)

#         print("Wake up robot")
#         # Wake up robot
#         motionProxy.wakeUp()

#         print("Go to posture")
#         # Send robot to Stand Init
#         postureProxy.goToPosture("StandInit", 0.5)

#         #Head turn left
#         names = ["HeadYaw"]
#         angleLists_L = [0.0, 60.97 * math.pi / 180.0]
#         timeLists = [1.0, 5.0]
#         isAbsolute = True

#         try:
#             motionProxy.angleInterpolation(names, angleLists_L, timeLists, isAbsolute)

#         except Exception as errorMsg:
#             print(errorMsg)
#             print("This example is not allowed on this robot")
#             exit()

#         print("Take Pic")

#     def turnright(self):
#         print("Calling ALProxy ... ")
#         motionProxy = ALProxy("ALMotion", self.robotIP, self.PORT)

#         # Head turn right
#         names = ["HeadYaw"]
#         angleLists_R = [0.0, -60.97 * math.pi / 180.0]
#         timeLists = [1.0, 5.0]
#         isAbsolute = True

#         try:
#             motionProxy.angleInterpolation(names, angleLists_R, timeLists, isAbsolute)

#         except Exception as errorMsg:
#             print(errorMsg)
#             print("This example is not allowed on this robot")
#             exit()

#         print("Take Pic")

#     def turnforward(self):
#         print("Calling ALProxy ... ")
#         motionProxy = ALProxy("ALMotion", self.robotIP, self.PORT)

#         # Head look forward
#         names = ["HeadYaw"]
#         angleLists_F = [0.0, 60.97 * math.pi / 180.0]
#         timeLists = [1.0, 5.0]
#         isAbsolute = True

#         try:
#             motionProxy.angleInterpolation(names, angleLists_F, timeLists, isAbsolute)

#         except Exception as errorMsg:
#             print(errorMsg)
#             print("This example is not allowed on this robot")
#             exit()

#         print("Take Pic")

# if __name__ == "__main__":
#     #iterations = 0
#     try:
#         rospy.init_node("scan")
#         print("init node")
#         #scan = scan_node()
#         #scan.move()
#         '''
#         print("Calling function")
#         if iterations == 0:
#             scan.turnleft()
#         elif iterations == 1:
#             scan.turnright()
#         elif iterations == 2:
#             scan.turnforward()
        
#         iterations += 1
        
#         if iterations < 4:
#             rospy.spin()
#         '''
#         print("done")
#         rospy.spin()
#     except rospy.ROSInternalException:
#         pass

# def handle_Movejoints(req):
#     self.bridge = CvBridge()
#     self.image_sub = rospy.Subscriber("nao_robot/camera/top/camera/image_raw", Image, self.callback)

#     isEnabled  = True
#     motionProxy.wbEnable(isEnabled) # Activate Whole Body Balancer.
    
#     names      = "HeadYaw"
#     angleLists = [-45.0]
#     timeLists  = [12.0]
#     isAbsolute = True
#     angleLists = [angle*almath.TO_RAD for angle in angleLists]
#     motionProxy.angleInterpolation(names, angleLists, timeLists, isAbsolute)
    

#     names      = "HeadYaw"
#     angleLists = [0.0]
#     timeLists  = [12.0]
#     isAbsolute = True
#     angleLists = [angle*almath.TO_RAD for angle in angleLists]
#     motionProxy.angleInterpolation(names, angleLists, timeLists, isAbsolute)
    
#     names      = "HeadYaw"
#     angleLists = [45.0]
#     timeLists  = [12.0]
#     isAbsolute = True
#     angleLists = [angle*almath.TO_RAD for angle in angleLists]
#     motionProxy.angleInterpolation(names, angleLists, timeLists, isAbsolute)


#     names      = "HeadYaw"
#     angleLists = [0.0]
#     timeLists  = [12.0]
#     isAbsolute = True
#     angleLists = [angle*almath.TO_RAD for angle in angleLists]
#     motionProxy.angleInterpolation(names, angleLists, timeLists, isAbsolute)

#     isEnabled  = False
#     motionProxy.wbEnable(isEnabled)

#     return EmptyResponse()


# def Movejoints_server():
#     s = rospy.Service('Shakehead', Empty, handle_Movejoints)

# if __name__ == '__main__':

     motionProxy = ALProxy("ALMotion", IP, 9559)   
     rospy.init_node('shakehead')
#     Movejoints_server()

     rospy.spin()
