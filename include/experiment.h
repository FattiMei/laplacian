#ifndef __EXPERIMENT_H__
#define __EXPERIMENT_H__


void residual(void (*action)(const float x[], float y[], int n), const float b[], const float x[], float r[], int n);
void error(const float xe[], const float x[], float e[], int n);
void setup(void (*action)(const float x[], float y[], int n), float xe[], float b[], int n);
float norm(const float [], int n);


#endif
