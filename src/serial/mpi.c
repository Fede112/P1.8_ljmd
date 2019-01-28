#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/time.h>
#include <mpi.h>


static int _mpi_is_initialized=0;


/* ---------------------------------------------------------------------- */
/* MPI Functions */
/* ---------------------------------------------------------------------- */

int MPI_Init(int *argc, char ***argv)
{
  if (_mpi_is_initialized > 0) {
    // printf("MPI Stub WARNING: MPI already initialized\n");
    return 1;
  }
  if (_mpi_is_initialized < 0) {
    // printf("MPI Stub WARNING: MPI already finalized\n");
    return 1;
  }
  _mpi_is_initialized = 1;
  return 0;
}

/* ---------------------------------------------------------------------- */

int MPI_Initialized(int *flag)
{
  *flag = (_mpi_is_initialized > 0) ? 1 : 0;
  return 0;
}

/* ---------------------------------------------------------------------- */

int MPI_Finalized(int *flag)
{
  *flag = (_mpi_is_initialized < 0) ? 1 : 0;
  return 0;
}

/* ---------------------------------------------------------------------- */

int MPI_Comm_rank(MPI_Comm comm, int *me)
{
  *me = 0;
  return 0;
}

/* ---------------------------------------------------------------------- */

int MPI_Comm_size(MPI_Comm comm, int *nprocs)
{
  *nprocs = 1;
  return 0;
}


/* ---------------------------------------------------------------------- */

int MPI_Bcast(void *buf, int count, MPI_Datatype datatype,
              int root, MPI_Comm comm) {return 0;}

/* ---------------------------------------------------------------------- */

/* copy values from data1 to data2 */

int MPI_Reduce(void *sendbuf, void *recvbuf, int count,
                   MPI_Datatype datatype, MPI_Op op,
                   int root, MPI_Comm comm)
{
  int n = count * stubtypesize(datatype);

  if (sendbuf == MPI_IN_PLACE || recvbuf == MPI_IN_PLACE) return 0;
  memcpy(recvbuf,sendbuf,n);
  return 0;
}


/* ---------------------------------------------------------------------- */

