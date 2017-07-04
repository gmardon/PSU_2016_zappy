#!/usr/bin/python2.7
#coding: utf-8

import socket
import re
import getopt, sys
import random
import time
import threading
import subprocess
from connection import *
from ia import *
from misc import *
from scavenge import *


def     _forward():
    s.send("Forward\n");
    if (s.recv_into(buff, buff_size) == 0 or str(buff) == "ko\n"):
        return(_cmd_failed("Forward"));
    backtrack.append("F");
    return (1);

def     _right():
    s.send("Right\n");
    if (s.recv_into(buff, buff_size) == 0 or str(buff) == "ko\n"):
        return(_cmd_failed("Right"));
    backtrack.append("R");
    return (1);

def     _left():
    s.send("Left\n");
    if (s.recv_into(buff, buff_size) == 0 or str(buff) == "ko\n"):
        return(_cmd_failed("Left"));
    backtrack.append("L");
    return (1);

def     _broadcast(text):
    s.send("Broadcast" + text + "\n");
    if (s.recv_into(buff, buff_size) == 0 or str(buff) == "ko\n"):
        return(_cmd_failed("Broadcast"));
    print("[*] [" + text + "] broadcasted\n");
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

def      _dead():
    s.send("-\n");
    if (s.recv_into(buff, buff_size) == 0 or str(buff) != "dead\n"):
        return(_cmd_failed("Dead"));
    return (1);

def     _take(obj):
    s.send("Take "+ str(obj) + "\n");
    if (s.recv_into(buff, buff_size) == 0  or str(buff) == "ko\n"):
        return(_cmd_failed("Take"));
    if (str(buff).split(" ")[0].split("\n")[0] == "ok"):
        return ("OK");
    else:
        print ("[!] Couldn't pick up object : " + obj +" ...\n");
        time.sleep(0.5);
        return ("NULL");

def     _set(obj):
    s.send("Set " + obj + "\n");
    if (s.recv_into(buff, buff_size) == 0 or str(buff) == "ko\n"):
        return(_cmd_failed("Set"));
    return (-1);

def     _incant():
    s.send("Incantation\n");
    if (s.recv_into(buff, buff_size) == 0 or str(buff) == "ko\n"):
        return(_cmd_failed("Incantation"));
    return (1);
