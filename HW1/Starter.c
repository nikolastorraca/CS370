/*
 * HW1: Dynamic Memory Allcoation
 * File: Starter.c
 * Developed by: Nik Torraca
 */

#include <stdio.h>
#include <stdlib.h>
#include "Executor.h"

int main(int argc, char *argv[]) {

    printf("Wow! This program compiles. Amazing!\n"); //DEBUG
    
    if(argc != 2)
    {
        printf("Incorrect Usage. Please run with 1 argument.\n");
        return 0;
    }
    
    printf("(DEBUG) You entered: %s\n", argv[1]); //DEBUG

    int seed = atoi(argv[1]);

    printf("(DEBUG) Seed: %d\n", seed); //DEBUG

    srand(seed);
    printf("[Starter]: With seed: %d\n", seed);    

    float running_ratio = get_running_ratio();
    printf("[Starter]: Running ratio: %.6f\n", running_ratio);
 
    return 0;
}
