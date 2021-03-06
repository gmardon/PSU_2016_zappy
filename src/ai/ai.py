#!/usr/bin/python2.7
#coding: utf-8

import socket
import re
import getopt, sys
import random
import time
import threading
import subprocess
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
lvl = 1
food = 3

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

backtrack = []
board = [[], [], [], []]
vision = []
moveBuff = [];
stone = "";
found = False;
inventory = [0, 0, 0, 0, 0, 0, 0]

FOOD = 0
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


# class   threadIO(threading.Thread):
    
    
#     def __init__(self):
#         threading.Thread.__init__(self);
#         self.lock = threading.Lock();
#         self.term = sys.stdout;
        
#     def     run(self):
#         global queue;
#         global alive;
#         alive = True;

#         self.term.write("[+]IOThread now running\n");
#         print "ok\n"
#         while (alive == True):
        
#             ret = s.recv_into(IOBuff, buff_size);
#             print (str(IOBuff));
#             if (ret < 0):
#                 print "Error";
#             break;
#         IOStr = str(IOBuff);
#         if (IOStr == "DEADBEEF"):
#             alive = False;
#         self.term.write("[+] Rcvd : [" + IOStr + "]\n");
            
def     _cmd_failed(cmd):
    print("[!] Error while processing [" + cmd + "]!\n");
    sys.exit(0);
    
def     _connect_routine():
    r = s.connect((host, port))
    print ("[-] ZappySanchezStyle - Les maçons du code\n[*] Connection on {}".format(port) + " @ " + host);
    
    r = s.recv_into(buff, buff_size);
    #print ("[" + str(buff) + "]");
    s.send("nj\n");
    r = s.recv_into(buff, buff_size);
    print ("[" + str(buff) + "]");
    msg = str(buff);
    if (msg.find("ko") != -1):
        _cmd_failed("connection routine");
    # else:
    #     #print ("buff =" + msg + " & find = " + msg.find("ok") + ".")
    # if (msg.split(" ", 1)[0] == "ko"):
    #     _cmd_failed("connection routine2");
    #     #print("Buff -> : [" + strmsg.split(" ")[0] + "]")
    buff[r] = 0;
    regEx = re.findall(r"\b\d+\b", str(msg));
    rem = regEx[0];
    yMax = regEx[1];
    xMax = regEx[2];

    #print ("[*]Info:\n\tRemaining conn :" + rem + "\n\tYmax : " + yMax + "\n\txMax : " + xMax);
    

def     _forward():
    s.send("Forward\n");
    
    if (s.recv_into(buff, buff_size) == 0 or str(buff) == "ko\n"):
        return(_cmd_failed("Forward"));
    #print("[*] Moved forward\n");
    backtrack.append("F");
    return (1);

def     _right():
    s.send("Right\n");
    if (s.recv_into(buff, buff_size) == 0 or str(buff) == "ko\n"):
        return(_cmd_failed("Right"));
    #print("[*] Move right\n");
    backtrack.append("R");
    return (1);

def     _left():
    s.send("Left\n");
    if (s.recv_into(buff, buff_size) == 0 or str(buff) == "ko\n"):
        return(_cmd_failed("Left"));
    #print("[*] Moved left\n");
    backtrack.append("L");
    return (1);

def     _look():
    s.send("Look\n");
    if (s.recv_into(buff, buff_size) == 0  or str(buff) == "ko\n"):
        return(_cmd_failed("Look"));
    return (str(buff));

def     _inventory():
    s.send("Inventory\n");
    if (s.recv_into(buff, buff_size) == 0  or str(buff) == "ko\n"):
        return(_cmd_failed("Inventory"));
    return (str(buff));

def     _broadcast(text):
    s.send("Broadcast" + text + "\n");
    if (s.recv_into(buff, buff_size) == 0 or str(buff) == "ko\n"):
        return(_cmd_failed("Broadcast"));
    print("[*] [" + text + "] broadcasted\n");
    return (1);

def     _connect_nbr():
    s.send("Connect_nbr\n");
    if (s.recv_into(buff, buff_size) == 0 or str(buff) == "ko\n"):
        return(_cmd_failed("Connect_nbr"));
    #print("[*] Number of team unused slots: " + str(buff));
    return (1);               

def     _fork():
    s.send("Fork\n");
    if (s.recv_into(buff, buff_size) == 0 or str(buff) == "ko\n"):
        return(_cmd_failed("Fork"));
    #print("[*] Drone forked\n");
    return (1);

def     _eject():
    s.send("Eject\n");
    if (s.recv_into(buff, buff_size) == 0 or str(buff) == "ko\n"):
        return(_cmd_failed("Eject"));
    if (str(buff) == "ko\n"):
        print ("[!] Couldn't eject drone ...\n");
    else:
        print ("[*} Player Ejected\n");
        return (1);
    
def      _dead():
    s.send("-\n");
    if (s.recv_into(buff, buff_size) == 0 or str(buff) != "dead\n"):
        return(_cmd_failed("Dead"));
    #print ("[*] X_X\n");
    return (1);

def     _take(obj):
    s.send("Take "+ str(obj) + "\n");
    if (s.recv_into(buff, buff_size) == 0  or str(buff) == "ko\n"):
        return(_cmd_failed("Take"));
    if (str(buff).split(" ")[0].split("\n")[0] == "ok"):
#        print ("[*] Object taken successfully !\n");
        return ("OK");
    else:
        print ("[!] Couldn't pick up object : " + obj +" ...\n");
        time.sleep(0.5);
        return ("NULL");

def     _set(obj):
    s.send("Set " + obj + "\n");
    if (s.recv_into(buff, buff_size) == 0 or str(buff) == "ko\n"):
        return(_cmd_failed("Set"));
    #print ("[*] Object " + obj + " has been put down !\n");
    return (-1);

def     _incant():
    s.send("Incantation\n");
    if (s.recv_into(buff, buff_size) == 0 or str(buff) == "ko\n"):
        return(_cmd_failed("Incantation"));
    
    return (1);

def     _flushMovBuff():
    global moveBuff;
    moveBuff[:] = [];

def     _display_help():

    print ("USAGE: ./zappy_ai -p port -n name -h machine \n\tport is the port number")
    print ("\tname\t is the name of the team\n\tmachine\t is the name of the machine; localhost by default\n");
    sys.exit(-1);


def     _updateVision():
    global board;
    i = 0;
    ret = _look().split(",");
    ret[0] = ret[0][1:];
    
    # #print (">>";
    # #print ret;
    # if (ret[0][0] == '['):
    while (i < 3):
        board[i] = ret[i].split(" ");
        if (i == 3):
            board[i] = board[i][0];
        i += 1;
    return (1);    

#if (food in board[i])
def     _scavengeFood():
    global moveBuff;
    i = 0;
    _harvested = 9;
    _flushMovBuff();
    
    while (_harvested < 10):
        i = 0;
        while (i < 3):
            if any ("food" in s for s in board[i]):
            #print ("[*] Found food on current tile !\n");
                if (_take("food") != "NULL"):
                    _harvested += 1;
                    #                   found = True;
                i += 1;
                _forward();
                    #print ("[*] Didn't found any food");
    return (1);
        
def     _checkInventory():
    i = 1;
    global stone;
    global inventory;
    global lvlUp;
    # _#printInventory();
    while (i < 7):
#        print ("Inv: " + str(inventory[i]) + " & patterns : " + str(lvlUpPatterns[lvl -1][i]) + " !");
        if (int(inventory[i]) < int(lvlUpPatterns[lvl -1][i])):
            if (i == LINEMATE):
 #               print ("Looking for linemate\n");
                stone = "linemate";
                return (1);
            if (i == DERAUMERE):
  #              print ("Looking for deraumere\n");
                stone = "deraumere";
                return (1);
            if (i == SIBURE):
   #             print ("Looking for sibur\n");
                stone = "sibur";
                return (1);
            if (i == MENDIANE):
    #            print ("Looking for mendiane\n");
                stone = "mendiane";
                return (1);
            if (i == PHIRAS):
     #           print ("Looking for phiras\n");
                stone = "phiras";
                return (1);
            if (i == THYSTAME):
      #          print ("Looking for thystame\n");
                stone = "thystame";
                return (1);
        i += 1;
    print ("[*] All stones gathered, go lvl up  !\n");
    _incant();
    print ("[*] Incant sent.");
    sys.exit();
    lvlUp = True;
    return (0);

def     _scavengeStones():
    i = 0;
    global stone;
    global found;
    global inventory;
    #print ("stone : [" + stone + "] !");
    while (i < 4):
        #print (str(board[i]));
        if any (str(stone) in s for s in board[i]):
#            print ("[*] Found " + stone + " on tile " + str(i) + " .");
            if (i == 0):
                found = True;
 #               print ("[*] Taking " + stone + " ! ");
                if (_take(stone) != "NULL"):
                    print "[*] " + stone + " taken !";
                    moveBuff.append("F");
                return (0);
            if (i == 1):
#                print ("[?] Should move up and left next turn\n");
                moveBuff.append("L");
                moveBuff.append("F");
                return (0);
            if (i == 2):
 #               print ("[?] Should move forward next turn\n");
                moveBuff.append("F");
                return (0);
            if (i == 3):
  #              print ("[?] Should move up and right next turn\n");
                moveBuff.append("R");
                moveBuff.append("F");
                _#printMap();
                return (0);
        i += 1;
    else:
        rand = random.randint(1, 3);
        if (rand == 1):
            #print ("MOVING LEFT");
            _left();
        elif (rand == 2):
            #print ("MOVING FORWARD");
            _forward();
        elif (rand == 3):
            #print ("MOVING LEFT");
            _left();
        else:
            print ("ERROR !\n")
            sys.exit(1);
    return (-1);

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

def     _layInventory():
    return (1);

def     _incant():
    return (1);

def     _printInventory():
    i = 0;
    while (i < 7):
        #print int(inventory[i]);
        i +=1;

def     _printMap():
    i = 0;
    while (i < 3):
        #print ("[*] Tile " + str(i) + " :\n");
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

def     _checkBuff():
    while (moveBuff[-1:]):
        char = str(moveBuff[-1:])
        if (char[2] == "F"):
#            print ("[*] Moving forward");
            _forward();
        elif (char[2] == "R"):
 #           print ("[*] Moving right");
            _right();
        elif (char[2] == "L"):
  #          print ("[*] Moving left");
            _left();
        moveBuff.pop();
    else:
        return (-1);


def     _ia():
    global found;
    global inventory
    global lvlUp;
    global moveBuff;
    
    # IO = threadIO();
    # IO.start();
    while (True):
        move = random.randint(1, 5);
        if (moveBuff):
            if (moveBuff[-1:]):
                _checkBuff();
        _updateVision();
        found = False;
        if (int(_updateInventory()[0]) < 10):
            print ("[*] Food level critically low [" + inventory[0] + "] !");
            _scavengeFood();
            _flushMovBuff();
        if (lvlUp == True):
            print ("[*] Gathering other drones !");
            _gatherDrones();
        elif ( _checkInventory() != 0):
            # print ("[*] Looking for " + stone + " !");
            _scavengeStones();
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
sys.exit(0);

## DBG
_updateInventory();
_updateVision();
_scavengeFood();
_checkInventory();
