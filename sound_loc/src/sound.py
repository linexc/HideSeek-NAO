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



rospy.init_node('core_program', anonymous=True)


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

#put your defined functions here

if __name__ == '__main__':
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

    memoryProxy.insertData("WordRecognized", ["", 0])

    motionProxy.rest()

    localizationProxy.setParameter("Sensitivity", 0.01)


    #initialize vocabulary if a new word is added or a new robot is used

    #note that recognitionProxy only has to run one time if its changed and then has to be commented 
    #otherwise an error occurs

    recognitionProxy.setLanguage("English")
    vocabulary = ["yes", "no", "hide", "seek", "marco", "polo", "one", "two", "start", "alpha", "bravo", "abord"]
    #recognitionProxy.setVocabulary(vocabulary, False)


    #waiting for the user to say 'start' to start the main functionalitities of the nao 

    recognitionProxy.subscribe("START")

    while(starting == False):
        temps = memoryProxy.getData("WordRecognized")
        #print(temps)
        if temps[0] == "start":
            starting = True
    starting = False
    temps[0] = "" 

    recognitionProxy.unsubscribe("START")

    motionProxy.wakeUp()
    postureProxy.goToPosture("StandInit", 0.5)


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
        speekingProxy.say("This has to be implemented later")



    # nao searches for a person
    elif hideorseek == "hide":
        speekingProxy.say("You will have 10 seconds to hide yourself now, when the 10 seconds are over I will inform you. Every time I say marco you have to say polo loud and clearly.")
        time.sleep(1)
        speekingProxy.say("Your time to hide starts now")
        temp[0] = ""

        time.sleep(10)

        speekingProxy.say("I will start seeking now")
        

    #starting the searching routine here until a face can be recognized and found_person is set TRUE

        while(found_person == False):


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
                
                
                print(polo)
            
                #only move if the correct keyword is recognized

                if polo == "polo":
                    correctsound = True
                    temp2 = memoryProxy.getData("ALSoundLocalization/SoundLocated")
                    #print(temp2[1][0]*180/math.pi)
                    direction = temp2[1][0]
                    
                else:
                    direction = 0
            print(polo)
            
            polo = " "
            

            print(direction)

            #turn into direction of sound and walk 50 cm in that direction

            motionProxy.moveTo(0.1, 0.1, direction)
            motionProxy.moveTo(0.5, 0, 0)


            #callfacial recognition here

            
            
            
            
            
            
            
            #reset all variables set during the soundrecognition for the next iteration
            correctsound == False

            temp[0] = " "

            temp2[1][0] = 0

            memoryProxy.insertData("WordRecognized", [" ", 0])

            memoryProxy.removeData("WordRecognized")

            recognitionProxy.unsubscribe("POLO")

            localizationProxy.unsubscribe("LookingForPOLO")

            

    








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

        #recognitionProxy.unsubscribe("POLO")
        #localizationProxy.unsubscribe("LookingForPOLO")
        
        
        #memoryProxy.unsubscribe("ALSoundLocalization/SoundLocated", "sound_callback")

        motionProxy.rest()


   


