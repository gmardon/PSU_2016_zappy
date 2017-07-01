#!/usr/bin
#coding: utf-8

import socket
import re
import getopt, sys
import random

host = -1
port = -1
teamname = "NONE";

buff_size = 2048
buff = bytearray(buff_size)
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

    print ("[-] ZappySanchezStyle - Les maçons du code\n[*] Connection on {}".format(port) + " @ " + host);
    
    r = s.recv_into(buff, buff_size);

    s.send("nj\n");
    
    r = s.recv_into(buff, buff_size);
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
    if (s.recv_into(buff, buff_size) == 0 or str(buff) == "ko\n"):
        return(_cmd_failed("Forward"));
    print("[*] Moved forward\n");
    backtrack.append("F");
    return (1);

def     _right():
    s.send("Right\n");
    if (s.recv_into(buff, buff_size) == 0 or str(buff) == "ko\n"):
        return(_cmd_failed("Right"));
    print("[*] Move right\n");
    backtrack.append("R");
    return (1);

def     _left():
    s.send("Left\n");
    if (s.recv_into(buff, buff_size) == 0 or str(buff) == "ko\n"):
        return(_cmd_failed("Left"));
    print("[*] Moved left\n");
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
    print("[*] Number of team unused slots: " + str(buff));
    return (1);               

def     _fork():
    s.send("Fork\n");
    if (s.recv_into(buff, buff_size) == 0 or str(buff) == "ko\n"):
        return(_cmd_failed("Fork"));
    print("[*] Drone forked\n");
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
    print ("[*] X_X\n");
    return (1);

def     _take(obj):
    s.send("Take food\n");
    if (s.recv_into(buff, buff_size) == 0  or str(buff) == "ko\n"):
        return(_cmd_failed("Take"));
    if (str(buff).split(" ")[0].split("\n")[0] == "ok"):
        print ("[*] Object taken successfully !\n");
        return (str(buff));
    else:
        print ("[!] Couldn't pick up object ...\n");
        return (NULL);

def     _set(obj):
    s.send("Set " + obj + "\n");
    if (s.recv_into(buff, buff_size) == 0 or str(buff) == "ko\n"):
        return(_cmd_failed("Set"));
    print ("[*] Object " + obj + " has been put down !\n");
    return (-1);

def     _incant():
    s.send("Incantation\n");
    if (s.recv_into(buff, buff_size) == 0 or str(buff) == "ko\n"):
        return(_cmd_failed("Incantation"));
    print ("[*] " + str(buff));
    return (1);


def     _display_help():

    print ("USAGE: ./zappy_ai -p port -n name -h machine \n\tport is the port number")
    print ("\tname\t is the name of the team\n\tmachine\t is the name of the machine; localhost by default\n");
    sys.exit(-1);


def     _updateVision():
    i = 0;
    ret = _look().split(",");
    if (ret[0][0] == '['):
        while (i < 4):
            board[i] = ret[i].split(" ");
#            print board[i];
            i += 1;
    return (1);    

def     _scavengeFood():
    i = 0;
    if any ("food" in s for s in board[0]):
        print ("[*] Found food on current tile !\n");
        _take("food");
        found = True;
        return (1);

        
def     _checkInventory():
    i = 1;
    global stone;
    while (i < 7):
        if (int(inventory[i]) < int(lvlUpPatterns[lvl -1][i])):
            if (i == 1):
                print ("Looking for linemate\n");
                stone = "linemate";
                return (1);
            if (i == 2):
                print ("Looking for deraumere\n");
                stone = "deraumere";
                return (1);
            if (i == 3):
                print ("Looking for sibur\n");
                stone = "sibur";
                return (1);
            if (i == 4):
                print ("Looking for mendiane\n");
                stone = "mendiane";
                return (1);
            if (i == 5):
                print ("Looking for phiras\n");
                stone = "mendiane";
                return (1);
            if (i == 6):
                print ("Looking for thystame\n");
                stone = "thystame";
                return (1);
        i += 1;
    print ("[*] No stone to look for !\n");
    return (0);

def     _scavengeStones():
    i = 0;
    global stone;
    print ("stone : " + stone + " !");
    while (i < 4):
        print (str(board[i]));
        if any (str(stone) in s for s in str(board[i])):
            print ("[*] Found " + stone + " on tile " + str(i) + " .");
            Found = True;
            print ("ok\n");
            if (i == 0):
                _take(stone);
                return (1);
            if (i == 1):
                print ("[?] Should move left\n");
                moveBuff.append("L");
                return (0);
            if (i == 2):
                print ("[?] Should move forward\n");
                moveBuff.append("F");
                return (0);
            if (i == 3):
                print ("[?] Should move right\n");
                moveBuff.append("R");
                return (0);
        i += 1;
    return (0);

def     _checkLvlUp():
    return (1);

def     _gatherDrones():
    return (1);

def     _layInventory():
    return (1);

def     _incant():
    return (1);

def     _printInventory():
    i = 0;
    while (i < 7):
        print inventory[i];
        i +=1;

def     _printMap():
    i = 0;
    while (i < 4):
        print ("[*] Tile " + str(i) + " :\n");
        print board[i];
        i +=1;
    return (0);
def     _updateInventory():

    l = _inventory().split(',');
    i = 0;
    while (i < 7):
        inventory[i] = l[i].split(' ')[2];
        i += 1;
    return (inventory);

def     _checkInventory2():
    stone = "lol";

def     _ia():
    global found;
    while (3945):
        found = False;
        move = random.randint(1, 5);
        _updateVision();
        if (int(_updateInventory()[0]) < 10):
            print ("[*] Food level critically low [" + str(food) + "] !");
            _scavengeFood();
        elif ( _checkInventory() != 0):
            print ("[*] Looking for " + stone + " !");
            _scavengeStones();
        elif (_checkLvlUp()):
            print ("[*] Gathering other drones !");
            _gatherDrones();
        else:
            _layInventory();
            _incant();
        if (found != True):
            _forward();
        else:
            print ("TRUE!\n");
        #Synchro ?
        #sleep(1);
        
        
    
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

## DBG
_updateInventory();
_updateVision();
_scavengeFood();
_checkInventory();
