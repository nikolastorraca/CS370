/*
 *  HW2: Parent and Child Processes
 *  File: Generator.c
 *  Developed by: Nik Torraca
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h> // wait()
#include <unistd.h> // fork(), pid_t

#define BUFF_SIZE 1000

int main(int argc, char** argv) {
    pid_t my_pid = getpid();
    int lucasReturnVal = 0;
    int hexReturnVal = 0;
    int harmonicReturnVal = 0;
    char returnValString[10];

    if(argc!=2) {
        printf("Expecting 1 argument (name of .txt file). Try again.\n");
        return 0;
    }

    // open file
    FILE *fp=fopen(argv[1],"r");
    char buff[BUFF_SIZE]; // Buffer to hold data from file

    // loop through each line in file
    while(fgets(buff, BUFF_SIZE-1, fp) != NULL){

        pid_t pid = fork(); // create child process
        if(pid < 0) {
            printf("Fork Failed\n");
            exit(1);
        }
        else if(pid == 0) { // Child Process
            execlp("./Lucas", "./Lucas", buff, NULL);
        }
        else { // Parent Process
            
            printf("[Generator %d]: Waiting for the child process %d\n", my_pid, pid);
            int status;
            pid = wait(&status);
            if(WIFEXITED(status)){
                //print 8-bit value returned by child process. Also store in variable for later
                printf("[Generator %d]: Child process %d returned %d\n", my_pid, pid, WEXITSTATUS(status));
                lucasReturnVal = WEXITSTATUS(status);
            }
            else {
                printf("Child did not terminate\n\n");
                exit(1);
            }
        }

        sprintf(returnValString, "%d", lucasReturnVal);  // change integer to string so it can be used as argument in execlp call
        pid_t pid2 = fork(); // create second child process

        if(pid2 < 0) {
            printf("Fork Failed\n");
            exit(1);
        }
        else if(pid2 == 0) { // Child Process
            execlp("./HexagonalSeries", "./HexagonalSeries", returnValString, NULL);
        }
        else { // Parent Process
            
            printf("[Generator %d]: Waiting for the child process %d\n", my_pid, pid2);
            int status;
            pid2 = wait(&status);
            if(WIFEXITED(status)){
                //print 8-bit value returned by child process. Also store in variable for later
                printf("[Generator %d]: Child process %d returned %d\n", my_pid, pid2, WEXITSTATUS(status));
                hexReturnVal = WEXITSTATUS(status);
            }
            else {
                printf("Child did not terminate\n\n");
                exit(1);
            }
        }

        sprintf(returnValString, "%d", hexReturnVal);  // change integer to string so it can be used as argument in execlp call
        pid_t pid3 = fork(); // create 3rd child process

        if(pid3 < 0) {
            printf("Fork Failed\n");
            exit(1);
        }
        else if(pid3 == 0) { // Child Process
            execlp("./HarmonicSeries", "./HarmonicSeries", returnValString, NULL);
        }
        else { // Parent Process
            
            printf("[Generator %d]: Waiting for the child process %d\n", my_pid, pid3);
            int status;
            pid3 = wait(&status);
            if(WIFEXITED(status)){
                //print 8-bit value returned by child process. Also store in variable for later
                printf("[Generator %d]: Child process %d returned %d\n", my_pid, pid3, WEXITSTATUS(status));
                harmonicReturnVal = WEXITSTATUS(status);
            }
            else {
                printf("Child did not terminate\n\n");
                exit(1);
            }
        }

        // print summary to user
        printf("[Generator %d]: The lucas child process returned %d\n", my_pid, lucasReturnVal);
        printf("[Generator %d]: The Hexagonal child process is %d\n", my_pid, hexReturnVal);
        printf("[Generator %d]: The sum of the first n Harmonic numbers is %d\n", my_pid, harmonicReturnVal);

    }

    printf("\n");

  // close file
  fclose(fp);
  return 0;
}
