/*
 *  HW4: CPU Scheduling Algorithms
 *  File: scheduler.c
 *  Developed by: Nik Torraca
 */

#include <stdio.h>
#include <stdlib.h>

#define BUFF_SIZE 1000

int main(int argc, char** argv) {

    if(argc != 3) 
        printf("Please enter 3 command line arguments\n");

    int quantum = atoi(argv[2]);

    FILE *fp=fopen(argv[1],"r");
    char buff[BUFF_SIZE]; // Buffer to hold data from file

    // loop through each line in file
    while(fgets(buff, BUFF_SIZE-1, fp) != NULL){

    }

    
    return 0;
}