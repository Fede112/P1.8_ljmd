#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include "mdsys_force.h"
#include "mdsys_struct.h"

// static const double kboltz=0.0019872067;     /* boltzman constant in kcal/mol/K */
// static const double mvsq2e=2390.05736153349; /* m*v^2 in kcal/mol */

int main(int argc, char const *argv[])
{
	printf("Testing force() ...\n");
	double eps_tole = 10e-8;
	double scale;
    // double *rx, *ry, *rz;
    // double *vx, *vy, *vz;
	mdsys_t sys;
	sys.natoms = 2;
	sys.mass = 39.948;
	sys.sigma = 3.405;
	sys.epsilon = 0.2379;
	sys.rcut = 4;
	sys.box = 16;


	sys.rx = (double *)malloc(sys.natoms*sizeof(double));
	sys.ry = (double *)malloc(sys.natoms*sizeof(double));
	sys.rz = (double *)malloc(sys.natoms*sizeof(double));
	sys.fx = (double *)malloc(sys.natoms*sizeof(double));
	sys.fy = (double *)malloc(sys.natoms*sizeof(double));
	sys.fz = (double *)malloc(sys.natoms*sizeof(double));



	/////////////////////////////////////////////////////////////////////////////////
	// Particle_Distance12 = 2 < sys.rcut
	// 1st particle: (0,0,0)
	// 2nd particle: direction (1,1,1)*scale

	scale = 2./sqrt(3);
	sys.rx[0] = 0; sys.ry[0] = 0; sys.rz[0] = 0; // (0,0,0)
	sys.rx[1] = scale; sys.ry[1] = scale; sys.rz[1] = scale; // (1,1,1)*(2/sqrt(3))

	force(&sys);

	// printf("Da esto: %lf\n", sys.fx[0] );
	if(	(fabs(sys.fx[0] - -1914.6104249) > 1914.6104249*eps_tole)  ){exit(1);}
	if(	(fabs(sys.fy[0] - -1914.6104249) > 1914.6104249*eps_tole)  ){exit(1);}
	if(	(fabs(sys.fz[0] - -1914.6104249) > 1914.6104249*eps_tole)  ){exit(1);}
	if(	(fabs(sys.fx[1] - 1914.6104249) > 1914.6104249*eps_tole)  ){exit(1);}
	if(	(fabs(sys.fy[1] - 1914.6104249) > 1914.6104249*eps_tole)  ){exit(1);}
	if(	(fabs(sys.fz[1] - 1914.6104249) > 1914.6104249*eps_tole)  ){exit(1);}

	/////////////////////////////////////////////////////////////////////////////////
	// Particle_Distance12 = 5 > sys.rcut
	// 1st particle: (0,0,0)
	// 2nd particle: direction (1,1,1)*scale

	scale = 5./sqrt(3);
	sys.rx[0] = 0; sys.ry[0] = 0; sys.rz[0] = 0; // (0,0,0)
	sys.rx[1] = -scale; sys.ry[1] = -scale; sys.rz[1] = scale; // (-1,-1,1)

	force(&sys);
	
	if(	(fabs(sys.fx[0] - 0) > eps_tole)  ){exit(1);}
	if(	(fabs(sys.fy[0] - 0) > eps_tole)  ){exit(1);}
	if(	(fabs(sys.fz[0] - 0) > eps_tole)  ){exit(1);}
	if(	(fabs(sys.fx[1] - 0) > eps_tole)  ){exit(1);}
	if(	(fabs(sys.fy[1] - 0) > eps_tole)  ){exit(1);}
	if(	(fabs(sys.fz[1] - 0) > eps_tole)  ){exit(1);}

	/////////////////////////////////////////////////////////////////////////////////
	// Particle_Distance12 = 5 > boxdist 
	// Testing pbc while also
	// 1st particle: (0,0,0)
	// 2nd particle: direction (1,-1,0)*scale


	scale = 20.0/sqrt(2);
	sys.rx[0] = 0; sys.ry[0] = 0; sys.rz[0] = 0; // (0,0,0)
	sys.rx[1] = scale; sys.ry[1] = -scale; sys.rz[1] = 0; // (-1,-1,0)
	// scale = sys.box*1.9;
	// sys.rx[0] = 0; sys.ry[0] = 0; sys.rz[0] = 0; // (0,0,0)
	// sys.rx[1] = scale; sys.ry[1] = 0; sys.rz[1] = 0; // (-1,-1,0)

	force(&sys);

	if(	(fabs(sys.fx[0] - 61.6889064) > 61.6889064*eps_tole)  ){exit(1);}
	if(	(fabs(sys.fy[0] - -61.6889064) > 61.6889064*eps_tole)  ){exit(1);}
	if(	(fabs(sys.fz[0] - 0) > 61.6889064*eps_tole)  ){exit(1);}
	if(	(fabs(sys.fx[1] - -61.6889064) > 61.6889064*eps_tole)  ){exit(1);}
	if(	(fabs(sys.fy[1] - 61.6889064) > 61.6889064*eps_tole)  ){exit(1);}
	if(	(fabs(sys.fz[1] - 0) > 61.6889064*eps_tole)  ){exit(1);}

	printf("force() test: PASSED!\n");

	return 0;
}
