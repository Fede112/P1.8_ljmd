#ifndef MDMPI_H
#define MDMPI_H

#include "mpi.h"
#include "mdsys_struct.h"

void mdsys_mpi_init(mdsys_t *sys);
void mdsys_mpi_finalize(mdsys_t *sys);

#endif // MDMPI_H