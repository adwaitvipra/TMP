#!/bin/python

from client import *

if __name__ == "__main__":
    print ("\t\tFIBCAL : FIBONACCI CALCULATOR")
    n = int (input ("\n\tN? "))

    if (n >= 0):
        ans = fib (n)

        if (ans >= 0):
            print ("\tFIB (%d) = %d" %(n, ans))
        else:
            print ("\tINTERNAL FAILURE")
    else:
        print ("\tVALUE ERROR")
