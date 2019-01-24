#ifndef MDFORCE_H
#define MDFORECE_H

#include "mdsys_struct.h"

/* a few physical constants */
extern const double kboltz;     /* boltzman constant in kcal/mol/K */
extern const double mvsq2e; /* m*v^2 in kcal/mol */

/* compute forces */
void force(mdsys_t *sys); 

/* compute kinetic energy */
void ekin(mdsys_t *sys);


#endif // MDFORECE_H