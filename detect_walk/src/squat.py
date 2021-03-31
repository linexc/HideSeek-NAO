#!/usr/bin/env python
# -*- encoding: UTF-8 -*-

#''' Whole Body Motion: Enable Balance Constraint '''
#''' This example is only compatible with NAO '''

#import argparse
import math
import time
import rospy
from naoqi import ALProxy
from std_msgs.msg import Bool
from detect_walk.msg import *  
IP = "10.152.246.74"

flag = True

class squat_node():
    def __init__(self):
        self.init_subscribers()
        self.init_publishers()
        self.PORT = 9559
        self.robotIP = IP
        
    ''' Example of a whole body Enable Balance Constraint
        Warning: Needs a PoseInit before executing
                 Whole body balancer must be inactivated at the end of the script
    '''
    

    def init_subscribers(self):
        # self.run_main = rospy.Subscriber("~/darkest_spot", Bool, self.control_posture)
        pass

    def init_publishers(self):
        pass

    def control_posture(self):
        print("Calling ALProxy ... ")
        motionProxy  = ALProxy("ALMotion", self.robotIP, self.PORT)
        postureProxy = ALProxy("ALRobotPosture", self.robotIP, self.PORT)

        print("Wake up robot")
        motionProxy.wakeUp()

        print("Go to posture")
        postureProxy.goToPosture("StandInit", 0.5)

        # Activate Whole Body Balancer
        isEnabled  = True
        motionProxy.wbEnable(isEnabled)

        # Constrain feet (=legs) in a plane
        stateName  = "Fixed"
        supportLeg = "Legs"
        motionProxy.wbFootState(stateName, supportLeg)

        # Constraint Balance Motion
        isEnable   = True
        supportLeg = "Legs"
        motionProxy.wbEnableBalanceConstraint(isEnable, supportLeg)

	#To make it more clear the jointnames, -angles etc were seperated. This makes it also easier to adjust them.

        # Legs angleInterpolation
        # Without Whole Body balancer, foot will fall down
        Legs_names      = ["LKneePitch", "RKneePitch", "LHipPitch", "RHipPitch", "LAnklePitch", "RAnklePitch"]
        Legs_angleLists = [ [0.0, 90.0*math.pi/180.0], [0.0, 90.0*math.pi/180.0], [0.0, -75.0*math.pi/180.0], [0.0, -75.0*math.pi/180.0], [0.0, -30.0*math.pi/180.0], [0.0, -30.0*math.pi/180.0]]
        Legs_timeLists  = [ [5.0, 16.0], [5.0, 16.0], [5.0, 13.0], [5.0, 13.0], [5.0, 13.0], [5.0, 13.0], [5.0, 10.0], [5.0, 10.0]]
        

        #Left Arm angleINterpolation and HeadPitch
        LArm_names      = ["LShoulderPitch", "LShoulderRoll", "LElbowYaw", "LElbowRoll", "LWristYaw", "HeadPitch"]
        LArm_angleLists = [ [0.0, 26.0*math.pi/180.0], [10*math.pi/180.0, -17.0*math.pi/180.0], [-10*math.pi/180.0, -61.0*math.pi/180.0], [-10*math.pi/180.0, -85.0*math.pi/180.0], [-10*math.pi/180.0, -75.0*math.pi/180.0], [0*math.pi/180.0, 25.0*math.pi/180.0]]
        LArm_timeLists  = [ [5.0, 10.0], [5.0, 10.0], [5.0, 10.0], [5.0, 10.0], [5.0, 10.0], [2.0, 7.0]]
        
        #Right Arm angleInterpolation
        RArm_names      = ["RShoulderPitch", "RShoulderRoll", "RElbowYaw", "RElbowRoll", "RWristYaw"]
        RArm_angleLists = [ [0.0, 26.0*math.pi/180.0], [10*math.pi/180.0, -17.0*math.pi/180.0], [-10*math.pi/180.0, -61.0*math.pi/180.0], [-10*math.pi/180.0, -85.0*math.pi/180.0], [-10*math.pi/180.0, -75.0*math.pi/180.0], [0*math.pi/180.0, 25.0*math.pi/180.0]]
        RArm_timeLists  = [ [5.0, 10.0], [5.0, 10.0], [5.0, 10.0], [5.0, 10.0], [5.0, 10.0]]
        
        names           = Legs_names + LArm_names + RArm_names
        angleLists      = Legs_angleLists + LArm_angleLists + RArm_angleLists
        timeLists       = Legs_timeLists + LArm_timeLists + RArm_timeLists
        isAbsolute      = True
        time.sleep(5)
        
        try:
           # motionProxy.openHand ("LHand")
            #motionProxy.openHand ("RHand")
            motionProxy.angleInterpolation(names, angleLists, timeLists, isAbsolute)
        
        except Exception as errorMsg:
            print (errorMsg)
            print ("This example is not allowed on this robot")
            exit()

        # Deactivate Whole Body Balancer
        isEnabled   = False
        motionProxy.wbEnable(isEnabled)
        print("hold position")
        time.sleep(5)

        # Go to rest position
        #motionProxy.rest()
        print ("fertig")
        flag = False

def initCallback(data):
    if(data.if_squat):
        time.sleep(5)
        squat = squat_node()
        print("Calling function")
        squat.control_posture()

if __name__ == "__main__":

    try:
        rospy.init_node("squat")
        print("init node")
        rospy.Subscriber('/squat',squatandhide,initCallback)
        rospy.spin()

       
    except rospy.ROSInternalException:
        pass
