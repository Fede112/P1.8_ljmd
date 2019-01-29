
#include <stdlib.h> 
#include <string.h> 

#include "mdsys_struct.h"
#include "mdsys_input.h"

#define BLEN 200

int main(int argc, char **argv) 
{
	
	int ok_counter=0;
	int natoms, nsteps, nprint1;
	double mass, epsilon, sigma, rcut, box, dt;

	mdsys_t sys;
	int nprint;
	char restfile[BLEN], trajfile[BLEN], ergfile[BLEN], line[BLEN];
	
	input_param(&sys, restfile, trajfile, ergfile, line, &nprint);
	
	natoms=108; nsteps=10000; nprint1=100;
	mass=39.948; epsilon=0.2379; sigma=3.405; rcut=8.5; box=17.1580; dt=5.0;
	
	
	printf("Testing input() ... \n");    
	
	if (sys.natoms==natoms) ok_counter++;
	else printf("NATOMS reading test failed!\n");
	
	if (sys.mass==mass) ok_counter++;
	else printf("MASS reading test failed!\n");

	if (sys.epsilon==epsilon) ok_counter++;
	else printf("EPSILON reading test failed!\n");

	if (sys.sigma==sigma) ok_counter++;
	else printf("SIGMA reading test failed!\n");
	
	if (sys.rcut==rcut) ok_counter++;
	else printf("RCUT reading test failed!\n");
    
	if (sys.box==box) ok_counter++;
	else printf("BOX LENGTH testreading failed!\n");

//	restfile1[200]="./check/argon_108.rest"; 
	if(!strcmp(restfile,"./test/check/argon_108.rest")) ok_counter++;
	else printf("Restart FILE failed!\n");

//	restfile1[200]="./check/argon_108.rest"; 
	if(!strcmp(trajfile,"./test/check/argon_108.xyz")) ok_counter++;
	else printf("Trajectory FILE failed!\n");

//	restfile1[200]="./check/argon_108.rest"; 
	if(!strcmp(ergfile,"./test/check/argon_108.dat")) ok_counter++;
	else printf("Energies FILE failed!\n");
	
	if (sys.nsteps==nsteps) ok_counter++;
	else printf("# md STEPS test reading failed!\n");
    
	if (sys.dt==dt) ok_counter++;
	else printf("md TIME STEP test reading failed!\n");
    
	if (nprint1==nprint) ok_counter++;
	else printf("output PRINT FREQ test reading failed!\n");

	if(ok_counter<12)
		printf("The other %d variables PASSED.\n Input test: FAILED!\n", ok_counter);
	else
		printf("Input test: PASSED!\n");

}	    
