#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv) {
    pid_t pid = getpid();
    printf("[Child %d] received arguments: \n", pid);
    for(int i = 0; i < argc; ++i) {
        printf("[Child %d] arg%d\t%s\n", pid, i, argv[i]);
    }
    return 20;
}


