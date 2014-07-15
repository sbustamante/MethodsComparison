#==================================================================================================
#			HEADERS
#==================================================================================================
from __future__ import division
from struct import *
import numpy as np
import sys
import matplotlib as mpl
#mpl.use('Agg')		#No X11 mode
import os
import matplotlib.pyplot as plt
from pylab import *
import scipy.integrate as integ
import scipy.interpolate as interp
plt.close("all")


#==================================================================================================
#			VARIABLES
#==================================================================================================
#Data Fold
#datafold = "../../../box20VPH/"
datafold = "../data/"
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
    (codesfold, snapbase, snap, files, axis, coor, dx, sampling, type) )
    data = np.loadtxt( "temp.tmp" )
    os.system( "rm temp.tmp" )
    
    return data
  
#..................................................................................................
# Saving data in ascii format
#..................................................................................................
def ascii( snapbase, snap, files, sampling, type ):
    #Running code
    os.system( "%s/Ascii.out %s__%03d %d %d temp.tmp %d"%\
    (codesfold, snapbase, snap, files, sampling, type) )
    data = np.loadtxt( "temp.tmp" )
    os.system( "rm temp.tmp" )
    
    return data