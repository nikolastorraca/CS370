/*
 *  HW3: Inter-Process Communications
 *  File: Lucas.c
 *  Developed by: Nik Torraca
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdint.h>

int main(int argc, char** argv) {

    if(argc!=3) {
        printf("Expecting 2 arguments. Try again.\n");
        return 0;
    }

    pid_t pid = getpid();
    int sum = 0;
    int number = atoi(argv[2]);
  
    //store lucas numbers sequence in array dynamically
    int lucasNums[number];
    lucasNums[0] = 2;
    lucasNums[1] = 1;

    for(int i = 3; i <= number; i++) {
        lucasNums[i-1] = lucasNums[i-2] + lucasNums[i-3];
    }

    printf("[Lucas %d]: The first %d numbers of the Lucas series are ", pid, number);
    //calculate first N number of series
    for(int i = 0; i <= number-1; i++){
        printf("%d ", lucasNums[i]);
        sum += lucasNums[i];
    }

    printf("\n");
    
    printf("[Lucas %d]: The nth number in the lucas series is %d\n", pid, lucasNums[number-1]);
    printf("[Lucas %d]: The sum of the first %d numbers of the Lucas series is %d\n", pid, number, sum);
    

    int SIZE = 4096;
    char valAsString[100];
    
    //create pointer to shared memory to write data
    void *lucasPtr;
    int shmLucas_fd = shm_open(argv[1], O_RDWR, 0666);
	if (shmLucas_fd == -1) {
		printf("shared memory failed\n");
		exit(-1);
    }

   	lucasPtr = mmap(0,SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shmLucas_fd, 0);
	if (lucasPtr == MAP_FAILED) {
		printf("Map failed\n");
		exit(-1);
	}

    //write data to shared memory

    //write n-th number if sum is greater than 50
    if(sum>50){
        sprintf(valAsString, "%d", lucasNums[number-1]);
        sprintf(lucasPtr,"%s",valAsString);
        return 0;
    }

    //otherwise write sum
    sprintf(valAsString, "%d", sum);
    sprintf(lucasPtr,"%s",valAsString);
  
    return 0;
}


