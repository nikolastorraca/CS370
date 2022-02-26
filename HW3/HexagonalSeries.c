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
    
    // store hexagonal number sequence in array dynamically
    int hexagonalNums[number];

    for(int i = 1; i <= number; i++) {
        hexagonalNums [i-1] = i*(2*i-1);
    }

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

    //create pointer to shared memory to write data
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

    //write to shared memory

    //write n-th number if sum is greater than 100
    if(sum>100){
        sprintf(valAsString,"%d", hexagonalNums[number-1]);
        sprintf(hexPtr, "%s", valAsString);
        return 0;
    }
    
    //otherwise write sum
    sprintf(valAsString,"%d", sum);
    sprintf(hexPtr, "%s", valAsString);

    return 0;
}


