#!/usr/bin/env python2
import rospy
import time
#import motion
#import numpy as np
#import almath
import sys
from naoqi import ALProxy
import math
#import argparse
#import tf
import cv2
from std_msgs.msg import String
from darknet_ros_msgs.msg import BoundingBoxes
from std_msgs.msg import Header
from std_msgs.msg import String
from detect_walk.srv import *



should_i_walk = 1

hideseek = ["hide","seek"]

#persons = ["max", "zhouyi"]

found_person = False
hideorseek = ""
hideanseek = False
polo = ""

temp = ["", 0]

starting = False

correctsound = False
direction = 0
"""
def excute(req):
	global should_i_walk
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
    theta = req.angle
    should_i_walk = req.walk
	#to turn the NAO to walking direction and then move forwards
	motionProxy.post.moveTo(0.1,0.1, theta)
	motionProxy.post.moveTo(0.5,0, 0)
	motionProxy.waitUntilMoveIsFinished()
	print("the move is done")
	return command
"""

#put your defined functions here
def callback(data):
   global found_person
   if(found_person != True):
        if(data.bounding_boxes[0].Class=="max"):
            speekingProxy.say("Hi max")
            found_person = True
            print("Hi max")
            return True
        if(data.bounding_boxes[0].Class=="zhouyi"):  
            speekingProxy.say("Hi z") 
            found_person = True 
            print("Hi z")
            return True
        return False
   return False

def box_sub():
  #rospy.init_node('detect', anonymous=True)
  rospy.Subscriber('/darknet_ros/bounding_boxes',BoundingBoxes,callback)
  #rospy.spin()



if __name__ == '__main__':

    

    print("main is called")
    #initialize all desired proxies here

    robotIP="10.152.246.74"
    PORT=int(9559)
    memoryProxy = ALProxy("ALMemory", robotIP, PORT)
    motionProxy = ALProxy("ALMotion", robotIP, PORT)
    postureProxy = ALProxy("ALRobotPosture", robotIP, PORT)
    speekingProxy = ALProxy("ALTextToSpeech", robotIP, PORT)
    recognitionProxy = ALProxy("ALSpeechRecognition", robotIP, PORT)
    localizationProxy = ALProxy("ALSoundLocalization", robotIP, PORT)

    #reset all values that could occur during testing errors
    rospy.init_node('core_program', anonymous=True)

    #memoryProxy.removeData("WordRecognized")
    memoryProxy.insertData("WordRecognized", ["haha", 0])

    motionProxy.rest()
    localizationProxy.setParameter("Sensitivity", 0.3)

    
    #initialize vocabulary if a new word is added or a new robot is used

    #note that recognitionProxy only has to run one time if its changed and then has to be commented 
    #otherwise an error occurs if an error during the program occurs unsubscribe has to be uncommented too

    #recognitionProxy.unsubscribe("START")
    recognitionProxy.setLanguage("English")
    vocabulary = ["yes", "no", "hide", "seek", "marco", "polo", "one", "two", "start", "alpha", "bravo", "abord","hello"]
    recognitionProxy.setVocabulary(vocabulary, False)


    #waiting for the user to say 'start' to start the main functionalitities of the nao 

    speekingProxy.say("I am ready now")

    recognitionProxy.subscribe("START")


    while(starting == False):
        temps = memoryProxy.getData("WordRecognized")
        print(temps)
        if temps[0] == "start":
            starting = True


    starting = False
    temps[0] = "" 

    recognitionProxy.unsubscribe("START")

    motionProxy.wakeUp()
    postureProxy.goToPosture("StandZero", 0.2)


    speekingProxy.say("Hello, my name is NAO. I want to play a game of hide and seek with you.")

    time.sleep(1)

    speekingProxy.say("If you want to hide say hide. If you want to seek say seek.")

    time.sleep(1)

    #nao listens to get the key word for the mode it will switch to

    recognitionProxy.subscribe("GameMode")

    while(hideanseek == False):
        temp = memoryProxy.getData("WordRecognized")
        hideorseek = temp[0]
        if hideorseek in hideseek:
            hideanseek = True
    hideanseek = False

    print(hideorseek)

    speekingProxy.say("You chose to " + hideorseek)

    recognitionProxy.unsubscribe("GameMode")

    # nao hides itself:
    if hideorseek == "seek":
        speekingProxy.say("I will start hiding now")
        while(should_i_walk == 1):
            try:
                print("the nao is active")
                rospy.Service("walkerServer",walkdirection,excute)

            except rospy.ROSInternalException:
                pass
        

    # nao searches for a person
    elif hideorseek == "hide":
        speekingProxy.say("You will have 10 seconds to hide yourself now, when the 10 seconds are over I will inform you. Every time I say marco you have to say polo loud and clearly.")
        time.sleep(1)
        speekingProxy.say("Your time to hide starts now")
        temp[0] = ""

        time.sleep(10)

        speekingProxy.say("I will start seeking now")
        
        print(found_person)
    #starting the searching routine here until a face can be recognized and found_person is set TRUE

        while(found_person == False):
            time.sleep(0.5)
            if found_person == True:
                break

            speekingProxy.say("Marco")
            time.sleep(0.5)



            localizationProxy.subscribe("LookingForPOLO")

            recognitionProxy.subscribe("POLO")
            
            while(correctsound == False):
                
                temp = memoryProxy.getData("WordRecognized")
                polo = temp[0]

                # if nao recognizes keyword 'abord' the nao will reset to the start of the programm
                if polo == "abord" :
                
                    recognitionProxy.unsubscribe("POLO")

                    localizationProxy.unsubscribe("LookingForPOLO")

                    motionProxy.rest()

                    polo = " "
                    
                    rospy.spin()
                
                
                temp1 = memoryProxy.getData("ALSoundLocalization/SoundLocated")
                #print(temp1)

                #print(polo)
            
                #only move if the correct keyword is recognized

                if polo == "polo":
                    correctsound = True
                    temp2 = memoryProxy.getData("ALSoundLocalization/SoundLocated")
		            #print(temp2)
                    #print(temp2[1][0]*180/math.pi)
                    direction = temp2[1][0]
                    
                    postureProxy.goToPosture("StandZero", 0.2)
                    time.sleep(2)
                    
                else:
                    direction = 0
            #print(polo)
            
            polo = " "
            

            print(direction)

            if abs(direction) > math.pi/2:
                direction += math.pi

            #turn into direction of sound and walk 50 cm in that direction

            motionProxy.moveTo(0.1, 0.1, direction)
            
            time.sleep(0.5)
            
            motionProxy.moveTo(0.5, 0, 0)

            direction = 0
            #callfacial recognition here
            time.sleep(2)
            postureProxy.goToPosture("StandZero", 0.2)
            box_sub()
            #print(found_person)
            
            
            
            
            #reset all variables set during the soundrecognition for the next iteration
            correctsound = False

            temp[0] = " "

            #temp2[1][0] = 0

            temp4 = memoryProxy.getData("WordRecognized")
            #print(temp4)


            memoryProxy.insertData("WordRecognized", [" ", 0])

            #memoryProxy.removeData("WordRecognized")


            temp5 = memoryProxy.getData("WordRecognized")
            #print(temp5)

            recognitionProxy.unsubscribe("POLO")

            localizationProxy.unsubscribe("LookingForPOLO")



        #recognitionProxy.unsubscribe("POLO")
        #localizationProxy.unsubscribe("LookingForPOLO")
        
        
        #memoryProxy.unsubscribe("ALSoundLocalization/SoundLocated", "sound_callback")

        motionProxy.rest()


   


