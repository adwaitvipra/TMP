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

clientSocket = socket (AF_INET, SOCK_STREAM)
clientSocket.connect ((serverAddr, serverPort))

while True:
    msg = input("> ")

    clientSocket.send (msg.encode ())

    modifiedMsg = clientSocket.recv (4096)

    print(">", modifiedMsg.decode ())
    if modifiedMsg.decode() == "exit" :
        break

clientSocket.close()
input("Press Any Key To Exit!")
