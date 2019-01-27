

#include <stdio.h>
#include <stdlib.h> 
#include <time.h> 

#include "mdsys_struct.h"
#include "mdsys_force.h"

int main()
{

	//const double kboltz=0.0019872067;     /* boltzman constant in kcal/mol/K */
//	const double mvsq2e=2390.05736153349; /* m*v^2 in kcal/mol */
 	srand(time(NULL));
 	const int natoms=11;
 	double mass = (0.01*(rand()%100))+(0.001*(rand()%1000));
	double kin, temp;
	double vx[natoms],vy[natoms],vz[natoms]; 
	
	mdsys_t sys;
	sys.natoms = natoms;
	sys.mass = mass;
    sys.vx=(double *)malloc(sys.natoms*sizeof(double));
    sys.vy=(double *)malloc(sys.natoms*sizeof(double));
    sys.vz=(double *)malloc(sys.natoms*sizeof(double));
    
    for (int i=0; i<natoms; ++i){
    	vx[i]=0.00001*(rand()%100);
    	vy[i]=0.00001*(rand()%100);
    	vz[i]=0.00001*(rand()%100);
    	}
    
	for (int i=0; i<sys.natoms; ++i){
		sys.vx[i] = vx[i];
		sys.vy[i] = vy[i];
		sys.vz[i] = vz[i];
		}
    
    ekin(&sys);	
	
	kin=0.0;    
	printf("Testing ekin() ... \n", kin);    
	for (int i=0; i<natoms; i++){
		kin+=0.5*mass*mvsq2e*(vx[i]*vx[i]+vy[i]*vy[i]+vz[i]*vz[i]);
    	}
//    printf("KIN=%f \n", kin);    
//	printf("SYS.KIN=%f \n\n", sys.ekin);
    temp= 2.0*kin/(3.0*(natoms-1)*kboltz);
         
//    printf("SYS.TEMP=%f \n", sys.temp);
//    printf("TEMP=%f \n\n", temp);
    
    
    if ((sys.temp-temp)<(temp*10e-8) && sys.ekin==kin){ 
    	printf("Kinetic Energy test: PASSED!\n");
    	return 0;
    	}
    else{
	    printf("Kinetic Energy TEST: FAILED!\n");
	    return 1;
	    }
}	    
