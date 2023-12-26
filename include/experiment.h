#ifndef __EXPERIMENT_H__
#define __EXPERIMENT_H__


void residual(const float b[], const float x[], float r[], int n);
void error(const float xe[], const float x[], float e[], int n);
void setup(float xe[], float b[], int n);


#endif
