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
    printf("[Generator %d] Preparing to fork...\n", my_pid);

    if(argc!=2) {
        printf("Expecting 1 arguments. Try again.\n");
        return 0;
    }

    printf("[Generator %d]: Preparing to open file:\n", my_pid);
    FILE *fp=fopen(argv[1],"r");

    char buff[BUFF_SIZE]; // Buffer to hold data from file

    while(fgets(buff, BUFF_SIZE-1, fp) != NULL){

        printf("Input: %s", buff);
        pid_t pid = fork();
        if(pid < 0) {
            printf("Fork Failed\n");
            exit(1);
        }
        else if(pid == 0) { // Child Process
            printf("[Generator %d]: about to execlp...\n\n", getpid());
            execlp("./Lucas", "./Child", buff, NULL);
        }
        else { // Parent Process
            
            printf("[Generator %d]: Waiting for the child process %d.\n", my_pid, pid);
            int status;
            pid = wait(&status);
            printf("[Generator %d]: Done waiting for process %d.\n", my_pid, pid);
            if(WIFEXITED(status)){
                printf("[Generator %d]: Child process %d returned %d.\n", my_pid, pid, WEXITSTATUS(status));
            }
            else {
                printf("Child did not terminate.\n\n");
                exit(1);
            }
        }

    }
    printf("\n");

/*
    pid_t pid = fork();

    if(pid < 0) {
        printf("Fork Failed\n");
        exit(1);
    }
    else if(pid == 0) { // Child Process
        printf("[Child %d] about to execlp...\n\n", getpid());
        execlp("./Child", "./Child", "1", NULL);
    }
    else { //Parent Process
        printf("[Generator %d]: Forked process with ID %d.\n", my_pid, pid);
        printf("[Generator %d]: Waiting for Process %d.\n", my_pid, pid);
        int status;
        pid = wait(&status);
        printf("\n[Generator %d]: Done waiting for Process %d.\n", my_pid, pid);
        if(WIFEXITED(status)){
            printf("[Generator %d]: Child process %d returned %d.\n", my_pid, pid, WEXITSTATUS(status));
        }
        else {
            printf("Child did not terminate\n");
            exit(1);
        }
    }
*/
  fclose(fp);
  return 0;
}
