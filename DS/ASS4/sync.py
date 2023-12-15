#!/bin/python

from socket import *
from sys import argv
from threading import Thread 

argc = len (argv)

if argc > 4:
    src_addr = argv[1]
    src_port = int (argv[2])
    dst_addr = argv[3]
    dst_port = int (argv[4])

else:
    src_addr = dst_addr = '127.0.0.1'
    src_port = 11111
    dst_port = 55555

def ping (addr, port, msg):
    peer = socket (AF_INET, SOCK_STREAM)
    peer.connect ((addr, port))

    peer.send (msg.encode ())

    peer.close ()

def synchronize (addr, port):
    global counter

    this = socket (AF_INET, SOCK_STREAM)
    this.bind ((addr, port))
    this.listen (5)

    while True:
        peer_socket, addr = this.accept ()
        data = peer_socket.recv (1024).decode ()

        peer_counter = int (data)

        if (counter < peer_counter):
            counter = peer_counter + 1

if __name__ == "__main__":
    global counter
    counter = 0

    th = Thread(target = synchronize, args = (src_addr, src_port,))
    th.start()

    while True:

        opt = int (input ("\n0. SHOW\n1. INCREMENT\n2. SYNCHRONIZE\nENTER AN OPTION > "))

        if opt == 0:
            print ("COUNTER =", counter);

        elif opt == 1:
            counter = counter + 1
            print("COUNTER =", counter)

        elif opt == 2:
            msg = str (counter)
            ping (dst_addr, dst_port, msg)

        else:
            print("ERROR!")
