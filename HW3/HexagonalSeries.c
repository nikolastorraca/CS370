/*
 *  HW3: Inter-Process Communications
 *  File: HexagonialSeries.c
 *  Developed by: Nik Torraca
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

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
    
    if(number > 5){ // if number > 5, the sum is > 100
        sprintf(argv[1],"%d", number);
        return 0;
    }

    sprintf(argv[1],"%d", sum);

    return 0;
}


