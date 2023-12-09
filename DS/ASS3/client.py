#!/usr/bin/python3

from sys import argv
from socket import *

argc = len (argv)

if argc > 1:
    serverAddr = argv[1]
    if argc > 2:
        serverPort = int (argv[2])
else:
    serverAddr = '127.0.0.1'
    serverPort = 55555

def fib (n):
    clientSocket = socket (AF_INET, SOCK_STREAM)
    clientSocket.connect ((serverAddr, serverPort))

    msg = str (n)

    clientSocket.send (msg.encode ())

    modifiedMsg = clientSocket.recv (4096)

    res = modifiedMsg.decode ()
    ret = int (res)

    clientSocket.close()

    return ret
