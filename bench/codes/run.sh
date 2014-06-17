#!/bin/bash

SNAPBASE="../data/snap__135"
SNAPFILES=1
AXIS=0
SLIDE=10000
DX=1000
SAMPLING=1
OUTPUT="temp.tmp"

#Compiling
if [ $1 -eq 1 ]; then
    rm ./Cutter.out
    make Cutter 
fi

#Running code
time ./Cutter.out $SNAPBASE $SNAPFILES $AXIS $SLIDE $DX $SAMPLING $OUTPUT