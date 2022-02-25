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
    /*if(number>20 || number<1){
        printf("[HarmonicSeries] ERROR: %d is not between 1 (inclusive) and 20 (inclusive).\n", number);
        return 0;
    }*/

    // store harmonic number series in array
    float harmonicNums[] = {1,((float)1/(float)2),((float)1/(float)3),((float)1/(float)4),((float)1/(float)5),((float)1/(float)6),((float)1/(float)7),((float)1/(float)8),((float)1/(float)9),((float)1/(float)10),
        ((float)1/(float)11),((float)1/(float)12),((float)1/(float)13),((float)1/(float)14),((float)1/(float)15),((float)1/(float)16),((float)1/(float)17),((float)1/(float)18),((float)1/(float)19),((float)1/(float)20)};

    printf("[HarmonicSeries %d]: The first %d numbers of the Harmonic series are ", pid, number);
    //calculate sum
    for(int i = 0; i <= number-1; i++){
        printf("%.6f ", harmonicNums[i]);
        sum += harmonicNums[i];
    }

    printf("\n");

    printf("[HarmonicSeries %d]: The nth number in the Harmonic series is %.6f\n", pid, harmonicNums[number-1]);
    printf("[HarmonicSeries %d]: The sum of the first %d numbers of the Harmonic series are %.6f\n", pid, number, sum);

    
    int intSum = (int)sum; //cast to int because WEXITSTATUS only returns 8 least-significant bits
    
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

    sprintf(valAsString, "%d", intSum);
    sprintf(harmonicPtr,"%s", valAsString);

    return 0;
}


