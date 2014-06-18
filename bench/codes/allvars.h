/**************************************************************************************************
			      STRUCTURES
**************************************************************************************************/
//Gadget header structure
struct gadget_head{
    int      npart[6];
    double   mass[6];
    double   time;
    double   redshift;
    int      flag_sfr;
    int      flag_feedback;
    int      npartTotal[6];
    int      flag_cooling;
    int      num_files;
    double   BoxSize;
    double   Omega0;
    double   OmegaLambda;
    double   HubbleParam; 
    char     fill[256- 6*4- 6*8- 2*8- 2*4- 6*4- 2*4 - 4*8];  /* fills to 256 Bytes */
    };

//Particle structure
struct part{
    float pos[3];
    float vel[3];
    int id;
    float mass;
    float energy;
    float rho;
    };

    
/**************************************************************************************************
			      MACROS AND GLOBAL VARIABLES
**************************************************************************************************/
#define NMAX1		1000
#define X		0
#define Y		1
#define Z		2

//Particle arrays
struct part *Part, *cutted;
//Number of particles in current snap
int Npart_snap;
//Number of particles in current snap with variable masses
int Npart_snap_mass;

/**************************************************************************************************
			      HEADERS
**************************************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <proto.h>