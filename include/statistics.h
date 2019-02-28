//
/// Basic statistics library.  Currently only calculates the mean and standard deviation.
// Created by John J. Hritz on 2/8/2019.
//

#include <math.h>

#ifndef LETSROBOTDCMOTORS_STATISTICS_H
#define LETSROBOTDCMOTORS_STATISTICS_H

float mean(int* data, int n);
float mean(float* data, int n);

float stdev(int* data, int n);
float stdev(float* data, int n);

#endif //LETSROBOTDCMOTORS_STATISTICS_H
