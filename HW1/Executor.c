/*
 * HW1: Dynamic Memory Allcoation
 * File: Executor.c
 * Developed by: Nik Torraca
 */

#include <stdio.h>
#include <stdlib.h>
#include "Executor.h"
#include <stdbool.h>

float get_running_ratio()
{
    int maxPrimeCount = 0;
    int maxCountIteration = 0;
    float ratioSum = 0;
    int arraySize;

    int totalIterations = random_in_range(50, 99);
    printf("[Executor]: Number of iterations is: %d\n", totalIterations);

    for(int i = 0; i < totalIterations; i++)
    {
        arraySize = random_in_range(100, 144);

        int *array = malloc(arraySize * sizeof(int));
        for(int i = 0; i < arraySize; i++)
        {
            array[i] = random_in_range(50, 199);
        }
          
        int newPrimeCount = get_prime_count(array, arraySize);
 
        if(newPrimeCount > maxPrimeCount) {
            maxPrimeCount = newPrimeCount;
            maxCountIteration = i;
        }

        int difference = arraySize-newPrimeCount;
        float ratio = ((float)newPrimeCount/(float)difference);

        ratioSum += ratio;

        free(array);
    }

    printf("[Executor]: Iteration with maximum prime count is %d\n", maxCountIteration);
    return (ratioSum/arraySize);
}

int random_in_range(int lower_bound, int upper_bound)
{
    return ((rand() % (upper_bound - lower_bound)) + lower_bound);
}

int get_prime_count(int *array, int arraySize)
{
        
    int primeTotal = 0;
    //Iterating each number 
    for(int i = 0; i < arraySize; i++){
        
        int number = array[i]; //initialzie number 
        int j = 2;
        int flag = 1;

        //logic
        while (j < number) {
            if(number % j == 0) {
                flag = 0;
                break;
            }   
            j++;
        }
        if(flag == 1) {
            primeTotal++;
        }
        
    }  
        
    return primeTotal;
}