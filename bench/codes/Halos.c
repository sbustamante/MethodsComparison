#include <allvars.h>
/*Usage:	
 	   ./Halos.out 
	   *	<snapbase>
 	   *	<number of files per snap>
 	   *	<output filename> 
 	   *	<0-all or 1-gas or 2-DM>
 	   *	<linking lenght>
 	   *	<minim number of particles>
*/

int main( int argc, char *argv[] )
{
    int i, file_snap, type;
    long int n_slide;
    float linking;
    int min_parts;

    char snapbase[NMAX1], output[NMAX1], cmd[NMAX1];

    //Snapbase filename
    sprintf( snapbase, "%s", argv[1] );
    //Number of files per snap
    file_snap = atoi( argv[2] );
    //Output filename
    sprintf( output, "%s", argv[3] );
    //Type of data
    type = atoi( argv[4] );
    //Linking lenght for FOF scheme
    linking = atof( argv[5] );
    //Minim number of particles for constructing a halo
    min_parts = atoi( argv[6] );
    
    //Reading data from Gadget file
    Npart_snap = read_snap( snapbase, file_snap, type );

    //Writing temporal data with positions
    ascii_data_pos( Part, Npart_snap, "pos.tmp", 1 );
    
    //Runing FOF scheme
    printf("\n==========================================================================\n");
    printf(" Identifying Halos\n");
    printf("==========================================================================\n");
    sprintf( cmd, "./fofscr/fof -e %f -m %d -p %lf < ./pos.tmp", linking, min_parts, 1 );
    system( cmd );
    system( "rm ./pos.tmp" );

    return 0;
}