/*
 * HW1: Dynamic Memory Allcoation
 * File: Executor.c
 * Developed by: Nik Torraca
 */

#include <stdio.h>
#include <stdlib.h>
#include "Executor.h"

float get_running_ratio()
{
    int maxPrimeCount = 0;
    //int maxCountIteration = 0;
    float ratioSum = 0;
    int arraySize;

    int totalIterations = random_in_range(50, 99);
    printf("[Executor]: Number of iterations is: %d\n", totalIterations);

    for(int i = 0; i < totalIterations; i++)
    {
        arraySize = random_in_range(100, 149);

        int *array = malloc(arraySize * sizeof(int));
        for(int i = 0; i < arraySize; i++)
        {
            array[i] = random_in_range(50, 199);
        }
    
    int newPrimeCount = get_prime_count(array, arraySize);

    if(newPrimeCount > maxPrimeCount)
        maxPrimeCount = newPrimeCount;
    float ratio = newPrimeCount/(arraySize-newPrimeCount);
    ratioSum += ratio;

    free(array);
    }

    return (ratioSum/arraySize);
}

int random_in_range(int lower_bound, int upper_bound)
{
    return ((rand() % (upper_bound - lower_bound)) + lower_bound);
}

int get_prime_count(int *array, int arraySize)
{
    int flag = 0;
    int primeCount = 0;
    for(int i = 0; i < arraySize; i++)
    {
        int number = array[i];
        
        for(int j = 2; j <= number/2; ++j)
        {
            if(number % j == 0)
                flag = 1;
        }
        if(0 == flag)
        {
            primeCount += 1;
        }
    } 

    return primeCount;
}
