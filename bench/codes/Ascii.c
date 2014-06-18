#include <allvars.h>
/*Usage:	
 	   ./Ascii.out 
	   *	<snapbase>
 	   *	<number of files per snap>
 	   *	<density of data sampling>
 	   *	<output filename> 
 	   *	<0-gas or 1-all> 
*/

int main( int argc, char *argv[] )
{
    int i, file_snap, sampling, type;
    
    char snapbase[NMAX1], output[NMAX1];

    //Snapbase filename
    sprintf( snapbase, "%s", argv[1] );
    //Number of files per snap
    file_snap = atoi( argv[2] );
    //Density of data sampling
    sampling = atoi( argv[3] );
    //Output filename
    sprintf( output, "%s", argv[4] );
    //Type of data
    type = atoi( argv[5] );
        
    //Reading data from Gadget file
    if( type == 0 )	//Gas
	Npart_snap = read_snap_gas( snapbase, file_snap );
    else		//All
	Npart_snap = read_snap_all( snapbase, file_snap );
    
    //Writing data
    if( type == 0 )	//Gas
	ascii_data_gas( Part, Npart_snap, output, sampling );
    else		//All
	ascii_data_all( Part, Npart_snap, output, sampling );
    
    return 0;
}