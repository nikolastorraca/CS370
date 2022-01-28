/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

int num_prime();
int random_number();

int main()
{
    printf("*****Num Prime******\n");
    
    printf("1\n");
    int arrayLength = 20;
      int *array = malloc(arrayLength * sizeof(int));
    printf("2\n");
    for(int i = 0; i < arrayLength; i++) {
        array[i] = random_number();
    }
    printf("3\n");
    // Print array
    for(int i = 0; i < arrayLength; i++) {
        printf("%d: %d  ", i, array[i]);
    }
    
    int primeTotal = num_prime(array, arrayLength);
    printf("Prime Total: %d\n", primeTotal);
    return 0;
}

int num_prime(int *array, int arrayLength){
    
    
    int primeTotal = 0;
    printf("\n4\n");
    //Iterating each number 
    for(int i = 0; i < arrayLength; i++){
        int number = array[i]; //initialzie number 
        int j = 2;
        int m = 0;
        int flag = 1;
        printf("5\n");
        //logic
        printf("Checking for: %d\n", number);
        while (j < number) {
            if(number % j == 0) {
                flag = 0;
                break;
            }   
            j++;
        }
        printf("6\n");
        if(flag == 1) {
            primeTotal++;
            printf("%d is prime!\n", number);
        }
        else
            printf("%d is not prime...\n", number);
        
    }  //END OF NUMBER
    
    printf("7\n");
    
    return primeTotal;
}

int random_number() {
    return (rand() % (45 - 2 + 1)) + 2;   
}
