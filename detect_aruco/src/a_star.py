#!/usr/bin/env python


##This python file is for navigation either during the detect darkness or leaving out of the room 
## A* planner is implemented. 

import rospy
import tf
import time
import motion
import cv2
import numpy as np
import almath
import sys
from naoqi import ALProxy
from detect_aruco.msg import *
from detect_aruco.srv import *
import argparse
from geometry_msgs.msg import Twist
from geometry_msgs.msg import Pose2D

flagforDarkspot = 0  # navi for detecting darkspot
flagForAruco  = 0  # navi for leaving the room 

n = 30 #size of the map  
m = 30
# x axle from top to down
# y axle from left to right
maze = [[0] * m for i in range(n)] # 30*30 map 

class Node():
    """A node class for A* Pathfinding"""

    def __init__(self, parent=None, position=None):
        self.parent = parent
        self.position = position

        self.g = 0
        self.h = 0
        self.f = 0

    def __eq__(self, other):
        return self.position == other.position

def astar(maze, start, end):
    """Returns a list of tuples as a path from the given start to the given end in the given maze"""

    # Create start and end node
    start_node = Node(None, start)
    start_node.g = start_node.h = start_node.f = 0

    end_node = Node(None, end)
    end_node.g = end_node.h = end_node.f = 0

    # Initialize both open and closed list
    open_list = []
    closed_list = []

    # Add the start node
    open_list.append(start_node)

    # Loop until you find the end
    while len(open_list) > 0:

        # Get the current node
        current_node = open_list[0]
        current_index = 0
        for index, item in enumerate(open_list):
            if item.f < current_node.f:
                current_node = item
                current_index = index

        # Pop current off open list, add to closed list
        open_list.pop(current_index)
        closed_list.append(current_node)

        # Found the goal
        if current_node == end_node:
            path = []
            current = current_node
            while current is not None:
                path.append(current.position)
                current = current.parent
            return path[::-1] # Return reversed path

        # Generate children
        children = []
        for new_position in [(0, -1), (0, 1), (-1, 0), (1, 0), (-1, -1), (-1, 1), (1, -1), (1, 1)]: # Adjacent squares

            # Get node position
            node_position = (current_node.position[0] + new_position[0], current_node.position[1] + new_position[1])

            # Make sure within range
            if node_position[0] > (len(maze) - 1) or node_position[0] < 0 or node_position[1] > (len(maze[len(maze)-1]) -1) or node_position[1] < 0:
                continue

            # Make sure walkable terrain
            if maze[node_position[0]][node_position[1]] != 0:
                continue

            # Create new node
            new_node = Node(current_node, node_position)

            # Append
            children.append(new_node)

        # Loop through children
        for child in children:

            # Child is on the closed list
            for closed_child in closed_list:
                if child == closed_child:
                    continue

            # Create the f, g, and h values
            child.g = current_node.g + 1
            child.h = ((child.position[0] - end_node.position[0]) ** 2) + ((child.position[1] - end_node.position[1]) ** 2)
            child.f = child.g + child.h

            # Child is already in the open list
            for open_node in open_list:
                if child == open_node and child.g > open_node.g:
                    continue

            # Add the child to the open list
            open_list.append(child)


def setAruco(data):
    for(i in range(data):
        if(data.id[i]==5 or data.id[i]==6):
            x= -data.x[i]
            y = -data.y[i]
            maze[x][y]= 1


def getDestination():
    print("the door is fixed")

def getRobotPosition(data):
    global start = maze[data.x][data.y]
    global angle = data.theta

# call walk_polar sever to move the robot.
def myClientFunction(x,y,theta)
    rospy.wait_for_service("walk_polar") # the server is walk general in detect_walk
    try:
        feedback = rospy.ServiceProxy("WalkPolar",walk_polar)
        return feeback(x,y,theta)
    except rospy.ServiceException, e:
        print("call walkpolar failed")


if __name__ == '__main__':
    # get nao's postion  as start on map
    rospy.Subscriber("naolocation",naolocation,getRobotPosition)
    print(start) 
   
    # get aruco's info for comfirming the obstacles' postion
    rospy.Subscriber("detectedmarker",arucomsgs,setAruco)

    # the door is fixed at the room 
    end = maze[15][15] 
    print(end) 

    

    
    path = astar(maze, start, end)
    print(maze)
    print(path) 

    # updating the robot's angle for each step 
    for (i in len(path)):
        angle= math.atan2(path[i][1],path[i][0]) - angle
        x = path[i][0] - start[0]
        y = path[i][1] - start[1]
        start[0] =  path[i][0]
        start[1] = path[i][1]
        response = myClientFunction(x,y,angle)


        

