#!/bin/bash

# SNAPBASE="/home/sbustamante/box20VPH/SPH_064/snap__010"
SNAPBASE="$HOME/data/SPH_064/snap__135"
# SNAPBASE="./snapshot_007"
SNAPFILES=1
AXIS=0
SLIDE=10000
DX=1000
SAMPLING=1
OUTPUT="temp.tmp"
TYPE=0			#[ 0-all      1-gas      2-DM ]
LINKING=0.2
MINIMPART=30

#Running Cutter [ 1 ]
if [ $1 -eq 1 ]; then
    rm ./Cutter.out
    make Cutter 
    #Running code
    time ./Cutter.out $SNAPBASE $SNAPFILES $AXIS $SLIDE $DX $SAMPLING $OUTPUT $TYPE

#Running Ascii [ 2 ]
elif [ $1 -eq 2 ]; then
    rm ./Ascii.out
    make Ascii
    #Running code
    time ./Ascii.out $SNAPBASE $SNAPFILES $SAMPLING $OUTPUT $TYPE
    
#Running Halos [ 3 ]
elif [ $1 -eq 3 ]; then
    rm ./Halos.out
    make Halos
    #Running code
    time ./Halos.out $SNAPBASE $SNAPFILES $OUTPUT $TYPE $LINKING $MINIMPART
    
fi