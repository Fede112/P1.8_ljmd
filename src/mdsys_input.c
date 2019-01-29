#include <stdlib.h>

#include "mdsys_input.h"
#include "mdsys_struct.h"
#include "mdsys_util.h"


/* generic file- or pathname buffer length */
#define BLEN 200

int get_a_line(FILE *fp, char *buf)
{
    char tmp[BLEN], *ptr;

    /* read a line and cut of comments and blanks */
    if (fgets(tmp,BLEN,fp)) {
        int i;

        ptr=strchr(tmp,'#');
        if (ptr) *ptr= '\0';
        i=strlen(tmp); --i;
        while(isspace(tmp[i])) {
            tmp[i]='\0';
            --i;
        }
        ptr=tmp;
        while(isspace(*ptr)) {++ptr;}
        i=strlen(ptr);
        strcpy(buf,tmp);
        return 0;
    } else {
        perror("problem reading input");
        return -1;
    }
    return 0;
}

/*add comment*/
int input_param( mdsys_t *sys, char* inputfile, char *restfile, char *trajfile, char *ergfile, char *line, int *nprint)
{
    FILE *fin;
    fin=fopen(inputfile,"r");
    /* read input file */
    if(get_a_line(fin,line)) return 1;
    sys->natoms=atoi(line);
    if(get_a_line(fin,line)) return 1;
    sys->mass=atof(line);
    if(get_a_line(fin,line)) return 1;
    sys->epsilon=atof(line);
    if(get_a_line(fin,line)) return 1;
    sys->sigma=atof(line);
    if(get_a_line(fin,line)) return 1;
    sys->rcut=atof(line);
    if(get_a_line(fin,line)) return 1;
    sys->box=atof(line);
    if(get_a_line(fin,restfile)) return 1;
    if(get_a_line(fin,trajfile)) return 1;
    if(get_a_line(fin,ergfile)) return 1;
    if(get_a_line(fin,line)) return 1;
    sys->nsteps=atoi(line);
    if(get_a_line(fin,line)) return 1;
    sys->dt=atof(line);
    if(get_a_line(fin,line)) return 1;
    *nprint=atoi(line);
    fclose(fin);
    
    return 0;
	
}


/*add comment*/
int read_data (char *restfile, mdsys_t *sys)
{
    /* read restart */
    FILE *fp;
    int i;
    fp=fopen(restfile,"r");
    if(fp) {
        for (i=0; i<sys->natoms; ++i) {
            fscanf(fp,"%lf%lf%lf",sys->rx+i, sys->ry+i, sys->rz+i);
        }
        for (i=0; i<sys->natoms; ++i) {
            fscanf(fp,"%lf%lf%lf",sys->vx+i, sys->vy+i, sys->vz+i);
        }
        fclose(fp);
        azzero(sys->fx, sys->natoms);
        azzero(sys->fy, sys->natoms);
        azzero(sys->fz, sys->natoms);
    } 
    else {
        perror("cannot read restart file");
        return 3;
        }
    return 1;
}
	
	

