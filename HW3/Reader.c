/*
 *  HW3: Inter-Process Communications
 *  File: Reader.c
 *  Developed by: Nik Torraca
 */

#define LARGE_BUFF 1000
#define SMALL_BUFF 100
#define READ_END 0
#define WRITE_END 1

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h> // wait()
#include <unistd.h> // fork(), pid_t
#include <string.h> //strlens

int main(int argc, char** argv) {

    int sum = 0;
    if(argc!=3) {
        printf("Expecting 1 argument (name of file). Try again.\n");
        return 0;
    }

    int fileDescriptor = atoi(argv[2]);

    // open file
    FILE *fp=fopen(argv[1],"r");
    char buff[LARGE_BUFF]; // Buffer to hold data from file

     // loop through each line in file
    while(fgets(buff, LARGE_BUFF-1, fp) != NULL){

        sum += atoi(buff);
    }

    fclose(fp);

    char sumAsString[SMALL_BUFF];
    sprintf(sumAsString, "%d", sum);

    //Write sum to pipe and close write end of pipe
    write(fileDescriptor, sumAsString, strlen(sumAsString)+1);
    close(fileDescriptor);

    return 0;
}