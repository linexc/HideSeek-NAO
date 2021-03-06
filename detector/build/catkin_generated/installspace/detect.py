#!/usr/bin/env python2
from __future__ import print_function

import sys
import rospy
import cv2
from std_msgs.msg import String
from darknet_ros_msgs.msg import *
from naoqi import ALProxy

class detect:
  def __init__(self):   	
    self.box_sub = rospy.Subscriber("/darknet_ros/bounding_boxes",BoundingBoxes,self.callback)
    print("hi")

  def callback(self,data):
     # if(data.bounding_boxes.Class=="zhouyi"):
     ROS_INFO_STREAM("hi")
     tts.say("Hi")       

def main(args):
  tts = ALProxy("ALTextToSpeech", "10.152.246.115", 9559)
  ic = detect()
  rospy.init_node('detect', anonymous=True)
  try:
    rospy.spin()
  except KeyboardInterrupt:
    print("Shutting down")
  cv2.destroyAllWindows()

if __name__ == '__main__':
    main(sys.argv)
