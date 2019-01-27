#include "mdsys_mpi.h"

void mdsys_mpi_init(mdsys_t *sys)
{
    MPI_Initialized(&(sys->initialized));
    if (!sys->initialized)
    {
        MPI_Init(NULL, NULL);
        MPI_Comm_size(MPI_COMM_WORLD, &(sys->nproc));
        MPI_Comm_rank( MPI_COMM_WORLD, &(sys->rank));
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