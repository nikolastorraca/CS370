/*
 * HW1: Dynamic Memory Allcoation
 * File: Starter.c
 * Developed by: Nik Torraca
 */

#include <stdio.h>
#include "Executor.h"

int main(int argc, char *argv[]) {

    printf("Wow! This program compiles. Amazing!\n");
    if(argc != 2)
    {
        printf("Incorrect Usage. Please run with 1 argument.\n");
        return 0;
    }
    
    printf("You entered: ");
    printf("%s", argv[1]);
    printf("\n");
    

    reachesExecutor();
    
    return 0;
}
