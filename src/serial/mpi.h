#include <stdlib.h>

/* Dummy defs for MPI stubs */

#define MPI_COMM_WORLD 0

#define MPI_SUCCESS   0
#define MPI_ERR_ARG  -1

#define MPI_INT 1
#define MPI_FLOAT 2
#define MPI_DOUBLE 3
#define MPI_CHAR 4
#define MPI_BYTE 5
#define MPI_LONG 6
#define MPI_LONG_LONG 7
#define MPI_DOUBLE_INT 8

#define MPI_SUM 1
#define MPI_MAX 2
#define MPI_MIN 3
#define MPI_MAXLOC 4
#define MPI_MINLOC 5
#define MPI_LOR 6

#define MPI_UNDEFINED -1
#define MPI_COMM_NULL -1
#define MPI_GROUP_EMPTY -1

#define MPI_ANY_SOURCE -1
#define MPI_STATUS_IGNORE NULL

#define MPI_Comm int
#define MPI_Request int
#define MPI_Datatype int
#define MPI_Op int
#define MPI_Fint int
#define MPI_Group int
#define MPI_Offset long

#define MPI_IN_PLACE NULL

#define MPI_MAX_PROCESSOR_NAME 128


int MPI_Init(int *argc, char ***argv);
int MPI_Initialized(int *flag);
int MPI_Finalized(int *flag);
int MPI_Finalize();
int MPI_Comm_rank(MPI_Comm comm, int *me);
int MPI_Comm_size(MPI_Comm comm, int *nprocs);
int MPI_Bcast(void *buf, int count, MPI_Datatype datatype,
              int root, MPI_Comm comm);
int MPI_Reduce(void *sendbuf, void *recvbuf, int count,
   MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm);