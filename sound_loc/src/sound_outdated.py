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
import tf


direction = 0
found_person = False
hideorseek = ""
polo = ""
correctsound = False
correcgesture = False
gesture = ""
"""
def sound_callback(eventName, value, subscriberIdentifier):
    print(value)
    if len(value) != 0:
        direction = float(value[1][0])
    else:
        print("an error occured with the localization") 
"""
def gesturehandler(some_gesture):
    gesture = some_gesture

def pythondatachanged(eventName, gestureName, value):
    
    #print "datachanged", strVarName, " ", value, " ", strMessage
    #global check
    #check = 1
    print(gestureName)
    gesture = gestureName


#if __name__ == '__main__':
#rospy.init_node('move_joints_server')
robotIP="10.152.246.115"
PORT=int(9559)
memoryProxy = ALProxy("ALMemory", robotIP, PORT)
motionProxy = ALProxy("ALMotion", robotIP, PORT)
postureProxy = ALProxy("ALRobotPosture", robotIP, PORT)
speekingProxy = ALProxy("ALTextToSpeech", robotIP, PORT)
recognitionProxy = ALProxy("ALSpeechRecognition", robotIP, PORT)
localizationProxy = ALProxy("ALSoundLocalization", robotIP, PORT)
#gesture = ALTactileGesture

x = 1
y = 0 

localizationProxy.setParameter("Sensitivity", 0.99)

print(recognitionProxy.getAvailableLanguages())

recognitionProxy.setLanguage("English")
vocabulary = ["yes", "no", "hide", "seek", "marco", "polo", "one", "two"]
#recognitionProxy.setVocabulary(vocabulary, False)


#motionProxy.wakeUp()
#postureProxy.goToPosture("StandInit", 0.5)
memoryProxy.subscribeToEvent("ALTactileGesture/Gesture","pythonModule", "pythondatachanged")
while(correcgesture == False):
    #gesture = memoryProxy.getData("ALTactileGesture/Gesture")
    print(gesture)



"""
speekingProxy.say("Hello, my name is NAO. I want to play a game of hide and seek with you.")

time.sleep(1)

speekingProxy.say("If you want to hide say hide. If you want to seek say seek.")

recognitionProxy.subscribe("GameMode")

while(len(hideorseek) == 0):
    temp = memoryProxy.getData("WordRecognized")
    hideorseek = temp[0]

print(hideorseek)

speekingProxy.say("You chose to" + hideorseek)

recognitionProxy.unsubscribe("GameMode")

if hideorseek == "seek":
    speekingProxy.say("This has to be implemented later")
elif hideorseek == "hide":
    speekingProxy.say("You will have 20 seconds to hide yourself now, when the 20 seconds are over I will inform you. Every time I say marco you have to say polo loud and clearly.")
    time.sleep(1)
    speekingProxy.say("Your time to hide starts now")

    #localizationProxy.subscribe("LookingForPOLO")
    
    #memoryProxy.subscribeToMicroEvent("ALSoundLocalization/SoundLocated", "sound_callback", "source_located")
    
    #recognitionProxy.subscribe("POLO")

    time.sleep(20)
"""
speekingProxy.say("I wil start seeking now")
speekingProxy.say("two")
time.sleep(0.5)
localizationProxy.subscribe("LookingForPOLO")

#memoryProxy.subscribeToMicroEvent("ALSoundLocalization/SoundLocated", "sound_callback")

recognitionProxy.subscribe("POLO")
while(correctsound == False):
    temp = memoryProxy.getData("WordRecognized")
    polo = temp[0]
    print(polo)
    temp2 = memoryProxy.getData("ALSoundLocalization/SoundLocated")
    direction = (temp2[1][0])*180/math.pi
    print(direction)
    if polo == "one":
        correctsound = True
    else:
        direction = 0

polo = ""

#only get angles in front direction otherwise reflection from wall 
#wait for 5 seconds if nothing from front rotate and again

print(polo)
#polo = memoryProxy.getData("WordRecognized")
print(direction)
"""
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

"""
recognitionProxy.unsubscribe("POLO")

#memoryProxy.unsubscribe("ALSoundLocalization/SoundLocated", "sound_callback")

localizationProxy.unsubscribe("LookingForPOLO")

#motionProxy.rest()


   


