#include <allvars.h>
/*Usage:	
 	   ./Ascii.out 
	   *	<snapbase>
 	   *	<number of files per snap>
 	   *	<density of data sampling>
 	   *	<output filename> 
*/

int main( int argc, char *argv[] )
{
    int i, file_snap, sampling;
    struct part *Part;
    
    char snapbase[NMAX1], output[NMAX1];

    //Snapbase filename
    sprintf( snapbase, "%s", argv[1] );
    //Number of files per snap
    file_snap = atoi( argv[2] );
    //Density of data sampling
    sampling = atoi( argv[6] );
    //Output filename
    sprintf( output, "%s", argv[7] );
        
    //Writing data
    ascii_data( Part, Npart_snap, output, sampling );
    
    return 0;
}