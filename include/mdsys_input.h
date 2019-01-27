/* mdsys input Header Files */
#ifndef MDIN_H
#define MDIN_H

#include <stdio.h> 
#include <string.h>
#include <ctype.h> // for isspace()

#include "mdsys_struct.h"

/* helper function: read a line and then return
   the first string with whitespace stripped off */
int get_a_line(FILE *fp, char *buf);

/*add commet*/
int input_param( mdsys_t *sys, char *restfile, char *trajfile, char *ergfile, char *line, int *nprint);


/*add comment*/
int read_data (FILE *fp, char *restfile, mdsys_t *sys);


#endif // MDIN_H
