#!/usr/bin

import socket
import re
import getopt, sys

host = "127.0.0.1"
port = 4242

buff = bytearray(1024)
yMax = -1
xMax = -1

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)




def     _cmd_failed(cmd):
    print("[!] Error while processing [" + cmd + "]!\n[!] Connection closed by ZappyServer\n");
    s.close();
    sys.exit(-1);

def     _connect_routine():
    s.connect((host, port))

    print ("[-] ZappySanchezStyle\n[*] Connection on {}".format(port));
    
    r = s.recv_into(buff, 1024);
#    print "<-" + buff

    s.send("nj\n");
 #   print "-> nj"
    
    r = s.recv_into(buff, 1024);
    if (str(buff) == "ko"):
        cmd_failed();
    buff[r] = 0;
    regEx = re.findall(r"\b\d+\b", str(buff));
    rem = regEx[0];
    yMax = regEx[1];
    xMax = regEx[2];

    print ("[*]Info:\n\tRemaining conn :" + rem + "\n\tYmax : " + yMax + "\n\txMax : " + xMax);
    s.close()

def     _forward():
    s.send("Forward\n");
    if (s.recv_into(buff, 1024) == 0 or str(buff) == "ko\n"):
        _cmd_failed("Forward");
    print("[*] Moved forward\n");

def     _right():
    s.send("Right\n");
    if (s.recv_into(buff, 1024) == 0 or str(buff) == "ko\n"):
        _cmd_failed("Right");
    print("[*] Move right\n");
    
def     _left():
    s.send("Left\n");
    if (s.recv_into(buff, 1024) == 0 or str(buff) == "ko\n"):
        _cmd_failed("Left");
    print("[*] Moved left\n");

def     _look():
    s.send("Look\n");
    if (s.recv_into(buff, 1024) == 0  or str(buff) == "ko\n"):
        _cmd_failed("Look");
    print("[*] Look:\n" + str(buff));

def     _inventory():
    s.send("Inventory\n");
    if (s.recv_into(buff, 1024) == 0  or str(buff) == "ko\n"):
        _cmd_failed("Inventory");
    print("[*] Inventory:\n" + str(buff));

def     _broadcast(text):
    s.send("Broadcast" + text + "\n");
    if (s.recv_into(buff, 1024) == 0 or str(buff) == "ko\n"):
        _cmd_failed("Broadcast");
    print("[*] [" + text + "] broadcasted\n");

def     _connect_nbr():
    s.send("Connect_nbr\n");
    if (s.recv_into(buff, 1024) == 0 or str(buff) == "ko\n"):
        _cmd_failed("Connect_nbr");
    print("[*] Number of team unused slots: " + str(buff));

def     _fork():
    s.send("Fork\n");
    if (s.recv_into(buff, 1024) == 0 or str(buff) == "ko\n"):
        _cmd_failed("Fork");
    print("[*] Drone forked\n");

def     _eject():
    s.send("Eject\n");
    if (s.recv_into(buff, 1024) == 0 or str(buff) == "ko\n"):
        _cmd_failed("Eject");
    if (str(buff) == "ko\n"):
        print ("[!] Couldn't eject drone ...\n");
    else:
        print ("[*} Player Ejected\n");

def      _dead():
    s.send("-\n");
    if (s.recv_into(buff, 1024) == 0 or str(buff) != "dead\n"):
        _cmd_failed("Dead");
    print ("[*] X_X\n");

def     _take(obj):
    s.send("Take " + obj + "\n");
    if (s.recv_into(buff, 1024) == 0  or str(buff) == "ko\n"):
        _cmd_failed("Take");
    if (str(buff) == "ok\n"):
        print ("[*] Object taken successfully !\n");
        return (1);
    else:
        print ("[!] Couldn't pick up object ...\n");
        return (-1);

def     _set(obj):
    s.send("Set " + obj + "\n");
    if (s.recv_into(buff, 1024) == 0 or str(buff) == "ko\n"):
        _cmd_failed("Set");
    print ("[*] Object " + obj + " has been put down !\n");

def     _incant():
    s.send("Incantation\n");
    if (s.recv_into(buff, 1024) == 0 or str(buff) == "ko\n"):
        _cmd_failed("Incantation");
    if (str(buff) == "Elevation underway"):
        print ("[!] Couldn't accomplish elevation...\n");
        return (-1);
    print ("[*] Elevation done : " + str(buff) + " !");
    return (1);


def     _display_help():

    print ("USAGE: ./zappy_ai -p port -n name -h machine \n\tport is the port number")
    print ("\tname\t is the name of the team\n\tmachine\t is the name of the machine; localhost by default\n");
    sys.exit(-1);
    
if (len(sys.argv) != 4):
    _display_help();
opt, rem = getopt.getopt(sys.argv[1:], 'n:p:h:')
print opt
_connect_routine();
