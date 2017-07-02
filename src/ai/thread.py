import socket
import re
import getopt, sys
import random
import time
from threading import Condition, Thread, Lock
queue = [];
lock = Lock();
MAX_NUM = 10;
condition = Condition()

class   ConsumerThread(Thread):
    def run(self):
        global queue;
        while (True):
            condition.acquire();
            if not queue:
                print "Empty queue";
                condition.wait();
                print "Producer added smthg to queue";
            num = queue.pop(0);
            print "Consumed", num;
            condition.notify()
            condition.release()
            time.sleep(random.random())


class   ProducerThread(Thread):
    def run(self):
        nums = range(5);
        global queue;
        while (42):
            condition.acquire();
            if (len(queue) == MAX_NUM):
                print "Queue is full";
                condition.wait();
                print "Queue has been released";
            num = random.choice(nums);
            queue.append(num);
            print "Produced", num;
            condition.notify()
            condition.release()
            time.sleep(random.random());

    
# ProducerThread().start();
# ConsumerThread().start();

