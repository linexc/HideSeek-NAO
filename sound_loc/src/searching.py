#!/usr/bin/env python
import rospy
import time
import motion
import numpy as np
import almath
import sys
from naoqi import ALProxy
import math
import argparse

global direction = 0


def sound_callback(eventName, value, subscriberIdentifier):
    print(value)
    if len(value) not 0:
        direction = float(value[1][0])
    else:
        print("an error occured with the localization") 

import tf

global found_person = False


if __name__ == '__main__':
    rospy.init_node('move_joints_server')
    robotIP=str(sys.argv[1])
    PORT=int(sys.argv[2])
    memoryProxy = ALProxy("ALMemory", robotIP, PORT)
    motionProxy = ALProxy("ALMotion", robotIP, PORT)
    postureProxy = ALProxy("ALRobotPosture", robotIP, PORT)
    speekingProxy = ALProxy("ALTextToSpeech", robotIP, PORT)
    recognitionProxy = ALProxy("ALSpeechRecognition", robotIP, PORT)
    localizationProxy = ALProxy("ALSoundLocalization", robotIP, PORT)

    x = 1
    y = 0 

    localizationProxy.setParameter("Sensitivity", 0.8)

    recognitionProxy.setLanguage("English")
    vocabulary = ["yes", "no", "hide", "seek", "marco", "polo"]
    recognitionProxy.setVocabulary(vocabulary, False)
    
    
    motionProxy.wakeUp()
    postureProxy.goToPosture("StandInit", 0.5)


   
    
    speekingProxy.say("Hello, my name is NAO. I want to play a game of hide and seek with you.")
    
    time.sleep(1)
    recognitionProxy.subscribe("GameMode")

    speekingProxy.say("If you want to hide say hide. If you want to seek say seek.")

    hideorseek = memoryProxy.getData("WordRecognized")

    speekingProxy.say("You chose to" + hideorseek)

    recognitionProxy.unsubscribe("GameMode")

    if hideorseek == "seek":
        speekingProxy.say("This has to be implemented later")
    elif hideorseek == "hide":
        speekingProxy.say("You will have 20 seconds to hide yourself now, when the 20 seconds are over I will inform you. Every time I say marco you have to say polo loud and clearly.")
        time.sleep(1)
        speekingProxy.say("Your time to hide starts now")

        localizationProxy.subscribe("LookingForPOLO")
        memoryProxy.subscribeToMicroEvent("ALSoundLocalization/SoundLocated", "sound_callback", "source_located")
        recognitionProxy.subscribe("POLO")

        time.sleep(20)

        speekingProxy.say("I wil start seeking now")
        speekingProxy.say("Marco")
        
        polo = memoryProxy.getData("WordRecognized")
        print(direction)

        if direction not 0 & polo == "polo":
            motionProxy.moveTo(x, y, direction)
        else:
            motionProxy.moveTo(0, 0, math.pi/2)
            speekingProxy.say("Marco")
        
            polo = memoryProxy.getData("WordRecognized")
            print(direction)
            if direction not 0 & polo == "polo":
                motionProxy.moveTo(x, y, direction)
            else:
                motionProxy.moveTo(0, 0, math.pi/2)
                speekingProxy.say("Marco")
            
                polo = memoryProxy.getData("WordRecognized")
                print(direction)
                if direction not 0 & polo == "polo":
                    motionProxy.moveTo(x, y, direction)
                else:
                    motionProxy.moveTo(0, 0, math.pi/2)
                    speekingProxy.say("Marco")
                
                    polo = memoryProxy.getData("WordRecognized")
                    print(direction)
                    if direction not 0 & polo == "polo":
                        motionProxy.moveTo(x, y, direction)
                    else: 
                        speekingProxy.say("Are you still there ?")


        recognitionProxy.unsubscribe("POLO")

        memoryProxy.unsubscribe("ALSoundLocalization/SoundLocated", "sound_callback")

        localizationProxy.unsubscribe("LookingForPOLO")

        motionProxy.rest()


   


