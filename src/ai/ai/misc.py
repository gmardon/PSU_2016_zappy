#!/usr/bin
#coding: utf-8   

import socket
import re
import getopt, sys
import random
import time
import threading
import subprocess
from action import *
from ia import *
from misc import *
from scavenge import *
from threading import Condition, Thread, Lock

def     _layInventory():
    return (1);

def     _incant():
    return (1);

def     _printInventory():
    i = 0;
    while (i < 7):
        i +=1;

def     _updateVision():
    i = 0;
    ret = _look().split(",");
    ret[0] = ret[0][1:];
    while (i < 3):
        board[i] = ret[i].split(" ");
        if (i == 3):
            board[i] = board[i][0];
        i += 1;
    return (1);

def     _checkBuff():
    while (moveBuff[-1:]):
        char = str(moveBuff[-1:])
        if (char[2] == "F"):
            _forward();
        elif (char[2] == "R"):
            _right();
        elif (char[2] == "L"):
            _left();
        moveBuff.pop();
    else:
        return (-1);

def     _printMap():
    i = 0;
    while (i < 3):
        if (i == 2):
            print(board[i][0]);
        else:
            print board[i];
        i +=1;
    return (0);

def     _updateInventory():
    global inventory;
    i = 0;
    l = [];
    while (len(l) != 7):
        invent = _inventory().split(']')[0];
        l = invent.split(',');
        l[0] = l[0][1:]


    while (i < 7):
        inventory[i] = l[i].split(' ')[2];
        i += 1;
    return (inventory);

def     _checkLvlUp():
    i = 0;
    while (i < 7):
        if (int(inventory[i]) != int(lvlUpPatterns[lvl -1][i])):
            return (False);
        i+=1;
    return (True);

def     _gatherDrones():
    _broadcast(teamname + " LVL " + str(lvl) + " RDY");
    return (1);

def     _display_help():

    print ("USAGE: ./zappy_ai -p port -n name -h machine \n\tport is the port number")
    print ("\tname\t is the name of the team\n\tmachine\t is the name of the machine; localhost by default\n");
    sys.exit(-1);


