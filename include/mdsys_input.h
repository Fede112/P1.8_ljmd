/* mdsys input Header Files */
#ifndef MDIN_H
#define MDIN_H

#include <stdio.h> 
#include <string.h>
#include <ctype.h> // for isspace()

/* helper function: read a line and then return
   the first string with whitespace stripped off */
int get_a_line(FILE *fp, char *buf);

#endif // MDIN_H