#!/bin/bash

SNAPBASE="../data/SPH_snap__135"
SNAPFILES=1
AXIS=0
SLIDE=10000
DX=1000
SAMPLING=10
OUTPUT="temp.tmp"

#Running Cutter [ 1 ]
if [ $1 -eq 1 ]; then

    #Compiling [ 1-compile	0-nothing ]
    if [ $2 -eq 1 ]; then
	rm ./Cutter.out
	make Cutter 
    fi

    #Running code
    time ./Cutter.out $SNAPBASE $SNAPFILES $AXIS $SLIDE $DX $SAMPLING $OUTPUT

#Running Ascii [ 2 ]
elif [ $1 -eq 2 ]; then
    
    #Compiling [ 1-compile	0-nothing ]
    if [ $2 -eq 1 ]; then
	rm ./Ascii.out
	make Ascii
    fi

    #Running code
    time ./Ascii.out $SNAPBASE $SNAPFILES $SAMPLING $OUTPUT
    
fi