#include <stdio.h>
#include <stdlib.h>

int num_prime();
int random_number();

int main()
{
    printf("*****Num Prime******\n");
    num_prime();
    return 0;
}

int num_prime(int *array, int arrayLength){
    
    printf("1\n");
    int arrayLength = 15;
    int primeTotal = 0;
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
    printf("Prime Total: %d\n", primeTotal);
    return 0;
}

int random_number() {
    return (rand() % (100 - 5 + 1)) + 5;   
}
