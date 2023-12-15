#!/bin/bash

lex wc.l
gcc lex.yy.c -ll
