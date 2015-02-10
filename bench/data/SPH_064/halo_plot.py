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


#Loading particles
datos = np.loadtxt("part.dat", usecols=(1,2,3,))
#Loading index of halo domains
domain_index = np.loadtxt("snap__135.domain")
#Loading index of halo members
members_index = np.loadtxt("snap__135.members")-1
#Loading Halo catalog
halos = np.loadtxt("snap__135.halo_catalog",usecols=(0,1,2,5,6,))

#Number of particles within halos
print "Particles in halos:", sum( halos[:,3] )
print "Particles in the domain:", sum( halos[:,4] )
print "Total particles:", sum( halos[:,3] )+sum( halos[:,4] )

#Index of halo to plot 
i = int(sys.argv[1])

#Plotting
C1 = 0
C2 = 1
part_domain=datos[domain_index==i]
part_members=datos[members_index==i]

plt.plot( part_domain[:,C1], part_domain[:,C2], "o", color = "blue", markersize=9 )
plt.plot( part_members[:,C1], part_members[:,C2], "o", color = "red" )
plt.plot( [halos[i,C1],], [halos[i,C2],], "o", color="black", markersize=10 )

#Ploting all halos
plt.plot( halos[:,C1], halos[:,C2], "o", color="black", markersize=3 )

#plt.xlim((0,20000))
#plt.ylim((0,20000))
Radius = 1000
plt.xlim((halos[i,C1]-Radius,halos[i,C1]+Radius))
plt.ylim((halos[i,C2]-Radius,halos[i,C2]+Radius))

plt.show()