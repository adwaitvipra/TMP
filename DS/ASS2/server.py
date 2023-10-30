#!/usr/bin/python3

from sys import argv
from socket import *
from threading import Thread

argc = len (argv)

if argc > 1:
    serverAddr = argv[1]
    if argc > 2:
        serverPort = int (argv[2])
else:
    serverAddr = '127.0.0.1'
    serverPort = 55555

def do_io (connectionSocket):
    while True:
        msg = connectionSocket.recv (4096)
        msg = msg.decode ()

        if  msg == "exit":
            connectionSocket.send ("exit".encode ())
            break

        connectionSocket.send (msg.encode ())

    print ("Client with address", connectionSocket.getsockname (),"disconnected...")
    connectionSocket.close ()


serverSocket = socket (AF_INET, SOCK_STREAM)
print ("Server socket created...")

serverSocket.bind ((serverAddr, serverPort))
print ("Server socket bound bo address %s & port %d..."%(serverAddr, serverPort))

serverSocket.listen (5)
print ("Server socket listening...")

while True:
    connectionSocket, clientAddr = serverSocket.accept ()
    print ("Client with address", clientAddr, "connected...")
    th = Thread (target=do_io, args = (connectionSocket, ))
    th.start ()

serverSocket.close ()
print ("Server socket closed...")
print("Bye!")
