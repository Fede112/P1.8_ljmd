#ifndef MDBC_H
#define MDBS_H
/* helper function: apply minimum image convention */
//double pbc(double x, const double boxby2);
extern inline double pbc(double x, const double boxby2)
{
    while (x >  boxby2) x -= 2.0*boxby2;
    while (x < -boxby2) x += 2.0*boxby2;
    return x;
}

#endif // MDBS_H
