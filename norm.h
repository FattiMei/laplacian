#ifndef __NORM_H__
#define __NORM_H__


#include "config.h"


double norm              (const float x[], int n);
double norm_kahan        (const float x[], int n);
double norm_ordered      (      float x[], int n);
double norm_kahan_ordered(      float x[], int n);


#endif
