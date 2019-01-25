#ifndef MDVELVERLET_H
#define MDVELVERLET_H

#include "mdsys_struct.h"

extern const double mvsq2e; /* m*v^2 in kcal/mol */

/*First half of VEL VERLET*/
void velverlet_1(mdsys_t *sys);

/*Second half of VEL VERLET*/
void velverlet_2(mdsys_t *sys);

#endif // MDVELVERLET_H
