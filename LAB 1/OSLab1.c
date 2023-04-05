#include <stdio.h>
// used to include the standard input-output library in a C program.

// define a Process struct to store process information (Something like a process control block)
struct Process {
    char process_ID;        // process ID, represented as a single character. Example: A,B,C...
    int process_arrival_time;   // arrival time of the process
    int process_burst_time;     // CPU burst time required by the process
};

// function to calculate waiting time and turnaround time for First Come First Serve(FCFS) algorithm
void firstComeFirstServe(struct Process processes[], int numberOfProcess, int waiting_time[], int turnaround_time[]) {
    // calculate waiting time for first process
    waiting_time[0] = 0;
    
    // calculate waiting time for remaining processes
    for (int i = 1; i < numberOfProcess; i++) {
        waiting_time[i] = waiting_time[i-1] + processes[i-1].process_burst_time + processes[i-1].process_arrival_time - processes[i].process_arrival_time;
        /*
        - waiting_time[i-1] : the waiting time of the previous process
        - processes[i-1].process_burst_time : the burst time of the previous process
        - processes[i-1].process_arrival_time : the arrival time of the previous process
        - processes[i].process_arrival_time : the arrival time of the current process
        */
       turnaround_time[i-1] = waiting_time[i-1] + processes[i-1].process_burst_time;
        /*
        - waiting_time[i] : the waiting time of the current process
        - processes[i].process_burst_time : the burst time of the current process
        */
       if(i == numberOfProcess - 1 ){
        turnaround_time[numberOfProcess-1] = waiting_time[numberOfProcess-1] + processes[numberOfProcess-1].process_burst_time;
       }
       
    }
    
}

// function to print process details and calculated times
void showOutput(struct Process processes[], int numberOfProcess, int waiting_time[], int turnaround_time[]) {
    printf("Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < numberOfProcess; i++) {
        printf("%c\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].process_ID, processes[i].process_arrival_time, processes[i].process_burst_time, waiting_time[i], turnaround_time[i]);
        /*
        - processes[i].process_ID : the character that represents the process ID 
        - processes[i].process_arrival_time : the arrival time of the current process
        - processes[i].process_burst_time : the burst time of the current process
        - waiting_time[i] : the waiting time of the current process
        - turnaround_time[i] : the turnaround time of the current process
        */
    }
}

// main function
int main() {
    struct Process processes[] = {{'A', 0, 12}, {'B', 1, 5}, {'C', 2, 10}, {'D', 3, 2}};
    int numberOfProcess = sizeof(processes) / sizeof(struct Process);
    /*
    - processes : an array of Process structs, representing the processes to be scheduled
    - numberOfProcess : the number of processes in the processes array
    */
    
    int waiting_time[numberOfProcess], turnaround_time[numberOfProcess];
    /*
    - waiting_time : an array to store the waiting time of each process
    - turnaround_time : an array to store the turnaround time of each process
    */
    
    firstComeFirstServe(processes, numberOfProcess, waiting_time, turnaround_time);  // call the firstComeFirstServe function to calculate waiting and turnaround times
    
    showOutput(processes, numberOfProcess, waiting_time, turnaround_time);  // print the process details and calculated times
    
    return 0;   // exit the program
}
