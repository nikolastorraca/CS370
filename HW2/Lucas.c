/*
 *  HW2: Parent and Child Processes
 *  File: Lucas.c
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
        printf("[Lucas] ERROR: %d is not between 1 (inclusive) and 20 (inclusive).\n", number);
        return 0;
    }
    int lucasNums[] = {2,1,3,4,7,11,18,29,47,76,123,199,322,521,843,1346,2207,3571,5778,9349};
    printf("[Lucas %d] received argument: %d\n", pid, number);

    for(int i = 0; i <= number-1; i++){
        sum += lucasNums[i];
    }

    printf("[Lucas %d]: The sum of the first %d number of the Lucas series is %d\n", pid, number, sum);
    printf("[Lucas %d]: The nth number in the lucas series is %d\n", pid, lucasNums[number-1]);
    
    if(number > 7){
        printf("The sum of %d lucas numbers is > 50 so return n.\n", number);
        return number;
    }

    printf("The sum of %d lucas numbers is <= 50 so return the sum.\n", number);
    return sum;
}


