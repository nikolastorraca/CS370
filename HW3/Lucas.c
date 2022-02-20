/*
 *  HW3: Inter-Process Communications
 *  File: Lucas.c
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
    
    if(number > 7){ // if num > 7, the sum is > 50
        sprintf(argv[1],"%d", number);
        return 0;
    }

    sprintf(argv[1], "%d", sum);

    return 0;
}


