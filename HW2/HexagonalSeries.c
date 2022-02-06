/*
 *  HW2: Parent and Child Processes
 *  File: HexagonialSeries.c
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
    int sum = 0;
    int number = atoi(argv[1]);
     if(number>20 || number<1){
        printf("[HexagonalSeries] ERROR: %d is not between 1 (inclusive) and 20 (inclusive).\n", number);
        return 0;
    }
    int hexagonalNums[] = {1,6,15,28,45,66,91,120,153,190,231,276,325,378,435,496,561,630,703,780};

    for(int i = 0; i <= number-1; i++){
        sum += hexagonalNums[i];
    }

    printf("[HexagonalSeries %d]: The sum of the first %d numbers of the Hexagonal series is %d\n", pid, number, sum);
    printf("[HexagonalSeries %d]: The nth number in the Hexagonal series is %d\n", pid, hexagonalNums[number-1]);
    
    if(number > 5){
        return number;
    }

    return sum;
}


