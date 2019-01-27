#ifndef MDSTRUCT_H
#define MDSTRUCT_H

/* structure to hold the complete information 
 * about the MD system */
struct _mdsys {
    int natoms,nfi,nsteps;
    double dt, mass, epsilon, sigma, box, rcut;
    double ekin, epot, temp;
    double *rx, *ry, *rz;
    double *vx, *vy, *vz;
    double *fx, *fy, *fz;
    // MPI variables
    double *b_fx, *b_fy, *b_fz; // buffer needed to calculate force
    int initialized;
    int finalized;
    int rank; // world_rank
    int nproc; // world_size
};
typedef struct _mdsys mdsys_t;

#endif // MDSTRUCT_H