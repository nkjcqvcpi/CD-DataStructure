#!/bin/bash

TASK=highway

#  -static

g++ -std=gnu++14 -Wall -O2 -o ${TASK} grader.cpp ${TASK}.cpp
