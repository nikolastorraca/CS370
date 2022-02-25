/*
 *  HW3: Inter-Process Communications
 *  File: HexagonialSeries.c
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
        printf("[HexagonalSeries] ERROR: %d is not between 1 (inclusive) and 20 (inclusive).\n", number);
        return 0;
    }*/
    
    // store hexagonal number sequence in array
    int hexagonalNums[] = {1,6,15,28,45,66,91,120,153,190,231,276,325,378,435,496,561,630,703,780};

    printf("[HexagonalSeries %d]: The first %d numbers of the Hexagonal series are ", pid, number);
    //calculate sum
    for(int i = 0; i <= number-1; i++){
        printf("%d ", hexagonalNums[i]);
        sum += hexagonalNums[i];
    }

    printf("\n");

    printf("[HexagonalSeries %d]: The nth number in the Hexagonal series is %d\n", pid, hexagonalNums[number-1]);
    printf("[HexagonalSeries %d]: The sum of the first %d numbers of the Hexagonal series is %d\n", pid, number, sum);
    
    int SIZE = 4096;
    char valAsString[100];

    void *hexPtr;
    int shmHex_fd = shm_open(argv[1], O_RDWR, 0666);
    if (shmHex_fd == -1) {
        printf("shared memory failed\n");
        exit(-1);
    }

    hexPtr = mmap(0,SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shmHex_fd, 0);
    if(hexPtr == MAP_FAILED) {
        printf("Map failed\n");
		exit(-1);
    }


    if(number > 5){ // if number > 5, the sum is > 100
        sprintf(valAsString,"%d", number);
        sprintf(hexPtr, "%s", valAsString);
        return 0;
    }

    sprintf(valAsString,"%d", sum);
    sprintf(hexPtr, "%s", valAsString);

    return 0;
}


