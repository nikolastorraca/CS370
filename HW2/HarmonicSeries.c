/*
 *  HW2: Parent and Child Processes
 *  File: HarmonicSeries.c
 *  Developed by: Nik Torraca
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char** argv) {

    if(argc!=2) {
        printf("Expecting 1 arguments. Try again.\n");
        return 0;
    }

    pid_t pid = getpid();
    float sum = 0;
    int number = atoi(argv[1]);
    if(number>20 || number<1){
        printf("[HarmonicSeries] ERROR: %d is not between 1 (inclusive) and 20 (inclusive).\n", number);
        return 0;
    }
    float harmonicNums[] = {1,((float)1/(float)2),((float)1/(float)3),((float)1/(float)4),((float)1/(float)5),((float)1/(float)6),((float)1/(float)7),((float)1/(float)8),((float)1/(float)9),((float)1/(float)10),
        ((float)1/(float)11),((float)1/(float)12),((float)1/(float)13),((float)1/(float)14),((float)1/(float)15),((float)1/(float)16),((float)1/(float)17),((float)1/(float)18),((float)1/(float)19),((float)1/(float)20)};

    for(int i = 0; i <= number-1; i++){
        sum += harmonicNums[i];
    }

    printf("[HarmonicSeries %d]: The sum of the first %d numbers of the Harmonic series is %.6f\n", pid, number, sum);
    printf("[HarmonicSeries %d]: The nth number in the Harmonic series is %.6f\n", pid, harmonicNums[number-1]);

    
    return (int)sum;
}


