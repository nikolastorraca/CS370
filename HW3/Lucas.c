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
    /* if(number>20 || number<1){
        printf("[Lucas] ERROR: %d is not between 1 (inclusive) and 20 (inclusive).\n", number);
        return 0;
    }*/

    //store lucas numbers sequence in array
    int lucasNums[] = {2,1,3,4,7,11,18,29,47,76,123,199,322,521,843,1346,2207,3571,5778,9349};

    printf("[Lucas %d]: The first %d numbers of the Lucas series are ", pid, number);
    //calculate first N number of series
    for(int i = 0; i <= number-1; i++){
        printf("%d ", lucasNums[i]);
        sum += lucasNums[i];
    }

    printf("\n");
    
    printf("[Lucas %d]: The nth number in the lucas series is %d\n", pid, lucasNums[number-1]);
    printf("[Lucas %d]: The sum of the first %d numbers of the Lucas series is %d\n", pid, number, sum);
    
    //printf("%s\n", argv[1]);

    int SIZE = 4096;
    char valAsString[100];
    
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

    if(number > 7){ // if num > 7, the sum is > 50
        sprintf(valAsString, "%d", number);
        sprintf(lucasPtr,"%s",valAsString);
        return 0;
    }

    sprintf(valAsString, "%d", sum);
    sprintf(lucasPtr,"%s",valAsString);
  
    return 0;
}


