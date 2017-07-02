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

def     _connect_nbr():
    s.send("Connect_nbr\n");
    if (s.recv_into(buff, buff_size) == 0 or str(buff) == "ko\n"):
        return(_cmd_failed("Connect_nbr"));
    return (1);

def     _fork():
    s.send("Fork\n");
    if (s.recv_into(buff, buff_size) == 0 or str(buff) == "ko\n"):
        return(_cmd_failed("Fork"));
    return (1);

def     _eject():
    s.send("Eject\n");
    if (s.recv_into(buff, buff_size) == 0 or str(buff) == "ko\n"):
        return(_cmd_failed("Eject"));
    if (str(buff) == "ko\n"):
        print ("[!] Couldn't eject drone ...\n");
    else:
        print ("[*} Player Ejected\n");

def     _cmd_failed(cmd):
    print("[!] Error while processing [" + cmd + "]!\n");
    sys.exit(0);

def     _connect_routine():
    r = s.connect((host, port))
    print ("[-] ZappySanchezStyle - Les maçons du code\n[*] Connection on {}".format(port) + " @ " + host);
    r = s.recv_into(buff, buff_size);
    s.send("nj\n");
    r = s.recv_into(buff, buff_size);
    msg = str(buff);
    if (msg.find("ko") != -1):
        _cmd_failed("connection routine");
    buff[r] = 0;
    regEx = re.findall(r"\b\d+\b", str(msg));
    rem = regEx[0];
    yMax = regEx[1];
    xMax = regEx[2];
