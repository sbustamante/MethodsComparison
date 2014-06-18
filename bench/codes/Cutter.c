#include <allvars.h>
/*Usage:	
 	   ./Cutter.out 
	   *	<snapbase>
 	   *	<number of files per snap>
 	   *	<axis> 
 	   *	<slide>				[Mpc h^-1]
 	   *	<dx> 				[Mpc h^-1]
 	   *	<density of data sampling>
 	   *	<output filename> 
*/

int main( int argc, char *argv[] )
{
    int i, file_snap, sampling;
    long int n_slide;
    
    int axis;
    float slide, dx;
    char snapbase[NMAX1], output[NMAX1];

    //Snapbase filename
    sprintf( snapbase, "%s", argv[1] );
    //Number of files per snap
    file_snap = atoi( argv[2] );
    //Axis
    axis = atoi( argv[3] );
    //Slide
    slide = atof( argv[4] );
    //Dx
    dx = atof( argv[5] );
    //Density of data sampling
    sampling = atoi( argv[6] );
    //Output filename
    sprintf( output, "%s", argv[7] );
    
    //Reading data from Gadget file
    Npart_snap = read_snap_gas( snapbase, file_snap );

    //Cutting box
    n_slide = cut_box( axis, slide, dx );
    
    //Writing data
    ascii_data_gas( cutted, n_slide, output, sampling );
    
    return 0;
}