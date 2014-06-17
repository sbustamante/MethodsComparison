#!/bin/bash

SNAPBASE="../data/snap__135"
SNAPFILES=1
AXIS=0
SLIDE=0
DX=1000
SAMPLING=1
OUTPUT="temp.tmp"

#Running code
rm ./Cutter.out
make Cutter 
time ./Cutter.out $SNAPBASE $SNAPFILES $AXIS $SLIDE $DX $SAMPLING $OUTPUT