/*
 *  HW3: Inter-Process Communications
 *  File: Starter.c
 *  Developed by: Nik Torraca
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h> // wait()
#include <unistd.h> // fork(), pid_t

#define LARGE_BUFF 1000
#define SMALL_BUFF 100
#define READ_END 0
#define WRITE_END 1

int findMaxPrime(int sum);

int main(int argc, char** argv) {

    pid_t my_pid = getpid();
    int fd[2];
    int sum;

    if(argc!=2) {
        printf("Expecting 1 argument (name of file). Try again.\n");
        return 0;
    }

    if(pipe(fd) == -1) {
        printf("Pipe Failed");
        exit(1);
    }

    //sprintf to get file descriptor of the wrtie end of the pipie into a character array
    char writeAsString[SMALL_BUFF];
    sprintf(writeAsString, "%d", fd[WRITE_END]);

    pid_t pid = fork(); // create child process
    if(pid < 0) {
        printf("Fork Failed\n");
        exit(1);
    }
    else if(pid == 0) { // Child Process
        execlp("./Reader", "./Reader", argv[1], writeAsString, NULL);
    }
    else { // Parent Process
            
        printf("[Starter %d]: Waiting for the child process %d\n", my_pid, pid);
        //int status;
        close(fd[WRITE_END]);

        char read_str[SMALL_BUFF];
        //Read from pipe:
        read(fd[READ_END], read_str, SMALL_BUFF);
        sum = atoi(read_str);
        printf("[Starter %d]: The sum is: %d\n",my_pid, sum);

        close(fd[READ_END]);
    }

    int maxPrime = findMaxPrime(sum);

    printf("[Starter %d]: The max prime number is: %d\n", my_pid, maxPrime);

    char primeAsString[SMALL_BUFF];
    sprintf(primeAsString, "%d", maxPrime);


    return 0;
}

int findMaxPrime(int sum) {

    for(int i = sum; i >= 2; i--) {

        int flag = 0;

        if(i == 0 || i==1)
            flag = 1;

        for(int j=2; j<= i/2; ++j) {

            if(i%j==0){
                flag =1;
                break;
            }
        }
        
        if(flag==0)
            return i;
    }

    printf("There are no prime numbers.\n");
    return 0;
}