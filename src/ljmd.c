/* 
 * simple lennard-jones potential MD code with velocity verlet.
 * units: Length=Angstrom, Mass=amu; Energy=kcal
 *
 * baseline c version.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

#include "mdsys_struct.h"
#include "mdsys_input.h"
#include "mdsys_output.h"
#include "mdsys_bc.h"
#include "mdsys_force.h"
#include "mdsys_util.h"
#include "mdsys_velverlet.h"

// #include "mpi.h"

#include "mdsys_mpi.h"

/* generic file- or pathname buffer length */
#define BLEN 200

/* a few physical constants */
// const double kboltz=0.0019872067;     /* boltzman constant in kcal/mol/K */
// const double mvsq2e=2390.05736153349; /* m*v^2 in kcal/mol */

/* main */
int main(int argc, char **argv) 
{
    int nprint;
    char restfile[BLEN], trajfile[BLEN], ergfile[BLEN], line[BLEN];
    FILE *fp,*traj,*erg;
    mdsys_t sys;

    mdsys_mpi_init(&sys);

    if (input_param(&sys,restfile, trajfile,ergfile,line, &nprint)==1)
		return 1;

    /* allocate memory */
    sys.rx=(double *)malloc(sys.natoms*sizeof(double));
    sys.ry=(double *)malloc(sys.natoms*sizeof(double));
    sys.rz=(double *)malloc(sys.natoms*sizeof(double));
    sys.vx=(double *)malloc(sys.natoms*sizeof(double));
    sys.vy=(double *)malloc(sys.natoms*sizeof(double));
    sys.vz=(double *)malloc(sys.natoms*sizeof(double));
    sys.fx=(double *)malloc(sys.natoms*sizeof(double));
    sys.fy=(double *)malloc(sys.natoms*sizeof(double));
    sys.fz=(double *)malloc(sys.natoms*sizeof(double));
    sys.b_fx=(double *)malloc(sys.natoms*sizeof(double));
    sys.b_fy=(double *)malloc(sys.natoms*sizeof(double));
    sys.b_fz=(double *)malloc(sys.natoms*sizeof(double));

    if (!sys.rank)
    {	
    	if (read_data (fp, restfile, &sys)== 3) return 3;
    }

    /* initialize forces and energies.*/
    sys.nfi=0;
    force(&sys);
    ekin(&sys);
    
    if (!sys.rank)
    {
        erg=fopen(ergfile,"w");
        traj=fopen(trajfile,"w");

        printf("Starting simulation with %d atoms for %d steps.\n",sys.natoms, sys.nsteps);
        printf("     NFI            TEMP            EKIN                 EPOT              ETOT\n");
        output(&sys, erg, traj);
    }

    /**************************************************/
    /* main MD loop */
    for(sys.nfi=1; sys.nfi <= sys.nsteps; ++sys.nfi) {

        /* write output, if requested */
        if ((sys.nfi % nprint) == 0)
            if (!sys.rank)
            {
                output(&sys, erg, traj);
            }

        /* propagate system and recompute energies */
        velverlet_1(&sys);
        force(&sys);
        velverlet_2(&sys);
        ekin(&sys);
    }
    /**************************************************/
    

    mdsys_mpi_finalize(&sys);

    /* clean up: close files, free memory */
    printf("Simulation Done.\n");
    
    if (!sys.rank)
    {
        fclose(erg);
        fclose(traj);
    }

    free(sys.rx);
    free(sys.ry);
    free(sys.rz);
    free(sys.vx);
    free(sys.vy);
    free(sys.vz);
    free(sys.fx);
    free(sys.fy);
    free(sys.fz);

    return 0;
}

