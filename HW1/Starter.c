/*
 * HW1: Dynamic Memory Allcoation
 * File: Starter.c
 * Developed by: Nik Torraca
 */

#include <stdio.h>
#include <stdlib.h>
#include "Executor.h"

int main(int argc, char *argv[]) {

    if(argc != 2)
    {
        printf("Incorrect Usage. Please run with 1 argument.\n");
        return 0;
    }
    
    int seed = atoi(argv[1]);

    srand(seed);
    printf("[Starter]: With seed: %d\n", seed);    

    float running_ratio = get_running_ratio();
    printf("[Starter]: Running ratio: %.6f\n", running_ratio);
 
    return 0;
}
