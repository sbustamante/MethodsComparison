#include<stdlib.h>
#include<stdio.h>
#include<math.h>

struct gadget_head
{
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
  char     fill[256- 6*4- 6*8- 2*8- 2*4- 6*4- 2*4 - 4*8];  /* fills to 
							      256 Bytes */
};


struct part
{
  float pos[3];
  float vel[3];
  //float mass;
  int id;
}*Part;


int Npart_Total;
struct gadget_head Gheader;


int read_head0(char *infile)
{
  
  int dummi,i;
  char label[4];
  FILE *fp_inp;
  
  if((fp_inp=fopen(infile,"r"))==NULL)    
    {
      printf("read_gadget cannot open %s",infile);
      exit(0);
    }
  
  fread(&dummi,sizeof(dummi),1,fp_inp);
  fread(&label,sizeof(char),4,fp_inp);
  fread(&dummi,sizeof(dummi),1,fp_inp);
  fread(&dummi,sizeof(dummi),1,fp_inp);
  
  fread(&dummi,sizeof(dummi),1,fp_inp);
  fread(&Gheader,sizeof(Gheader),1,fp_inp);
  fread(&dummi,sizeof(dummi),1,fp_inp);
  
  /*
    REDSHIFT     = Gheader.redshift;
    OMEGA_MATTER = Gheader.Omega0;
    OMEGALAMBDA  = Gheader.OmegaLambda;
    HUBBLEPARAM  = Gheader.HubbleParam;
    COSMIC_TIME  = Gheader.time;
    BoxSize      = Gheader.BoxSize;
  */

  for(i=0; i<6; i++)
    printf(" * %d Particles of class %d\n",Gheader.npart[i],i); 
  
  printf("\n"); 
  
  for(i=0; i<6; i++)
    { 
      if((Gheader.npart[i] != 0) && (Gheader.mass[i] != 0.0))
	printf(" * The mass of each particle is %d es %g\n",i,Gheader.mass[i]);
      
      if((Gheader.npart[i] != 0) && (Gheader.mass[i] == 0.0))
	printf(" * There are individual mases for this particle set %d\n",i);
      
    }     
  
  printf("\n");
  
  printf(" * Frame's Time... %g\n",Gheader.time); 
  printf(" * Redshift... %g\n",Gheader.redshift);
  printf(" * Flagsfr... %d\n",Gheader.flag_sfr);
  printf(" * Flagfed... %d\n",Gheader.flag_feedback);
  
  printf("\n");
  
  Npart_Total = 0;
  for(i=0; i<6; i++)
    {
      printf(" * Header nall[%d] is: %d \n",i,Gheader.npartTotal[i]);
      Npart_Total += Gheader.npartTotal[i];
    }
  
  printf("\n");
  
  printf(" * Flagcool... %d\n",Gheader.flag_cooling);
  printf(" * numfiles... %d\n",Gheader.num_files);
  printf(" * Boxsize... %g\n",Gheader.BoxSize);
  printf(" * Omega0... %g\n",Gheader.Omega0);
  printf(" * OmageLa... %g\n",Gheader.OmegaLambda);
  printf(" * Hubbleparam... %g\n",Gheader.HubbleParam);
  printf(" * Npart_Total=%d\n",Npart_Total);
  
  Part = (struct part *) malloc((size_t) Npart_Total*sizeof(struct part));
  if(Part == NULL)
    {
      printf("No memory available for load dar particles (%s)\n",infile);
      exit(0);
    }
  
  printf("Using %f Mb in memory\n",Npart_Total*sizeof(struct part)/(1020*1024.0));

  return 0;
  
}


int main(int argc, char *argv[])
{
    
  int dummi,i,Npart_snap,global_acum,s,id,k;
  float pos[3],vel[3],aux[3];
  struct gadget_head header1;
  char label[4], buf[200], outfile[200];
  long int blksize_pos,blksize_vel,blksize_ids;
  
  float xmin,ymin,zmin,xmax,ymax,zmax;
  float vxmin,vymin,vzmin,vxmax,vymax,vzmax;
  

  FILE *fp_pos;
  FILE *fp_vel;
  FILE *fp_ids;
  FILE *fp_head;
  FILE *pf_out;
  
  char *snapbase = argv[1];
  int NSNAPS     = atoi(argv[2]);

  global_acum = 0;
  s=NSNAPS;

  sprintf(buf,"%s%d",snapbase,s);
  
//   if(s==0)
    read_head0(buf);

  if((fp_head=fopen(buf,"r"))==NULL)    
    {
      printf("read_gadget cannot open %s\n",buf);
      exit(0);
    }

  fp_pos=fopen(buf,"r");
  fp_vel=fopen(buf,"r");
  fp_ids=fopen(buf,"r");
  
  
  /* reading the header for this sub snap */
  fread(&dummi,sizeof(dummi),1,fp_head);
  fread(&label,sizeof(char),4,fp_head);
  fread(&dummi,sizeof(dummi),1,fp_head);
  fread(&dummi,sizeof(dummi),1,fp_head);
  
  fread(&dummi,sizeof(dummi),1,fp_head);
  fread(&header1,sizeof(header1),1,fp_head);
  fread(&dummi,sizeof(dummi),1,fp_head);
  
  fclose(fp_head);
  
  Npart_snap = 0;
  for(i=0; i<6; i++)
    {
      printf(" * Header nall[%d] is: %d \n",i,header1.npart[i]);
      Npart_snap += header1.npart[i];
    }
  
  
  //  Begining with the groups
  
  blksize_pos = 9*sizeof(int)  + 2*4*sizeof(char) + sizeof(header1);
  blksize_vel = 14*sizeof(int) + 3*4*sizeof(char) + sizeof(header1) + 3*Npart_snap*sizeof(float);
  blksize_ids = 19*sizeof(int) + 4*4*sizeof(char) + sizeof(header1) + 2*3*Npart_snap*sizeof(float);
  
  fseek(fp_pos,blksize_pos,SEEK_SET);
  fseek(fp_vel,blksize_vel,SEEK_SET);
  fseek(fp_ids,blksize_ids,SEEK_SET);

  for(i=0; i<Npart_snap ;i++)   
    {
      
      fread(&pos[0],sizeof(float),3,fp_pos);
      fread(&vel[0],sizeof(float),3,fp_vel);
      fread(&id,sizeof(int),1,fp_ids);

      Part[id].pos[0] = pos[0];
      Part[id].pos[1] = pos[1];
      Part[id].pos[2] = pos[2];
      
      Part[id].vel[0] = vel[0];
      Part[id].vel[1] = vel[1];
      Part[id].vel[2] = vel[2];
      
      Part[id].id = id;
      
      global_acum++;
    }
  
  fclose(fp_pos);
  fclose(fp_vel);
  fclose(fp_ids);
  
  FILE *out;
  out = fopen( "out.dat", "w" );
  for(i=0; i<Npart_snap ;i+=10)   
    fprintf( out, "%1.5e\t%1.5e\t%1.5e\n", Part[i].pos[0], Part[i].pos[1], Part[i].pos[2] );
  
  fclose( out );
  
  
  printf("=====================================================\n");
  printf("   *-* End of reading from gadget file %s, %d \n",buf, global_acum);
  printf("=====================================================\n");
          
  return 0;  
  
}
