/* Force and energy definition */

#include "math.h"
#include "mdsys_force.h"
#include "mdsys_bc.h"
#include "mdsys_struct.h"
#include "mdsys_util.h"
#include "mdsys_mpi.h"

// #include "mpi.h"


double const kboltz=0.0019872067;     /* boltzman constant in kcal/mol/K */
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

    // MPI_Initialized(&(sys->initialized));
    // if (!sys->initialized)
    // {
    //     MPI_Init(NULL, NULL);
    //     MPI_Comm_size(MPI_COMM_WORLD, &(sys->nproc));
    //     MPI_Comm_rank( MPI_COMM_WORLD, &(sys->rank));
    // }

    mdsys_mpi_init(sys);


    // buffers for mpi
    double b_epot; 
    // b_fx, b_fy, b_fz are malloc outside because it is to expensive to malloc every time force is called


    // Broadcast from rank 0 to other ranks
    MPI_Bcast(sys->rx, sys->natoms, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(sys->ry, sys->natoms, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(sys->rz, sys->natoms, MPI_DOUBLE, 0, MPI_COMM_WORLD);


    double r,ffac;
    double rx,ry,rz;
    int i,j;

    /* zero energy and forces */
    b_epot=0.0;
    sys->epot=0.0;
    // azzero(sys->fx,sys->natoms);
    // azzero(sys->fy,sys->natoms);
    // azzero(sys->fz,sys->natoms);
    azzero(sys->b_fx,sys->natoms);
    azzero(sys->b_fy,sys->natoms);
    azzero(sys->b_fz,sys->natoms);

    // for(i= (sys->natoms) - 1 - sys->rank; i > 0; i-=sys->nproc) 
    // {   
    //     for(j=i+1; j < (sys->natoms); ++j) {
    for(i=sys->rank; i < (sys->natoms) - 1; i+=sys->nproc) 
    {   
        for(j=i+1; j < (sys->natoms); ++j) {
            
            /* get distance between particle i and j */
            rx=pbc(sys->rx[i] - sys->rx[j], 0.5*sys->box);
            ry=pbc(sys->ry[i] - sys->ry[j], 0.5*sys->box);
            rz=pbc(sys->rz[i] - sys->rz[j], 0.5*sys->box);
            r = sqrt(rx*rx + ry*ry + rz*rz);
      
            /* compute force and energy if within cutoff */
            if (r < sys->rcut) {
                ffac = -4.0*sys->epsilon*(-12.0*pow(sys->sigma/r,12.0)/r
                                         +6*pow(sys->sigma/r,6.0)/r);
                
                b_epot += 4.0*sys->epsilon*(pow(sys->sigma/r,12.0)
                                               -pow(sys->sigma/r,6.0));

                sys->b_fx[i] += rx/r*ffac;
                sys->b_fy[i] += ry/r*ffac;
                sys->b_fz[i] += rz/r*ffac;

                sys->b_fx[j] -= rx/r*ffac;
                sys->b_fy[j] -= ry/r*ffac;
                sys->b_fz[j] -= rz/r*ffac;
            }
        }
    }
    MPI_Reduce(sys->b_fx, sys->fx, sys->natoms, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(sys->b_fy, sys->fy, sys->natoms, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(sys->b_fz, sys->fz, sys->natoms, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&b_epot, &sys->epot, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
}


/* compute kinetic energy */
void ekin(mdsys_t *sys)
{   
    int i;

    sys->ekin=0.0;
    for (i=0; i<sys->natoms; ++i) {
        sys->ekin += 0.5*mvsq2e*sys->mass*(sys->vx[i]*sys->vx[i] + sys->vy[i]*sys->vy[i] + sys->vz[i]*sys->vz[i]);
    }
    sys->temp = 2.0*sys->ekin/(3.0*sys->natoms-3.0)/kboltz;
}


