#include "mdsys_mpi.h"
#include <stdio.h>

void mdsys_mpi_init(mdsys_t *sys)
{
    MPI_Initialized(&(sys->initialized));
    sys->rank = 113;

    printf("sys-initialized: %d\n", sys->initialized);
    if (sys->initialized)
    {
        printf("HERE!\n");
        printf("sys-rank: %d\n", sys->rank);
        MPI_Init();
        MPI_Comm_size(MPI_COMM_WORLD, &(sys->nproc));
        MPI_Comm_rank(MPI_COMM_WORLD, &(sys->rank));
    }
    return;
}


void mdsys_mpi_finalize(mdsys_t *sys)
{
	MPI_Finalized(&(sys->finalized));
    if (!(sys->finalized))
    {
        MPI_Finalize();
    }
	return;
}