#!/usr/bin/env
#coding: utf-8

import socket
import re
import getopt, sys
import random
import time
import threading
import subprocess
from action import *
from connection import *
from misc import *
from scavenge import *
from threading import Condition, Thread, Lock

sys.stderr = open("zappy.log", "w")

condition = Condition();


host = -1
port = -1
teamname = "NONE";

buff_size = 9999
buff = bytearray(buff_size)
IOBuff = bytearray(buff_size)
IOStr = []

yMax = -1
xMax = -1
lvl = 2
food = 3

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

backtrack = []
board = [[], [], [], []]
vision = []
moveBuff = [];
stone = "";
found = False;
inventory = [0, 0, 0, 0, 0, 0, 0]

LINEMATE = 1
DERAUMERE = 2
SIBURE = 3
MENDIANE = 4
PHIRAS = 5
THYSTAME = 6

lvlUp = False;


lvlUpPatterns = [
    [1, 0, 0, 0, 0, 0, 0],
    [2, 1, 1, 1, 0, 0, 0],
    [2, 2, 0, 1, 0, 2, 0],
    [4, 1 ,1, 2, 0, 1, 0],
    [4, 1, 2, 1, 3, 0, 0],
    [6, 1, 2, 3, 0, 1, 0],
    [6, 2, 2, 2, 2, 2, 1]
]

alive = True
# Food
# nb plyr, line, derau, sib, mendia, phiras, thystame

# 0          1       2    3       4       5         6
# index -> lvl du drone

lock = Lock();
condition = Condition();

class   threadIO(threading.Thread):
    
    
    def __init__(self):
        threading.Thread.__init__(self);
        self.lock = threading.Lock();
        self.term = sys.stdout;
        
    def     run(self):
        global queue;
        global alive;
        alive = True;

#        self.term.write("[+]IOThread now running\n");
#       print "ok\n"
        while (alive == True):

            ret = s.recv_into(IOBuff, buff_size);
#            print (str(IOBuff));
        #     if (ret < 0):
        #         print "Error";
        #         break;
            IOStr = str(IOBuff);
        #     if (IOStr == "DEADBEEF"):
        #         alive = False;
 #           self.term.write("[+] Rcvd : [" + IOStr + "]\n");

def     _ia():
    global found;
    global inventory
    global lvlUp;

#    IO = threadIO();
#    IO.start();
    while (True):
        move = random.randint(1, 5);
        if (moveBuff):
            if (moveBuff[-1:]):
                _checkBuff();
        _updateVision();
        found = False;
        if (int(_updateInventory()[0]) < 3):
            print ("[*] Food level critically low [" + str(food) + "] !");
            _scavengeFood();
        if (lvlUp == True):
            print ("[*] Gathering other drones !");
            _gatherDrones();
        elif ( _checkInventory() != 0):
            _scavengeStones();
        else:
            _layInventory();
            _incant();

if (len(sys.argv) != 7):
    _display_help();
    sys.exit(0);

opt, rem = getopt.getopt(sys.argv[1:], 'n:p:h:')
for opt, arg in opt :
    if opt in ("-n"):
        teamname = arg;
    elif opt in ("-p"):
        port = int(arg);
    elif opt in ("-h"):
        host = arg;
_connect_routine();
_ia();
sys.exit(0);

## DBG
_updateInventory();
_updateVision();
_scavengeFood();
_checkInventory();
