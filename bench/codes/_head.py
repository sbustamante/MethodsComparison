#==================================================================================================
#			HEADERS
#==================================================================================================
from __future__ import division
from struct import *
import numpy as np
import sys
import os
import random
import matplotlib.pyplot as plt
import scipy.integrate as integ
import scipy.interpolate as interp
plt.close("all")


#==================================================================================================
#			VARIABLES
#==================================================================================================
#Data Fold
datafold = "../../../box20VPH/"
#Codes Fold
codesfold = "./"


#==================================================================================================
#			FUNCTIONS
#==================================================================================================

#..................................................................................................
# Cutting the simulation box
#..................................................................................................
def slide( snapbase, snap, files, axis, coor, dx, sampling, type ):
    #Running code
    os.system( "%s/Cutter.out %s__%03d %d %d %f %f %d temp.tmp %d"%\
    (codesfold,snapbase, snap, files, axis, coor, dx, sampling, type) )
    data = np.loadtxt( "temp.tmp" )
    os.system( "rm temp.tmp" )
    
    return data