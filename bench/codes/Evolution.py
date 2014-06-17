#Evolution.py
#
#This code makes a video of the evolution of a slide of the simulation
#Usage: Evolution.py
#
#by: Sebastian Bustamante

execfile('_Head.py')

#==================================================================================================
#			PARAMETERS
#==================================================================================================
#Simulation
simulation = "SPH_128/"
#Box lenght [kpc h^-1]
Box = 20000
#Snapbase
snapbase = "snap"
#Number of snapshots
snaps = 135
#Number of files per snap
snapfiles = 1
#Sampling rate
sampling = 10

#Axis [0-X  1-Y  2-Z]
axis = 0
#Slide	[kpc h^-1]
slide = 10000
#Thick	[kpc h^-1]
dx = 1000

#Background color
backcolor = "black"
#Particles color
partcolor = "white"
#Particles size
partsize = 0.2

#==================================================================================================
#			MAKING VIDEO OF EVOLUTION
#==================================================================================================
for snap in xrange( snaps ):
    #Image size
    plt.figure( figsize=(10,8) )
    
    #Loading data of current snap
    partsnap = slide( "%s/%s/%s"%(datafold,simulation,snapbase), \
    snap, snapfiles, axis, coor, dx, sampling )
    
    #Background
    plt.fill_between( [0,Box], [0,0], [Box,Box], color = backcolor )
    
    #Cut in X
    if axis == 0:
	plt.plot( partsnap[:,2], partsnap[:,3], ".", markersize = partsize, color = partcolor )
    #Cut in Y
    if axis == 1:
	plt.plot( partsnap[:,1], partsnap[:,3], ".", markersize = partsize, color = partcolor )
    #Cut in Z
    if axis == 2:
	plt.plot( partsnap[:,1], partsnap[:,2], ".", markersize = partsize, color = partcolor )

    plt.xlim( (0,Box) )
    plt.ylim( (0,Box) )
    fname='_tmp-%03d.png'%i
    plt.savefig(fname)
    files.append(fname)
    plt.close()

#Making the video
print 'Making movie animation.mpg - this make take a while'
os.system("ffmpeg -qscale 1 -r 10 -b 9600 -i _tmp-%03d.png  video.mp4")
#Deleting temporal images
os.system('rm -rf *.png')