#include <allvars.h>

/**************************************************************************************************
 NAME:	     read_head
 FUNCTION:   This function reads a header of a Gadget snapshot file
 INPUTS:     Filename
 RETURN:     0
 COMMENTS:   Based on the version by Juan Carlos Munoz-Cuartas
**************************************************************************************************/
int read_head( char *filename )
{
    int i, Npart_Total = 0, dummi;
    char label[4];
    FILE *fp_inp;
    struct gadget_head Gheader;

    //Opening input file
    if( (fp_inp=fopen(filename,"r"))==NULL ){
	printf( "It is not possible to open %s (not existing file)", filename );
	return 1;
	exit(0);}
    
    //Reading header
    fread(&dummi,sizeof(dummi),1,fp_inp);
    fread(&label,sizeof(char),4,fp_inp);
    fread(&dummi,sizeof(dummi),1,fp_inp);
    fread(&dummi,sizeof(dummi),1,fp_inp);
    fread(&dummi,sizeof(dummi),1,fp_inp);
    fread(&Gheader,sizeof(Gheader),1,fp_inp);
    fread(&dummi,sizeof(dummi),1,fp_inp);
  
    //Printing number of particles of each defined class
    for( i=0;i<6;i++ )
	printf(" * %10d Particles of class %d\n",Gheader.npart[i],i); 
    printf("\n");
        
    //Printing information about particles masses
    for(i=0; i<6; i++){
	//Individual masses
	if((Gheader.npart[i] != 0) && (Gheader.mass[i] != 0.0))
	    printf(" * The mass of each particle is %d es %g\n",i,Gheader.mass[i]);
	//Individual masses for each set of particles
	if((Gheader.npart[i] != 0) && (Gheader.mass[i] == 0.0))
	    printf(" * There are individual mases for this particle set %d\n",i);}
    printf("\n");
    
    //Information of this snapshot
    printf(" * Frame's Time... %g\n",Gheader.time); 
    printf(" * Redshift... %g\n",Gheader.redshift);
    printf(" * Flagsfr... %d\n",Gheader.flag_sfr);
    printf(" * Flagfed... %d\n",Gheader.flag_feedback);
    printf("\n");
    
    //Counting number of particles (nall for number>2^32 particles)
    for(i=0; i<6; i++){
	printf(" * Header nall[%d] is: %d \n",i,Gheader.npartTotal[i]);
	Npart_Total += Gheader.npartTotal[i];}
    printf("\n");
    
    //Information of the whole simulation
    printf(" * Flagcool... %d\n",Gheader.flag_cooling);
    printf(" * numfiles... %d\n",Gheader.num_files);
    printf(" * Boxsize... %g\n",Gheader.BoxSize);
    printf(" * Omega0... %g\n",Gheader.Omega0);
    printf(" * OmageLa... %g\n",Gheader.OmegaLambda);
    printf(" * Hubbleparam... %g\n",Gheader.HubbleParam);
    printf(" * Npart_Total=%d\n\n",Npart_Total);
    
    //Allocating memory for the particle array, (including all single files of the snapshot)
    if( !(Part = (struct part *) malloc((size_t) Npart_Total*sizeof(struct part))) ){
	printf("No memory available for load the particles (%s)\n",filename);
	return 1;
	exit(0);}
   
    //Used memory
    printf(" * Using %f Mb in memory\n\n",Npart_Total*sizeof(struct part)/(1020*1024.0));

    return 0;
}


/**************************************************************************************************
 NAME:	     read_snap
 FUNCTION:   This function reads a complete Gadget snap file in format 2.
 INPUTS:     Snapbase of the current snapshot, number of single component files
 RETURN:     number of particles in the snap (0 if some error)
 COMMENTS:   Based on the version by Juan Carlos Munoz-Cuartas
**************************************************************************************************/
int read_snap( char snapbase[NMAX1], 
	       int filenumber )
{
    int i, s, dummi, global_acum = 0;
    
    int id;
    float pos[3], vel[3];
        
    char label[4], filename[NMAX1];
    long int blksize_pos, blksize_vel, blksize_ids;
    
    struct gadget_head header1;
    
    FILE *fp_pos;
    FILE *fp_vel;
    FILE *fp_ids;
    FILE *fp_head;
    FILE *pf_out;
        
    printf("==========================================================================\n");
    printf(" Reading from gadget file %s, %d \n",filename);
    printf("==========================================================================\n");
    
    //Sweeping all component files of this snapshot
    for( s=0;s<filenumber;s++ ){

	//Filename of current file
	sprintf( filename,"%s.%d",snapbase,s );
	if( filenumber == 1 )
	    sprintf( filename,"%s",snapbase );
	  
	//Reading first file of the sequence for this snapshot
	if( s==0 )
	    read_head( filename );

	//Openning current file
	if( !(fp_head=fopen(filename,"r")) ){
	    printf("read_gadget cannot open %s\n",filename);
	    exit(0);}

	//Different blocks of the Gadget snapshot file
	fp_pos=fopen( filename,"r" );
	fp_vel=fopen( filename,"r" );
	fp_ids=fopen( filename,"r" );
	
	//Reading header of the s-th file of the current snapshot
	fread(&dummi,sizeof(dummi),1,fp_head);
	fread(&label,sizeof(char),4,fp_head);
	fread(&dummi,sizeof(dummi),1,fp_head);
	fread(&dummi,sizeof(dummi),1,fp_head);
	fread(&dummi,sizeof(dummi),1,fp_head);
	fread(&header1,sizeof(header1),1,fp_head);
	fread(&dummi,sizeof(dummi),1,fp_head);
	fclose(fp_head);
	
	//Counting number of particles (nall for number>2^32 particles)
	Npart_snap = 0;
	for(i=0; i<6; i++){
	    printf(" * Header nall[%d] is: %d \n",i,header1.npart[i]);
	    Npart_snap += header1.npart[i];}
	
	//Positioning of different blocks in the snapshot file in order to read them
	blksize_pos = 9*sizeof(int)  + 2*4*sizeof(char) + sizeof(header1);
	blksize_vel = 14*sizeof(int) + 3*4*sizeof(char) + sizeof(header1) + 3*Npart_snap*sizeof(float);
	blksize_ids = 19*sizeof(int) + 4*4*sizeof(char) + sizeof(header1) + 2*3*Npart_snap*sizeof(float);
	fseek(fp_pos,blksize_pos,SEEK_SET);
	fseek(fp_vel,blksize_vel,SEEK_SET);
	fseek(fp_ids,blksize_ids,SEEK_SET);

	//Reading positions, velocities and id of each particle	
	for(i=0; i<Npart_snap ;i++){
	    //Reading from binary files
	    fread(&pos[0],sizeof(float),3,fp_pos);
	    fread(&vel[0],sizeof(float),3,fp_vel);
	    fread(&id,sizeof(int),1,fp_ids);
	    //Positions
	    Part[id].pos[0] = pos[0];
	    Part[id].pos[1] = pos[1];
	    Part[id].pos[2] = pos[2];
	    //Velocities
	    Part[id].vel[0] = vel[0];
	    Part[id].vel[1] = vel[1];
	    Part[id].vel[2] = vel[2];
	    //IDs
	    Part[id].id = id;
	    global_acum++;}

	fclose(fp_pos);
	fclose(fp_vel);
	fclose(fp_ids);

	printf("==========================================================================\n");
	printf(" End of reading from gadget file %s, %d \n",filename, global_acum);
	printf("==========================================================================\n");}

    return Npart_snap;
}

/**************************************************************************************************
 NAME:	     ascii_data
 FUNCTION:   This function write positions, velocities and ids of each particle onto a ascci file
 INPUTS:     Struct with particles, number of particles, output filename, number of data sampling
 RETURN:     0
**************************************************************************************************/
int ascii_data( struct part *parts,
		int Npart,
		char output[NMAX1],
		int sampling )
{
    int i;
    FILE *out;
    
    //Creating output file
    out = fopen( output, "w" );

    //Writing data
    fprintf( out, "#Id\tX\t\tY\t\tZ\t\tVX\t\tVY\t\tVZ\n" );
    
    for( i=0;i<Npart;i+=sampling ){
	fprintf( out, "%d\t%1.5e\t%1.5e\t%1.5e\t%1.5e\t%1.5e\t%1.5e\n", 
		 parts[i].id,
		 parts[i].pos[X], parts[i].pos[Y], parts[i].pos[Z],
		 parts[i].vel[X], parts[i].vel[Y], parts[i].vel[Z]);}
    
    fclose( out );
    
    return 0;
}