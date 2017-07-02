#!/usr/bin
#coding: utf-8

import socket
import re
import getopt, sys
import random
import time
import threading
import subprocess
import action.py
import connection.py
import misc.py
import ia.py
from threading import Condition, Thread, Lock

def     _scavengeFood():
    i = 0;
    while (i < 3):
        if any ("food" in s for s in board[i]):
            if (_take("food") != "NULL"):
                found = True;
        i += 1;
    return (1);

def     _scavengeStones():
    i = 0;
    global stone;
    global found;
    global inventory;
    while (i < 4):
        if any (str(stone) in s for s in board[i]):
            if (i == 0):
                found = True;
                j = 0;
                if (_take(stone) != "NULL"):
                    print "[*] " + stone + " taken !";
                    moveBuff.append("F");
                return (0);
            if (i == 1):
                moveBuff.append("L");
                moveBuff.append("F");
                return (0);
            if (i == 2):
                moveBuff.append("F");
                return (0);
            if (i == 3):
                moveBuff.append("R");
                moveBuff.append("F");
                return (0);
        i += 1;
    else:
        rand = random.randint(1, 3);
        if (rand == 1):
            _left();
        elif (rand == 2):
            _forward();
        elif (rand == 3):
            _left();
        else:
            print ("ERROR !\n")
            sys.exit(1);
    return (-1);

def     _checkInventory():
    i = 1;
    global stone;
    global inventory;
    global lvlUp;

    while (i < 7):
        if (int(inventory[i]) < int(lvlUpPatterns[lvl -1][i])):
            if (i == LINEMATE):
                stone = "linemate";
                return (1);
            if (i == DERAUMERE):
                stone = "deraumere";
                return (1);
            if (i == SIBURE):
                stone = "sibur";
                return (1);
            if (i == MENDIANE):
                stone = "mendiane";
                return (1);
            if (i == PHIRAS):
                stone = "phiras";
                return (1);
            if (i == THYSTAME):
                stone = "thystame";
                return (1);
        i += 1;
    print ("[*] All stones gathered, go lvl up  !\n");
    lvlUp = True;
    return (0);

