/* Force and energy definition */

#include "math.h"
#include "mdsys_force.h"
#include "mdsys_bc.h"
#include "mdsys_struct.h"
#include "mdsys_util.h"


const double kboltz=0.0019872067;     /* boltzman constant in kcal/mol/K */
const double mvsq2e=2390.05736153349; /* m*v^2 in kcal/mol */



// struct _mdsys {
//     int natoms,nfi,nsteps;
//     double dt, mass, epsilon, sigma, box, rcut;
//     double ekin, epot, temp;
//     double *rx, *ry, *rz;
//     double *vx, *vy, *vz;
//     double *fx, *fy, *fz;
// };
// typedef struct _mdsys mdsys_t;


/* compute forces */
void force(mdsys_t *sys) 
{
    double r1,ffac1;
    double rx1,ry1,rz1;
	double r2,ffac2;
    double rx2,ry2,rz2;
    int i,j;

	double c6, c12, rsq, rcsq;
	c12= 4.0* sys->epsilon* pow(sys->sigma,12.0);
	c6 = 4.0* sys->epsilon* pow(sys->sigma,6.0);
	rcsq = sys->rcut * sys->rcut;

	
    /* zero energy and forces */
    sys->epot=0.0;
    azzero(sys->fx,sys->natoms);
    azzero(sys->fy,sys->natoms);
    azzero(sys->fz,sys->natoms);

	
	for(i=0; i < (sys->natoms); i++) {
	   for(j=0; j < (sys->natoms); j++) {

		if (i==j) continue;
            /* get distance between particle i and j */
			rx1=pbc(sys->rx[i] - sys->rx[j], 0.5*sys->box);
  	        ry1=pbc(sys->ry[i] - sys->ry[j], 0.5*sys->box);
   	        rz1=pbc(sys->rz[i] - sys->rz[j], 0.5*sys->box);
   	        rsq = rx1*rx1 + ry1*ry1 + rz1*rz1;

    	        /* compute force and energy if within cutoff */
			if (rsq < rcsq){
				
				double rsqinv = 1.0/rsq;
				double r6 = rsqinv *rsqinv *rsqinv;
				
				ffac1 = (12.0*c12*r6- 6.0*c6)*r6*rsqinv;
				sys->epot += 0.5*r6* (c12* r6 - c6);
				

//   	            ffac1 = -4.0*sys->epsilon*(-12.0*pow(sys->sigma/r1,12.0)/r1
  // 	            		+6*pow(sys->sigma/r1,6.0)/r1);
	                            
   	            //sys->epot += 0.5*4.0*sys->epsilon*(pow(sys->sigma/r1,12.0)
   	            	//		-pow(sys->sigma/r1,6.0));
                           
 	            sys->fx[i] += rx1*ffac1;	//sys->fx[j] -= rx1*ffac1;
   	            sys->fy[i] += ry1*ffac1;	//sys->fy[j] -= ry1*ffac1;
   	            sys->fz[i] += rz1*ffac1;	//sys->fz[j] -= rz1*ffac1;	
   	        	}
           	}
            


//			if(j!=i&&j!=i+1){
	            /* get distance between particle i and j */
/*    	        rx1=pbc(sys->rx[i] - sys->rx[j], 0.5*sys->box);
    	        ry1=pbc(sys->ry[i] - sys->ry[j], 0.5*sys->box);
    	        rz1=pbc(sys->rz[i] - sys->rz[j], 0.5*sys->box);
    	        r1 = sqrt(rx1*rx1 + ry1*ry1 + rz1*rz1);
    	        
    	        rx2=pbc(sys->rx[i+1] - sys->rx[j], 0.5*sys->box);
    	        ry2=pbc(sys->ry[i+1] - sys->ry[j], 0.5*sys->box);
    	        rz2=pbc(sys->rz[i+1] - sys->rz[j], 0.5*sys->box);
    	        r2 = sqrt(rx2*rx2 + ry2*ry2 + rz2*rz2);
  */  	              
    	        /* compute force and energy if within cutoff */
    /*	        if (r1 < sys->rcut) {
    	            ffac1 = -4.0*sys->epsilon*(-12.0*pow(sys->sigma/r1,12.0)/r1
    	            		+6*pow(sys->sigma/r1,6.0)/r1);
		                            
    	            sys->epot += 0.5*4.0*sys->epsilon*(pow(sys->sigma/r1,12.0)
    	            			-pow(sys->sigma/r1,6.0));
    	                       
    	            sys->fx[i] += rx1/r1*ffac1;
    	            sys->fy[i] += ry1/r1*ffac1;
    	            sys->fz[i] += rz1/r1*ffac1;
    		        }
            
    	        if (r2 < sys->rcut) {
    	        	ffac2 = -4.0*sys->epsilon * (-12.0*pow(sys->sigma/r2,12.0)/r2
		            		+6*pow(sys->sigma/r2,6.0)/r2);
		        	sys->epot += 0.5*4.0*sys->epsilon*(pow(sys->sigma/r2,12.0)
    	            			-pow(sys->sigma/r2,6.0));
					sys->fx[i+1] += rx2/r2*ffac2;
					sys->fy[i+1] += ry2/r2*ffac2;
					sys->fz[i+1] += rz2/r2*ffac2;
    		    		}
    		   		}
            /* particles have no interactions with themselves */
         //   else if (i+1==j){
            
            //=><//
//	        else if (i==j){

	            /* get distance between particle i+1 and j */
	         /* rx2=pbc(sys->rx[i+1] - sys->rx[j], 0.5*sys->box);
	            ry2=pbc(sys->ry[i+1] - sys->ry[j], 0.5*sys->box);
	            rz2=pbc(sys->rz[i+1] - sys->rz[j], 0.5*sys->box);
	            r2 = sqrt(rx2*rx2 + ry2*ry2 + rz2*rz2);
	            */     
	            /* compute force and energy if within cutoff */
	            /*if (r2 < sys->rcut) {
	            	ffac2 = -4.0*sys->epsilon * (-12.0*pow(sys->sigma/r2,12.0)/r2
		            		+6*pow(sys->sigma/r2,6.0)/r2);
		        	sys->epot += 0.5*4.0*sys->epsilon*(pow(sys->sigma/r2,12.0)
	                			-pow(sys->sigma/r2,6.0));
					sys->fx[i+1] += rx2/r2*ffac2;
					sys->fy[i+1] += ry2/r2*ffac2;
					sys->fz[i+1] += rz2/r2*ffac2;
		        	}
		        } */       	
        //}
    }
}


/* compute kinetic energy */
void ekin(mdsys_t *sys)
{   
    int i;

    sys->ekin=0.0;
    for (i=0; i<sys->natoms; i++) {
        sys->ekin += 0.5*mvsq2e*sys->mass*(sys->vx[i]*sys->vx[i] + sys->vy[i]*sys->vy[i] + sys->vz[i]*sys->vz[i]);
//        sys->ekin += 0.5*mvsq2e*sys->mass*(sys->vx[i+1]*sys->vx[i+1] + sys->vy[i+1]*sys->vy[i+1] + sys->vz[i+1]*sys->vz[i+1]);
    }
    sys->temp = 2.0*sys->ekin/(3.0*sys->natoms-3.0)/kboltz;
}


