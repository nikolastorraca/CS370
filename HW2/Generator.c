/*
 *  HW2
 *  File: Generator.c
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h> // wait()
#include <unistd.h> // fork(), pid_t

int main(int argc, char** argv) {
    pid_t my_pid = getpid();
    printf("[Generator %d] Preparing to fork...\n", my_pid);

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

    
  return 0;
}
