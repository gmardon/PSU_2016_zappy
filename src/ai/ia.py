#!/usr/bin

import socket
import re
import getopt, sys
import random

host = -1
port = -1
teamname = "NONE";

buff = bytearray(1024)
yMax = -1
xMax = -1
lvl = 1
food = 3

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

backtrack = []

inventory = [0, 0, 0, 0, 0, 0, 0]

lvlUpPatterns = [
    [1, 0, 0, 0, 0, 0, 0],
    [2, 1, 1, 1, 0, 0, 0],
    [2, 2, 0, 1, 0, 2, 0],
    [4, 1 ,1, 2, 0, 1, 0],
    [4, 1, 2, 1, 3, 0, 0],
    [6, 1, 2, 3, 0, 1, 0],
    [6, 2, 2, 2, 2, 2, 1]
]
# Food
# nb plyr, line, derau, sib, mendia, phiras, thystame

# 0          1       2    3       4       5         6
# index -> lvl du drone


def     _cmd_failed(cmd):
    print("[!] Error while processing [" + cmd + "]!\n");
    return (-1);

def     _connect_routine():
    s.connect((host, port))

    print ("[-] ZappySanchezStyle\n[*] Connection on {}".format(port) + " @ " + host);
    
    r = s.recv_into(buff, 1024);

    s.send("nj\n");
    
    r = s.recv_into(buff, 1024);
    if (str(buff) == "ko"):
        cmd_failed();
    buff[r] = 0;
    regEx = re.findall(r"\b\d+\b", str(buff));
    rem = regEx[0];
    yMax = regEx[1];
    xMax = regEx[2];

    print ("[*]Info:\n\tRemaining conn :" + rem + "\n\tYmax : " + yMax + "\n\txMax : " + xMax);
    

def     _forward():
    s.send("Forward\n");
    if (s.recv_into(buff, 1024) == 0 or str(buff) == "ko\n"):
        return(_cmd_failed("Forward"));
    print("[*] Moved forward\n");
    backtrack.append("F");
    return (1);

def     _right():
    s.send("Right\n");
    if (s.recv_into(buff, 1024) == 0 or str(buff) == "ko\n"):
        return(_cmd_failed("Right"));
    print("[*] Move right\n");
    backtrack.append("R");
    return (1);
    
def     _left():
    s.send("Left\n");
    if (s.recv_into(buff, 1024) == 0 or str(buff) == "ko\n"):
        return(_cmd_failed("Left"));
    print("[*] Moved left\n");
    backtrack.append("L");
    return (1);

def     _look():
    s.send("Look\n");
    if (s.recv_into(buff, 1024) == 0  or str(buff) == "ko\n"):
        return(_cmd_failed("Look"));
    print("[*] Look:\n" + str(buff));
    return (str(buff));

def     _inventory():
    s.send("Inventory\n");
    if (s.recv_into(buff, 1024) == 0  or str(buff) == "ko\n"):
        return(_cmd_failed("Inventory"));
    return (str(buff));

def     _broadcast(text):
    s.send("Broadcast" + text + "\n");
    if (s.recv_into(buff, 1024) == 0 or str(buff) == "ko\n"):
        return(_cmd_failed("Broadcast"));
    print("[*] [" + text + "] broadcasted\n");
    return (1);

def     _connect_nbr():
    s.send("Connect_nbr\n");
    if (s.recv_into(buff, 1024) == 0 or str(buff) == "ko\n"):
        return(_cmd_failed("Connect_nbr"));
    print("[*] Number of team unused slots: " + str(buff));
    return (1);               

def     _fork():
    s.send("Fork\n");
    if (s.recv_into(buff, 1024) == 0 or str(buff) == "ko\n"):
        return(_cmd_failed("Fork"));
    print("[*] Drone forked\n");
    return (1);

def     _eject():
    s.send("Eject\n");
    if (s.recv_into(buff, 1024) == 0 or str(buff) == "ko\n"):
        return(_cmd_failed("Eject"));
    if (str(buff) == "ko\n"):
        print ("[!] Couldn't eject drone ...\n");
    else:
        print ("[*} Player Ejected\n");
    return (1);

def      _dead():
    s.send("-\n");
    if (s.recv_into(buff, 1024) == 0 or str(buff) != "dead\n"):
        return(_cmd_failed("Dead"));
    print ("[*] X_X\n");
    return (1);

def     _take(obj):
    s.send("Take " + obj + "\n");
    if (s.recv_into(buff, 1024) == 0  or str(buff) == "ko\n"):
        return(_cmd_failed("Take"));
    if (str(buff) == "ok\n"):
        print ("[*] Object taken successfully !\n");
        return (1);
    else:
        print ("[!] Couldn't pick up object ...\n");
        return (-1);

def     _set(obj):
    s.send("Set " + obj + "\n");
    if (s.recv_into(buff, 1024) == 0 or str(buff) == "ko\n"):
        return(_cmd_failed("Set"));
    print ("[*] Object " + obj + " has been put down !\n");
    return (-1);

def     _incant():
    s.send("Incantation\n");
    if (s.recv_into(buff, 1024) == 0 or str(buff) == "ko\n"):
        return(_cmd_failed("Incantation"));
    print ("[*] " + str(buff));
    return (1);


def     _display_help():

    print ("USAGE: ./zappy_ai -p port -n name -h machine \n\tport is the port number")
    print ("\tname\t is the name of the team\n\tmachine\t is the name of the machine; localhost by default\n");
    sys.exit(-1);


def     _scavengeFood():

    return (1);
        
def     _checkInventory():

    return (1);

def     _scavengeStones():
    return (1);

def     _checkLvlUp():
    return (1);

def     _gatherDrones():
    return (1);

def     _layInventory():
    return (1);

def     _incant():
    return (1);

def     _updateInventory():

    l = _inventory().split(',');
    i = 0;
    while (i < 7):
        inventory[i] = l[i].split(' ')[2];
        i += 1;
    return (inventory);

def     _ia():
    move = random.randint(1, 5);
    while (3945):
        if (_updateInventory()[0] < 4):
            print ("[*] Food level critically low [" + str(food) + "] !");
            _scavengeFood();
        elif (_checkInventory()):
            print ("[*] Looking for some more stones !");
            _scavengeStones();
        elif (_checkLvlUp()):
            print ("[*] Gathering other drones !");
            _gatherDrones();
        else:
            _layInventory();
            _incant();
        
        
    
if (len(sys.argv) != 7):
    print len(sys.argv);
    
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
