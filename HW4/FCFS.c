#include <stdio.h>

struct myProcess {
    int processID;
    int arrTime;
    int burstTime;
    int waitTime;
    int turnaround;
};

/*
struct myState {
    int currentProcess;
    
};*/

int main()
{
    struct myProcess process1, process2, process3;
    
    
    process1.processID = 1;
    process1.arrTime = 4;
    process1.burstTime = 3;
    
    process2.processID = 2;
    process2.arrTime = 0;
    process2.burstTime = 2;
    
    process3.processID = 3;
    process3.arrTime = 5;
    process3.burstTime = 7;
    
    struct myProcess myProArray[3] = {process2, process1, process3};
    
    //caclulate total burst time
    int processTime = 0;
    for(int i = 0; i < 3; i++) {
        processTime += myProArray[i].burstTime;
    }
    
    printf("---------------FCFS-----------------\n");
    //print gnatt chart header
    printf("************Gnatt Chart*************\n");
    
    int proStartTime= 0;
    int proEndTime = 0;
    int currentProcess = 0;

    int i;
    for(i = 0; i < 3; i++) {
        if(proEndTime < myProArray[i].arrTime) {
            printf("[  %d  ]-IDLE-[  %d  ]\n", proEndTime, myProArray[i].arrTime);
            proEndTime = myProArray[i].arrTime;
            proStartTime += myProArray[i-1].burstTime;
            i--;
            continue;
        }
        
        currentProcess = myProArray[i].processID;
        proEndTime = proStartTime + myProArray[i].burstTime;
        myProArray[i].turnaround = proEndTime-myProArray[i].arrTime;
        myProArray[i].waitTime = myProArray[i].turnaround - myProArray[i].burstTime;
        printf("[  %d  ]--%d--[  %d  ]\n", proStartTime, currentProcess, proEndTime);
        proStartTime += myProArray[i].burstTime;
    }
    
    printf("\nProcessID | Waiting Time | Turnaround Time\n");
    int totalWait = 0;
    int totalTurnaround = 0;
    for(int i = 0; i < 3; i++) {
        totalWait += myProArray[i].waitTime;
        totalTurnaround += myProArray[i].turnaround;
        printf("   %d      |    %d         |     %d     \n", myProArray[i].processID, myProArray[i].waitTime, myProArray[i].turnaround);
    }
    
    printf("Average Waiting Time: %f\n", (float)totalWait/(float)3);
    printf("Average Turnaround Time: %f\n", (float)totalTurnaround/(float)3);
    
    
    return 0;
}
