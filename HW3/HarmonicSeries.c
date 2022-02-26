/*
 *  HW3: Inter-Process Communications
 *  File: HarmonicSeries.c
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
    float sum = 0;
    int number = atoi(argv[2]);

    // store harmonic number series in array dynamically
    float harmonicNums[number];

    for(int i = 1; i <= number; i++) {
        harmonicNums [i-1] = (float)1/(float)i;
    }

    printf("[HarmonicSeries %d]: The first %d numbers of the Harmonic series are ", pid, number);
    //calculate sum
    for(int i = 0; i <= number-1; i++){
        printf("%.6f ", harmonicNums[i]);
        sum += harmonicNums[i];
    }

    printf("\n");

    printf("[HarmonicSeries %d]: The nth number in the Harmonic series is %.6f\n", pid, harmonicNums[number-1]);
    printf("[HarmonicSeries %d]: The sum of the first %d numbers of the Harmonic series are %.6f\n", pid, number, sum);

    
    int intSum = (int)sum; //cast to int 
    
    //create pointer to shared memory to write data
    int SIZE = 4096;
    char valAsString[100];

    void *harmonicPtr;
    int shmHarmonic_fd = shm_open(argv[1], O_RDWR, 0666);
	if (shmHarmonic_fd == -1) {
		printf("shared memory failed\n");
		exit(-1);
    }

    harmonicPtr = mmap(0,SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shmHarmonic_fd, 0);
    if(harmonicPtr == MAP_FAILED) {
		printf("Map failed\n");
		exit(-1);
    }

    //write to shared memory
    sprintf(valAsString, "%d", intSum);
    sprintf(harmonicPtr,"%s", valAsString);

    return 0;
}


