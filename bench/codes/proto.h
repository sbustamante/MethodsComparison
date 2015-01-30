// Input Output Module
int read_head( char * );
int read_snap_gas( char *, int );
int read_snap_all( char *, int );
int ascii_data_all( struct part *, int, char *, int );
int ascii_data_gas( struct part *, int, char *, int );
int ascii_data_pos( struct part *, int, char *, int );

//Miscellaneous Module
long int cut_box( int, float, float );

//Gas Module
float pressure( float, float );
float temperature( float );