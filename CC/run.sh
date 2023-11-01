#!/bin/bash

lex calculator.l
yacc calculator.y
yacc -d calculator.y
cc lex.yy.c y.tab.c -ll -lm
./a.out
