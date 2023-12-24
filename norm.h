#ifndef __NORM_H__
#define __NORM_H__


#include "config.h"


double norm              (const Real x[], int n);
double norm_kahan        (const Real x[], int n);
double norm_ordered      (      Real x[], int n);
double norm_kahan_ordered(      Real x[], int n);


#endif
