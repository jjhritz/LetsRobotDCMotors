//
// Created by John J. Hritz on 2/8/2019.
//


#include "statistics.h"

float mean(int* data, int n)
/**
 * Calculates the mean of a set of integers.
 * @param data Array containing sample set.
 * @param n Number of elements in data.
 * @return The mean of all elements in data
 */
{
    int sum = 0;
    for(int i = 0; i < n; i++)
    {
        sum += data[i];
    }

    return (float)sum/n;
}

float mean(float* data, int n)
/**
 * Calculates the mean of a set of floats.
 * @param data Array containing sample set.
 * @param n Number of elements in data.
 * @return The mean of all elements in data
 */
{
    int sum = 0;
    for(int i = 0; i < n; i++)
    {
        sum += data[i];
    }

    return (float)sum/n;
}

float stdev(int* data, int n)
/**
 * Calculates the standard deviation of a set of integers.
 * @param data Array containing sample set.
 * @param n Number of elements in data.
 * @return The mean of all elements in data
 */
{
    float sum_of_squares = 0;
    float avg = mean(data, n);

    for(int i = 0; i < n; i++)
    {
        sum_of_squares += pow((data[i] - avg),2);
    }

    return sqrtf(sum_of_squares/(n - 1));
}

float stdev(float* data, int n)
/**
 * Calculates the standard deviation of a set of floats.
 * @param data Array containing sample set.
 * @param n Number of elements in data.
 * @return The mean of all elements in data
 */
{
    float sum_of_squares = 0;
    float avg = mean(data, n);

    for(int i = 0; i < n; i++)
    {
        sum_of_squares += pow((data[i] - avg),2);
    }

    return sqrtf(sum_of_squares/(n - 1));
}

