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
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

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

    //create pipe
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
            
        close(fd[WRITE_END]);

        char read_str[SMALL_BUFF];
        
        //Read from pipe:
        read(fd[READ_END], read_str, SMALL_BUFF);
        sum = atoi(read_str);
        printf("[Starter %d]: Contents read from the read end pipe: %d\n",my_pid, sum);

        close(fd[READ_END]);
    }

    int maxPrime = findMaxPrime(sum);

    char primeAsString[SMALL_BUFF];
    sprintf(primeAsString, "%d", maxPrime);

    //create shared memory segments
    char *SHM_Lucas = "SHM_Lucas";
    char *SHM_HarmonicSeries = "SHM_HarmonicSeries";
    char *SHM_HexagonalSeries = "SHM_HexagonalSeries";
    void *lucasPtr;
    void *harmonicPtr;
    void *hexPtr;
    int SIZE = 4096;
    int shmLucas_fd = shm_open(SHM_Lucas, O_CREAT | O_RDWR, 0666);
    ftruncate(shmLucas_fd, SIZE);
    lucasPtr = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shmLucas_fd, 0);
    	if (lucasPtr == MAP_FAILED) {
		printf("Map failed\n");
		return -1;
	}
    printf("[Starter %d]: Created Shared memory 'SHM_Lucas' with FD: %d\n", my_pid, shmLucas_fd);
    int shmHarmonic_fd = shm_open(SHM_HarmonicSeries, O_CREAT | O_RDWR, 0666);
    ftruncate(shmHarmonic_fd, SIZE);
    harmonicPtr = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shmHarmonic_fd, 0);
    	if (harmonicPtr == MAP_FAILED) {
		printf("Map failed\n");
		return -1;
	}
    printf("[Starter %d]: Created Shared memory 'SHM_Harmonic' with FD: %d\n", my_pid, shmHarmonic_fd);
    int shmHex_fd = shm_open(SHM_HexagonalSeries, O_CREAT | O_RDWR, 0666);
    ftruncate(shmHex_fd, SIZE);
    hexPtr = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shmHex_fd, 0);
    	if (hexPtr == MAP_FAILED) {
		printf("Map failed\n");
		return -1;
	}
    printf("[Starter %d]: Created Shared memory 'SHM_Hexagonal' with FD: %d\n", my_pid, shmHex_fd);

    //Create 3 child processes
    pid_t pid1, pid2, pid3;
    pid1 = fork();
    if(pid1 == 0) { //Child 1
        execlp("./Lucas", "./Lucas", SHM_Lucas, primeAsString, NULL);
    }
    else {
        pid2 = fork();
        if(pid2 == 0) { // Child 2
            execlp("./HarmonicSeries", "./HarmonicSeries", SHM_HarmonicSeries, primeAsString, NULL);
        }
        else {
            pid3 = fork();
            if(pid3 == 0) { // Child 3
                execlp("./HexagonalSeries", "./HexagonalSeries", SHM_HexagonalSeries, primeAsString, NULL);
            }
            else { //Parent Process
               //wait for all child processes to finish
               while(wait(NULL) > 0);
            }
        }
    }

    //Read data writen to shared memory by child process for lucas sequence
    char *readLucasPtr;
    int shm_fd = shm_open(SHM_Lucas, O_RDONLY, 0666);
	if (shm_fd == -1) {
		printf("shared memory failed\n");
		exit(-1);
	}
    readLucasPtr = mmap(0,SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
	if (readLucasPtr == MAP_FAILED) {
		printf("Map failed\n");
		exit(-1);
	}

    printf("[Starter %d]: Lucas last number: %s\n", my_pid, readLucasPtr);

    //Read data writen to shared memory by child process for harmonic sequence
    char *readHarmonicPtr;
    int shm_fd3 = shm_open(SHM_HarmonicSeries, O_RDONLY, 0666);
	if (shm_fd3 == -1) {
		printf("shared memory failed\n");
		exit(-1);
	}
    readHarmonicPtr = mmap(0,SIZE, PROT_READ, MAP_SHARED, shm_fd3, 0);
	if (readHarmonicPtr == MAP_FAILED) {
		printf("Map failed\n");
		exit(-1);
	}

    printf("[Starter %d]: HarmonicSeries last number: %s\n", my_pid, readHarmonicPtr);

    //Read data writen to shared memory by child process for hexagonal sequence
    char *readHexPtr;
    int shm_fd2 = shm_open(SHM_HexagonalSeries, O_RDONLY, 0666);
	if (shm_fd2 == -1) {
		printf("shared memory failed\n");
		exit(-1);
	}
    readHexPtr = mmap(0,SIZE, PROT_READ, MAP_SHARED, shm_fd2, 0);
	if (readHexPtr == MAP_FAILED) {
		printf("Map failed\n");
		exit(-1);
	}

    printf("[Starter %d]: HexagonalSeries last number: %s\n", my_pid, readHexPtr);

    // unlink shared memory
    if (shm_unlink(SHM_Lucas) == -1) {
		printf("Error removing %s\n",SHM_Lucas);
		exit(-1);
	}
    if (shm_unlink(SHM_HarmonicSeries) == -1) {
		printf("Error removing %s\n",SHM_HarmonicSeries);
		exit(-1);
	}
    if (shm_unlink(SHM_HexagonalSeries) == -1) {
		printf("Error removing %s\n",SHM_HexagonalSeries);
		exit(-1);
	}
    
    return 0;
}

//This function will calculate max prime number less than or equal to sum 
//Input: sum
//Output: Max prime number
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