#!/bin/bash

lex calculator.l
yacc calculator.y
cc lex.yy.c y.tab.c -ll -lm
