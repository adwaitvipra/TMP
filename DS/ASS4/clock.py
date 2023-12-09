#!/bin/python

class lamport_clock:
    time = 0

    def increment (self):
        self.time += 1

    def update (self, received_time):
        self.time = max (self.time, received_time) + 1

    def get_time (self):
        return self.time


count = int (input ("Enter the number of clocks: "))
clocks = [lamport_clock () for _ in range (count)]

while True:

    for i, clock in enumerate (clocks):
        print (f"Clock {i+1}: {clock.get_time()}")

    choice = input ("Enter an option \n1. Increase time\n2. Synchronise\n3. Exit\n>> ")

    if choice == "1":
        clock_index = int (input("Enter the clock : "))
        clocks[clock_index-1].increment ()

    elif choice == "2":
        sender_index = int (input ("Enter the sender clock index : "))
        receiver_index = int (input ("Enter the receiver clock index : "))
        clocks[receiver_index-1].update (clocks[sender_index-1].get_time ())

    elif choice == "3":
        break

    else:
        print ("Invalid option.")
