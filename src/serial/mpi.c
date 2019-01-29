
/* Code taken from LAAMPS github repo: */
/* -----------------------------------------------------------------------
   LAMMPS 2003 (July 31) - Molecular Dynamics Simulator
   Sandia National Laboratories, www.cs.sandia.gov/~sjplimp/lammps.html
   Steve Plimpton, sjplimp@sandia.gov
   Copyright (2003) Sandia Corporation.  Under the terms of Contract
   DE-AC04-94AL85000 with Sandia Corporation, the U.S. Government retains
   certain rights in this software.  This software is distributed under
   the GNU General Public License.
   See the README file in the top-level LAMMPS directory.
------------------------------------------------------------------------ */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/time.h>
#include <mpi.h>


/* data structure for double/int */

struct _mpi_double_int {
  double value;
  int proc;
};
typedef struct _mpi_double_int double_int;

/* extra MPI_Datatypes registered by MPI_Type_contiguous */

#define MAXEXTRA_DATATYPE 16

int nextra_datatype;
MPI_Datatype *ptr_datatype[MAXEXTRA_DATATYPE];
int index_datatype[MAXEXTRA_DATATYPE];
int size_datatype[MAXEXTRA_DATATYPE];

/* ---------------------------------------------------------------------- */

/* include sizes of user defined datatypes, stored in extra lists */

static int stubtypesize(MPI_Datatype datatype)
{
  if (datatype == MPI_INT)             return sizeof(int);
  else if (datatype == MPI_FLOAT)      return sizeof(float);
  else if (datatype == MPI_DOUBLE)     return sizeof(double);
  else if (datatype == MPI_CHAR)       return sizeof(char);
  else if (datatype == MPI_BYTE)       return sizeof(char);
  else if (datatype == MPI_LONG)       return sizeof(long);
  else if (datatype == MPI_LONG_LONG)  return sizeof(uint64_t);
  else if (datatype == MPI_DOUBLE_INT) return sizeof(double_int);
  else {
    int i;
    for (i = 0; i < nextra_datatype; i++)
      if (datatype == index_datatype[i]) return size_datatype[i];
  }
  return 0;
}

/* ---------------------------------------------------------------------- */


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

int MPI_Finalize()
{
  if (_mpi_is_initialized == 0) {
    printf("MPI Stub WARNING: MPI not yet initialized\n");
    return 1;
  }
  if (_mpi_is_initialized < 0) {
    printf("MPI Stub WARNING: MPI already finalized\n");
    return 1;
  }
  _mpi_is_initialized = -1;
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

