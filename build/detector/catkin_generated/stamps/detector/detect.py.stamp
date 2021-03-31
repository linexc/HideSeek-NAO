#!/usr/bin/env python
from __future__ import print_function

import sys
import rospy
import cv2
from std_msgs.msg import String
from darknet_ros_msgs.msg import BoundingBoxes
from std_msgs.msg import Header
from std_msgs.msg import String
from naoqi import ALProxy

def callback(data):
   global first_detect
   if(first_detect != True):
      if(data.bounding_boxes[0].Class=="max"):
        tts.say("Hi max")
        first_detect = True
      if(data.bounding_boxes[0].Class=="zhouyi"):  
        tts.say("Hi z")
        first_detect = True    

def box_sub():
  rospy.init_node('detect', anonymous=True)
  rospy.Subscriber('/darknet_ros/bounding_boxes',BoundingBoxes,callback)
  rospy.spin()

if __name__ == '__main__':
  tts = ALProxy("ALTextToSpeech", "10.152.246.74", 9559)
  first_detect = False
  try:
    box_sub()
  except rospy.ROSInterruptException:
    pass
