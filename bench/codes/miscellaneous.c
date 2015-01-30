#include <allvars.h>

/**************************************************************************************************
 NAME:	     cut_box
 FUNCTION:   This function selects particles within some set slide
 INPUTS:     axis to make the cut (0-X, 1-Y, 2-Z), slide coordinate, thick of 
	     the slide
 RETURN:     number of particles in the slide
**************************************************************************************************/
long int cut_box( int axis,
		  float slide,
		  float dx )
{
    long int i, n=0;
    int coor;
    
    //Counting number of particles within the slide
    for( i=0;i<Npart_snap;i++ )
	if( Part[i].pos[axis] >= slide && Part[i].pos[axis] < slide + dx )
	    n++;

    //Allocating memory for the cutted particle array
    if( !(cutted = (struct part *) malloc((size_t) n*sizeof(struct part))) ){
	printf("No memory available for load this slide\n");
	return 1;
	exit(0);}
	
    //Storing particles data for this slide
    n=0;
    for( i=0;i<Npart_snap;i++ )
	if( Part[i].pos[axis] >= slide && Part[i].pos[axis] < slide + dx ){
	    //Saving positions and velocities
	    for( coor=0;coor<3;coor++ ){
		cutted[n].pos[coor] =  Part[i].pos[coor];
		cutted[n].vel[coor] =  Part[i].vel[coor];}
	    //Ids 
	    cutted[n].id =  Part[i].id;
	    
	    //Mass
	    cutted[n].mass = Part[i].mass;
	    //Energy
	    cutted[n].energy = Part[i].energy;
	    //Density
	    cutted[n].rho = Part[i].rho;
	    //Pressure
	    cutted[n].pressure = Part[i].pressure;
	    //Temperature
	    cutted[n].temperature = Part[i].temperature;
	    
	    //Redshift
	    cutted[n].z = Part[i].z;
	    //Time
	    cutted[n].t = Part[i].t;
	    
	    n++;}
	    
    return n;
}