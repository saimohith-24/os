#include <stdio.h>

struct Process {
    int pid;       // Process ID
    int burstTime; // Burst Time
    int priority;  // Priority
    int arrivalTime; // Arrival Time
    int waitingTime; // Waiting Time
    int turnAroundTime; // Turnaround Time
    int remainingTime; // Remaining Burst Time
};

void calculateMetrics(struct Process processes[], int n) {
    int completed = 0, currentTime = 0;
    int shortest = -1, minPriority = 9999;

    while (completed != n) {
        // Find the process with the highest priority (lowest priority value)
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0 && processes[i].priority < minPriority) {
                shortest = i;
                minPriority = processes[i].priority;
            }
        }

        if (shortest == -1) {
            // No process is ready, increment time
            currentTime++;
            continue;
        }

        // Execute the process for 1 unit of time
        processes[shortest].remainingTime--;
        currentTime++;

        // Check if the process is completed
        if (processes[shortest].remainingTime == 0) {
            completed++;
            int completionTime = currentTime;
            processes[shortest].turnAroundTime = completionTime - processes[shortest].arrivalTime;
            processes[shortest].waitingTime = processes[shortest].turnAroundTime - processes[shortest].burstTime;
            minPriority = 9999; // Reset min priority for the next iteration
        }
    }
}

void displayMetrics(struct Process processes[], int n) {
    printf("\nPID\tPriority\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               processes[i].pid,
               processes[i].priority,
               processes[i].arrivalTime,
               processes[i].burstTime,
               processes[i].waitingTime,
               processes[i].turnAroundTime);
    }

    float avgWaitingTime = 0, avgTurnAroundTime = 0;
    for (int i = 0; i < n; i++) {
        avgWaitingTime += processes[i].waitingTime;
        avgTurnAroundTime += processes[i].turnAroundTime;
    }
    printf("\nAverage Waiting Time: %.2f\n", avgWaitingTime / n);
    printf("Average Turnaround Time: %.2f\n", avgTurnAroundTime / n);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    // Input process details
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("\nEnter details for Process %d\n", processes[i].pid);
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrivalTime);
        printf("Burst Time: ");
        scanf("%d", &processes[i].burstTime);
        printf("Priority (lower value = higher priority): ");
        scanf("%d", &processes[i].priority);
        processes[i].remainingTime = processes[i].burstTime;
    }

    // Calculate scheduling metrics
    calculateMetrics(processes, n);

    // Display metrics
    displayMetrics(processes, n);

    return 0;
}
