/*
 *  HW4: CPU Scheduling Algorithms
 *  File: scheduler.c
 *  Developed by: Nik Torraca
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFF_SIZE 1000

//This struct will hold the data of each process
struct myProcess {
    int processID;
    int arrTime;
    int burstTime;
    int waitTime;
    int turnaround;
};

//This function will switch two processes in the process array
//Input: Pointer to two processes in the array
//Postcondition: The two items are switched in the array
void swap(struct myProcess* xp, struct myProcess* yp) {
    struct myProcess temp = *xp;
    *xp = *yp;
    *yp = temp;
}


//This function will sort the processes by process ID
//Input: Process array and the number of processes
//Postcondition: Array of processes is sorted by PID
void sortProcessesById(struct myProcess myArray[], int numProcess) {
    
    int i, j, min_idx;

    for(i = 0; i < numProcess-1; i++) {
        min_idx = i;
        for(j = i+1; j < numProcess; j++) {
            if(myArray[j].processID < myArray[min_idx].processID)
                min_idx = j;
        }

        swap(&myArray[min_idx], &myArray[i]);
    }
}

//This function will sort the processes by process arrival time
//Input: Process array and the number of processes
//Postcondition: Array of processes is sorted by arrival time
void sortProcessesByArrival(struct myProcess myArray[], int numProcess) {
    
    int i, j, min_idx;

    for(i = 0; i < numProcess-1; i++) {
        min_idx = i;
        for(j = i+1; j < numProcess; j++) {
            if(myArray[j].arrTime < myArray[min_idx].arrTime)
                min_idx = j;
        }

        swap(&myArray[min_idx], &myArray[i]);
    }
}


//This function will create a gnatt chart for FCFS and make a number of calculations
//Input: Process array and the number of processes
//Postcondition: Gnatt chart and calulations are printed
void FCFS(struct myProcess myArray[], int numProcess){
 
    sortProcessesByArrival(myArray, numProcess);

    printf("---------------FCFS-----------------\n");
    //print gnatt chart header
    printf("************Gnatt Chart*************\n");

    int proStartTime= 0;
    int proEndTime = 0;
    int currentProcess = 0;
    int totalTime = 0;

    int i;
    for(i = 0; i < numProcess; i++) {
        if(proEndTime < myArray[i].arrTime) {
            printf("[  %d  ]-IDLE-[  %d  ]\n", proEndTime, myArray[i].arrTime);
            proEndTime = myArray[i].arrTime;
            proStartTime = proEndTime;
            i--;
            totalTime = proEndTime;
            continue;
        }
        
        currentProcess = myArray[i].processID;
        proEndTime = proStartTime + myArray[i].burstTime;
        myArray[i].turnaround = proEndTime-myArray[i].arrTime;
        myArray[i].waitTime = myArray[i].turnaround - myArray[i].burstTime;
        printf("[  %d  ]--%d--[  %d  ]\n", proStartTime, currentProcess, proEndTime);
        proStartTime = proEndTime;
        totalTime = proEndTime;
    }

    sortProcessesById(myArray, numProcess);

    printf("\nProcessID | Waiting Time | Turnaround Time\n");
    int totalWait = 0;
    int totalTurnaround = 0;
    for(int i = 0; i < numProcess; i++) {
        totalWait += myArray[i].waitTime;
        totalTurnaround += myArray[i].turnaround;
        printf("   %d      |    %d         |     %d     \n", myArray[i].processID, myArray[i].waitTime, myArray[i].turnaround);
    }
    
    printf("\nAverage Waiting Time: %f\n", (float)totalWait/(float)numProcess);
    printf("Average Turnaround Time: %f\n", (float)totalTurnaround/(float)numProcess);
    printf("Throughput: %f\n", (float)numProcess/(float)totalTime);

}


//This function will create a gnatt chart for SJF and make a number of calculations
//Input: Process array and the number of processes
//Postcondition: Gnatt chart and calulations are printed
void SJF(struct myProcess myArray[], int numProcess){
 
    sortProcessesByArrival(myArray, numProcess);

    printf("\n---------------SJF-----------------\n");
    //print gnatt chart header
    printf("************Gnatt Chart************\n");

    int proStartTime= 0;
    int proEndTime = 0;
    int currentProcess = 0;
    int totalTime = 0;

    int i;
    for(i = 0; i < numProcess; i++) {
        if(proEndTime < myArray[i].arrTime) {
            printf("[  %d  ]-IDLE-[  %d  ]\n", proEndTime, myArray[i].arrTime);
            proEndTime = myArray[i].arrTime;
            proStartTime = proEndTime;
            i--;
            totalTime = proEndTime;
            continue;
        }
        
        for(int j = i+1; j < numProcess; j++){
            if(myArray[i].arrTime < proEndTime && myArray[j].burstTime < myArray[i].burstTime)
                swap(&myArray[j], &myArray[i]);
        }
        currentProcess = myArray[i].processID;
        proEndTime = proStartTime + myArray[i].burstTime;
        myArray[i].turnaround = proEndTime-myArray[i].arrTime;
        myArray[i].waitTime = myArray[i].turnaround - myArray[i].burstTime;
        printf("[  %d  ]--%d--[  %d  ]\n", proStartTime, currentProcess, proEndTime);
        proStartTime = proEndTime;
        totalTime = proEndTime;
    }

    sortProcessesById(myArray, numProcess);

    printf("\nProcessID | Waiting Time | Turnaround Time\n");
    int totalWait = 0;
    int totalTurnaround = 0;
    for(int i = 0; i < numProcess; i++) {
        totalWait += myArray[i].waitTime;
        totalTurnaround += myArray[i].turnaround;
        printf("   %d      |    %d         |     %d     \n", myArray[i].processID, myArray[i].waitTime, myArray[i].turnaround);
    }
    
    printf("\nAverage Waiting Time: %f\n", (float)totalWait/(float)numProcess);
    printf("Average Turnaround Time: %f\n", (float)totalTurnaround/(float)numProcess);
    printf("Throughput: %f\n", (float)numProcess/(float)totalTime);

}

//This function will create a gnatt chart for Round Robin algorithm and make a number of calculations
//Input: Process array, the number of processes and the time quantum
//Postcondition: Gnatt chart and calulations are printed
void RR(struct myProcess myArray[], int numProcess, int quantum) {
 
    sortProcessesByArrival(myArray, numProcess);

    printf("\n-----------Round Robin-------------\n");
    printf("\nProcessID | Waiting Time | Turnaround Time\n");

    int count,time,remain,flag=0;
    int totalWait=0;
    int totalTurnaround=0;
    int rt[numProcess];
    remain = numProcess;

    for(int i = 0; i < numProcess; i++) {
        rt[i] = myArray[i].burstTime;
    }

    for(time=0,count=0;remain!=0;) {
        if(rt[count]<=quantum && rt[count]>0) {
            time+=rt[count];
            rt[count]=0;
            flag=1;
        }
        else if(rt[count]>0) {
            rt[count]-=quantum;
            time+=quantum;
        }
        if(rt[count]==0 && flag==1) {
            remain--;
            printf("    %d\t  |\t%d\t |\t%d\n",myArray[count].processID,time-myArray[count].arrTime,time-myArray[count].arrTime-myArray[count].burstTime);
            totalWait+=time-myArray[count].arrTime-myArray[count].burstTime;
            totalTurnaround+=time-myArray[count].arrTime;
            flag=0;
        }
        if(count==numProcess-1)
            count=0;
        else if(myArray[count+1].arrTime<=time)
            count++;
        else
            count=0;
  }

  printf("\nAverage Waiting Time= %f\n",(float)totalWait/(float)numProcess);
  printf("Average Turnaround Time = %f\n",(float)totalTurnaround/(float)numProcess);
  printf("Throughput: %f\n", (float)numProcess/(float)time);
}

int main(int argc, char** argv) {

    if(argc != 3) 
    {
        printf("Please enter 2 command line arguments, a valid CSV file and a quantum.\n");
        return -1;
    }

    int quantum = atoi(argv[2]);
    struct myProcess process1, process2, process3, process4, process5, process6, process7, process8, process9, process10, process11, process12, process13, process14, process15;
   
    FILE *fp=fopen(argv[1],"r"); // open CSV file
    char buff[BUFF_SIZE]; // Buffer to hold data from file

    int row = 0;
    int column = 0;
    int numProcess = 0;

    // loop through each line in file
    while(fgets(buff, BUFF_SIZE-1, fp) != NULL) {

        column = 0;
        numProcess++;
        row++;
        if(row == 1)
            continue;

        char* value = strtok(buff, ",");
        while(value) {

            //store process ID values from CSV file into structs
            if(column == 0) {
                if(row == 2)
                    process1.processID = atoi(value);
                if(row == 3)
                    process2.processID = atoi(value);
                if(row == 4)
                    process3.processID = atoi(value);
                if(row == 5)
                    process4.processID = atoi(value);
                if(row == 6)
                    process5.processID = atoi(value);
                if(row == 7)
                    process6.processID = atoi(value);
                if(row == 8)
                    process7.processID = atoi(value);
                if(row == 9)
                    process8.processID = atoi(value);
                if(row == 10)
                    process9.processID = atoi(value);
                if(row == 11)
                    process10.processID = atoi(value);
                if(row == 12)
                    process11.processID = atoi(value);
                if(row == 13)
                    process12.processID = atoi(value);
                if(row == 14)
                    process13.processID = atoi(value);
                if(row == 15)
                    process14.processID = atoi(value);
                if(row == 16)
                    process15.processID = atoi(value);

            }
            //store arrival time values from CSV file into structs
            else if(column == 1) {
                if(row == 2)
                    process1.arrTime = atoi(value);
                if(row == 3)
                    process2.arrTime = atoi(value);
                if(row == 4)
                    process3.arrTime = atoi(value);
                if(row == 5)
                    process4.arrTime = atoi(value);
                if(row == 6)
                    process5.arrTime = atoi(value);
                if(row == 7)
                    process6.arrTime = atoi(value);
                if(row == 8)
                    process7.arrTime = atoi(value);
                if(row == 9)
                    process8.arrTime = atoi(value);
                if(row == 10)
                    process9.arrTime = atoi(value);
                if(row == 11)
                    process10.arrTime = atoi(value);
                if(row == 12)
                    process11.arrTime = atoi(value);
                if(row == 13)
                    process12.arrTime = atoi(value);
                if(row == 14)
                    process13.arrTime = atoi(value);
                if(row == 15)
                    process14.arrTime = atoi(value);
                if(row == 16)
                    process15.arrTime = atoi(value);
            }
            //store burst time values from CSV file into structs
            else if(column == 2) {
                if(row == 2)
                    process1.burstTime = atoi(value);
                if(row == 3)
                    process2.burstTime = atoi(value);
                if(row == 4)
                    process3.burstTime = atoi(value);
                if(row == 5)
                    process4.burstTime = atoi(value);
                if(row == 6)
                    process5.burstTime = atoi(value);
                if(row == 7)
                    process6.burstTime = atoi(value);
                if(row == 8)
                    process7.burstTime = atoi(value);
                if(row == 9)
                    process8.burstTime = atoi(value);
                if(row == 10)
                    process9.burstTime = atoi(value);
                if(row == 11)
                    process10.burstTime = atoi(value);
                if(row == 12)
                    process11.burstTime = atoi(value);
                if(row == 13)
                    process12.burstTime = atoi(value);
                if(row == 14)
                    process13.burstTime = atoi(value);
                if(row == 15)
                    process14.burstTime = atoi(value);
                if(row == 16)
                    process15.burstTime = atoi(value);
            }
            value = strtok(NULL, ",");
            column++;
        }
    }

    //close file
    fclose(fp);
    numProcess--;

    //create array to store each process struct
    struct myProcess *processArray = malloc(numProcess * sizeof(process1));

    //store each process in array
    if(numProcess>=1){
        processArray[0] = process1;
    }
    if(numProcess>=2){
        processArray[1] = process2;
    }
    if(numProcess>=3){
        processArray[2] = process3;
    }
    if(numProcess>=4){
        processArray[3] = process4;
    }
    if(numProcess>=5){
        processArray[4] = process5;
    }
    if(numProcess>=6){
        processArray[5] = process6;
    }
    if(numProcess>=7){
        processArray[6] = process7;
    }
    if(numProcess>=8){
        processArray[7] = process8;
    }
    if(numProcess>=9){
        processArray[8] = process9;
    }
    if(numProcess>=10){
        processArray[9] = process10;
    }
    if(numProcess>=11){
        processArray[10] = process11;
    }
    if(numProcess>=12){
        processArray[11] = process12;
    }
    if(numProcess>=13){
        processArray[12] = process13;
    }
    if(numProcess>=14){
        processArray[13] = process14;
    }
    if(numProcess>=15){
        processArray[14] = process15;
    }
    if(numProcess>15){
        printf("Too many processes! There should be a maximum of 15 processes in your CSV file!\n");
        return -1;
    }

    sortProcessesById(processArray, numProcess);

    FCFS(processArray, numProcess);

    SJF(processArray, numProcess);
    
    RR(processArray, numProcess, quantum);

    printf("\n");
    
    free(processArray);

    return 0;
}