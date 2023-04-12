#include <stdio.h>
#include <stdlib.h>

struct process {
    int processID;      // process ID
    int burstTime;      // burst time
    int arrivalTime;    // arrival time
    int waitingTime;    // waiting time
    int turnaroundTime; // turnaround time
};

int compare(const void *a, const void *b) {  //O(1),
    struct process *p1 = (struct process *) a;  //p1 is less than the burst time of p2, the function returns a negative value
    struct process *p2 = (struct process *) b;
    return p1->burstTime - p2->burstTime;
}

void sjf(struct process process[], int n) {
    qsort(process, n, sizeof(struct process), compare);//qsort function O(n log n).

    int i, j;
    int completed = 0;
    int currentTime = 0;
    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;

    for (i = 0; i < n; i++) {                                                      //The code then starts a loop over all the processes in the input array. For each process, it calculates the waiting time by summing the burst times of all the previously executed processes. The waitingTime variable stores this value.
        // Calculate waiting time for current process
        int waitingTime = 0;
        for (j = 0; j < i; j++) {
            waitingTime += process[j].burstTime;
        }

        // Update current time and waiting time for current process
        currentTime += waitingTime;
        process[i].waitingTime = waitingTime;

        // Calculate turnaround time and update total waiting and turnaround time
        process[i].turnaroundTime = process[i].burstTime + process[i].waitingTime;
        totalWaitingTime += process[i].waitingTime;
        totalTurnaroundTime += process[i].turnaroundTime;

        // Increment completed processes count
        completed++; //indicating that one more process has been completed.
    }

    // Print results for each process and average waiting time and average turnaround time
    printf("Processes  Burst Time  Arrival Time  Waiting Time  Turnaround Time\n");
    for (i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", process[i].processID, process[i].burstTime, process[i].arrivalTime, process[i].waitingTime, process[i].turnaroundTime);
    }
    printf("Average waiting time: %.2f\n", (float) totalWaitingTime / (float) n);
    printf("Average turnaround time: %.2f\n", (float) totalTurnaroundTime / (float) n);
}

int main() {
    int n, i;
    struct process *process;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    process = (struct process *) malloc(n * sizeof(struct process)); //allocates memory dynamically for an array of n elements
 

    // Get burst time and arrival time for each process
    for (i = 0; i < n; i++) {
        printf("Enter the burst time and arrival time for process %d: ", i + 1);
        scanf("%d%d", &process[i].burstTime, &process[i].arrivalTime);
        process[i].processID = i + 1;
    }

    sjf(process, n);
    free(process);
    return 0;
}
