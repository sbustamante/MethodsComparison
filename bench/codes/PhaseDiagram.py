#PhaseDiagram.py
#
#This code makes a video of the evolution of a slide of the simulation
#Usage: PhaseDiagram.py
#
#by: Sebastian Bustamante

execfile('_head.py')

#==================================================================================================
#			PARAMETERS
#==================================================================================================
#Simulation
simulation = "SPH_64"
#Box lenght [kpc h^-1]
Box = 20000
#Snapbase
snapbase = "SPH_snap"
#Number of snapshots
snaps = 136
#Number of files per snap
snapfiles = 1
#Sampling rate
sampling = 2
#Type of print (gas-0	all-1)
type = 0

#Gas properties
properties = [ "Energy","Density","Pressure" ]	#Specific order of properties
indexes = { "Energy":8, "Density":9, "Pressure":10, "Temperature":11 }
units = { "Energy":"(km/sec)$^2$",\
	  "Density":"$10^{10}$ h$^{-1}$M$_{\odot}$/(h$^{-1}$ kpc)$^3$",\
	  "Pressure":"." }

#Window parameters
prop1 = [ 0, 7 ]
prop1_range = [0, 0.1, 0.2, 0.3, 0.4]
prop2 = [ -11, -4 ]
prop2_range = [0, 0.2, 0.4, 0.6]
#Bins of histograms
bins = 28.

#==================================================================================================
#			MAKING VIDEO OF EVOLUTION
#==================================================================================================
for snap in xrange( snaps ):
    #Formating plot................................................................................
    #no labels
    nullfmt = NullFormatter()

    #definitions for the axes
    left, width = 0.1, 0.65
    bottom_v, height = 0.1, 0.65
    bottom_h = left_h = left+width+0.02

    rect_hist2D = [left, bottom_v, width, height]
    rect_histx = [left, bottom_h, 1.24*width, 0.2]
    rect_histy = [left_h, bottom_v, 0.2, height]

    #start with a rectangular Figure
    plt.figure(1, figsize=(8,8))

    axHist2D = plt.axes(rect_hist2D)
    axHistx = plt.axes(rect_histx)
    axHisty = plt.axes(rect_histy)

    #no labels
    axHistx.xaxis.set_major_formatter(nullfmt)
    axHisty.yaxis.set_major_formatter(nullfmt)
    
    #Loading data of current snap..................................................................
    data = ascii( "%s/%s/%s"%(datafold,simulation,snapbase), snap, snapfiles, sampling, type )
    
    #Ordered properties
    property1 = np.log10(data[:,indexes[ properties[0] ]])
    property2 = np.log10(data[:,indexes[ properties[1] ]])
    property3 = np.log10(data[:,indexes[ properties[2] ]])

    #Phase diagram
    scatter2d = axHist2D.scatter( property1, property2, c=property3, s=2, marker='.',\
    linewidth=0.01, cmap='hot')
    #Create the colorbar
    axc, kw = matplotlib.colorbar.make_axes( axHistx,\
    orientation = "vertical", shrink=1., pad=.04, aspect=10, anchor=(.5,1.5) )
    cb = matplotlib.colorbar.Colorbar( axc, scatter2d, orientation = "vertical" )
    cb.set_label( "log$_{10}$(%s  [%s])"%(properties[2],units[properties[2]]), \
    labelpad=-60, fontsize=12 )
    
    #Histogram X (Prop1)
    histx = np.histogram( property1, bins=bins, normed=True, range=prop1 )
    axHistx.bar( histx[1][:-1], histx[0], width = (prop1[1]-prop1[0])/bins,\
    linewidth=2.0, color="gray" )
    #Histogram Y (Prop2)
    histy = np.histogram( property2, bins=bins, normed=True, range=prop2 )
    axHisty.barh( histy[1][:-1], histy[0], height = (prop2[1]-prop2[0])/bins,\
    linewidth=2.0, color="gray" )
    
    #Plot format
    #Upper histogram
    axHistx.set_xlim( prop1 )
    axHistx.set_xticks( np.linspace( prop1[0],prop1[1],bins/2.+1 ) )
    axHistx.set_yticks( prop1_range )
    axHistx.grid( color='black', linestyle='--', linewidth=1., alpha=0.3 )
    axHistx.set_ylabel( "Normed distribution" )
    #Right histogram
    axHisty.set_ylim( prop2 )
    axHisty.set_yticks( np.linspace( prop2[0],prop2[1],bins/2.+1 ) )
    axHisty.set_xticks( prop2_range )
    axHisty.grid( color='black', linestyle='--', linewidth=1., alpha=0.3 )
    axHisty.set_xlabel( "Normed distribution" )
    #2D Scatter
    axHist2D.grid( color='black', linestyle='--', linewidth=1., alpha=0.3 )
    axHist2D.set_xlim( prop1 )
    axHist2D.set_ylim( prop2 )
    axHist2D.set_xticks( np.linspace( prop1[0],prop1[1],bins/4.+1 ) )
    axHist2D.set_yticks( np.linspace( prop2[0],prop2[1],bins/4.+1 ) )
    axHist2D.set_xlabel( "log$_{10}$(%s  [%s])"%(properties[0],units[properties[0]]) )
    axHist2D.set_ylabel( "log$_{10}$(%s  [%s])"%(properties[1],units[properties[1]]) )
    axHist2D.legend( loc='upper right', fancybox=True, shadow=True, ncol = 1, prop={'size':10} )
    axHist2D.text( prop1[1] - 0.5*(prop1[1]-prop1[0]),prop2[1] - 0.05*(prop2[1]-prop2[0]),\
    "%s:snapshot %03d"%(simulation,snap), fontweight="bold" )

    fname='_tmp-%03d.png'%snap
    plt.savefig(fname)
    plt.close()

#Making the video
print 'Making movie animation.mpg - this make take a while'
os.system("ffmpeg -qscale 1 -r 10 -b 9600 -i _tmp-%03d.png  video.mp4")
#Deleting temporal images
os.system('rm -rf *.png')
