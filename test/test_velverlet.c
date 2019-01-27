#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include "mdsys_velverlet.h"
#include "mdsys_struct.h"



const double mvsq2e=2390.05736153349; /* m*v^2 in kcal/mol */

int main(int argc, char const *argv[])
{
	long double eps_tole = 10e-7; // relative tolerance
	double scale;
    // double *rx, *ry, *rz;
    // double *vx, *vy, *vz;
	mdsys_t sys;
	sys.natoms = 3;
	sys.mass = 39.948;
	sys.dt = 5.0;

	sys.rx = (double *)malloc(sys.natoms*sizeof(double));
	sys.ry = (double *)malloc(sys.natoms*sizeof(double));
	sys.rz = (double *)malloc(sys.natoms*sizeof(double));
	sys.vx = (double *)malloc(sys.natoms*sizeof(double));
    sys.vy = (double *)malloc(sys.natoms*sizeof(double));
    sys.vz = (double *)malloc(sys.natoms*sizeof(double));
	sys.fx = (double *)malloc(sys.natoms*sizeof(double));
	sys.fy = (double *)malloc(sys.natoms*sizeof(double));
	sys.fz = (double *)malloc(sys.natoms*sizeof(double));


	/////////////////////////////////////////////////////////////////////////////////
	// Three different particles:
	// 1st particle: force parallel to velocity
	// 2nd particle: force orthogonal to velocity
	// 3rd particle: force zero, velocity != 0.

	// velocities of the three particles are are L.I. between them 
	// The initial positions were chosen randomly to cover different distances and positions with respect to (0,0,0)

	printf("Testing velverlet_1() ...\n");
	
	sys.rx[0] = 1.0; sys.ry[0] = 1.0; sys.rz[0] = 1.0; // (1,1,1)
	sys.rx[1] = -20.1; sys.ry[1] = 10.7; sys.rz[1] = -10.3; // (-20.1, 10.7, -10.3)
	sys.rx[2] = 100.8; sys.ry[2] = -200.5; sys.rz[2] = 123.2; // (100.8,-200.5,123.2)
	
	sys.vx[0] = 10e-3; sys.vy[0] = 10e-3; sys.vz[0] = 10e-3; // cte*(1,1,1)
	sys.vx[1] = -10e-4; sys.vy[1] = -10e-4; sys.vz[1] = 10e-4; // cte*(-1,-1,1)
	sys.vx[2] = 10e-5; sys.vy[2] = -10e-5; sys.vz[2] = 0; // cte*(1,-1,0)
	
	sys.fx[0] = 10; sys.fy[0] = 10; sys.fz[0] = 10; // cte*(1,1,1)
	sys.fx[1] = 40; sys.fy[1] = -60; sys.fz[1] = 20; // cte*(2,-3,1)
	sys.fx[2] = 0; sys.fy[2] = 0; sys.fz[2] = 0; // (0,0,0)

	velverlet_1(&sys);

	if(	(fabs(sys.rx[0] - 1.0513092020) > 1.0513092020*eps_tole)  ){exit(1);}
	if(	(fabs(sys.ry[0] - 1.0513092020) > 1.0513092020*eps_tole)  ){exit(1);}
	if(	(fabs(sys.rz[0] - 1.0513092020) > 1.0513092020*eps_tole)  ){exit(1);}
	if(	(fabs(sys.vx[0] - 0.0102618404) > 0.0102618404*eps_tole)  ){exit(1);}
	if(	(fabs(sys.vy[0] - 0.0102618404) > 0.0102618404*eps_tole)  ){exit(1);}
	if(	(fabs(sys.vz[0] - 0.0102618404) > 0.0102618404*eps_tole)  ){exit(1);}

	if(	(fabs(sys.rx[1] - -20.0997631922) > 20.0997631922*eps_tole)  ){exit(1);}
	if(	(fabs(sys.ry[1] - 10.6871447882) > 10.6871447882*eps_tole)  ){exit(1);}
	if(	(fabs(sys.rz[1] - -10.2923815961) > 10.2923815961*eps_tole)  ){exit(1);}
	if(	(fabs(sys.vx[1] - 0.0000473616) > 0.0000473616*eps_tole)  ){exit(1);}
	if(	(fabs(sys.vy[1] - -0.0025710424) > 0.0025710424*eps_tole)  ){exit(1);}
	if(	(fabs(sys.vz[1] - 0.0015236808) > 0.0015236808*eps_tole)  ){exit(1);}

	if(	(fabs(sys.rx[2] - 100.8005000000) > 100.8005000000*eps_tole)  ){exit(1);}
	if(	(fabs(sys.ry[2] - -200.500500000) > 200.500500000*eps_tole)  ){exit(1);}
	if(	(fabs(sys.rz[2] - 123.200000000) > 123.200000000*eps_tole)  ){exit(1);}
	if(	(fabs(sys.vx[2] - 0.0001000000) > 0.0001000000*eps_tole)  ){exit(1);}
	if(	(fabs(sys.vy[2] - -0.0001000000) > 0.0001000000*eps_tole)  ){exit(1);}
	if(	(fabs(sys.vz[2] - 0.0) > eps_tole)  ){exit(1);}

	printf("velverlet_1() test completed.\n");

	printf("Testing velverlet_2() ...\n");

	// same configuration as velverlet_1()
	sys.vx[0] = 10e-3; sys.vy[0] = 10e-3; sys.vz[0] = 10e-3; // cte*(1,1,1)
	sys.vx[1] = -10e-4; sys.vy[1] = -10e-4; sys.vz[1] = 10e-4; // cte*(-1,-1,1)
	sys.vx[2] = 10e-5; sys.vy[2] = -10e-5; sys.vz[2] = 0; // cte*(1,-1,0)

	sys.fx[0] = 10; sys.fy[0] = 10; sys.fz[0] = 10; // cte*(1,1,1)
	sys.fx[1] = 40; sys.fy[1] = -60; sys.fz[1] = 20; // cte*(2,-3,1)
	sys.fx[2] = 0; sys.fy[2] = 0; sys.fz[2] = 0; // (0,0,0)

	velverlet_2(&sys);

	if(	(fabs(sys.vx[0] - 0.0102618404) > 0.0102618404*eps_tole)  ){exit(1);}
	if(	(fabs(sys.vy[0] - 0.0102618404) > 0.0102618404*eps_tole)  ){exit(1);}
	if(	(fabs(sys.vz[0] - 0.0102618404) > 0.0102618404*eps_tole)  ){exit(1);}

	if(	(fabs(sys.vx[1] - 0.0000473616) > 0.0000473616*eps_tole)  ){exit(1);}
	if(	(fabs(sys.vy[1] - -0.0025710424) > 0.0025710424*eps_tole)  ){exit(1);}
	if(	(fabs(sys.vz[1] - 0.0015236808) > 0.0015236808*eps_tole)  ){exit(1);}

	if(	(fabs(sys.vx[2] - 0.0001000000) > 0.0001000000*eps_tole)  ){exit(1);}
	if(	(fabs(sys.vy[2] - -0.0001000000) > 0.0001000000*eps_tole)  ){exit(1);}
	if(	(fabs(sys.vz[2] - 0.0) > eps_tole)  ){exit(1);}


	printf("velverlet_2() test completed.\n");



	return 0;
}
