#include <stdio.h>
void calculateNeed(int need[][10], int max[][10], int allot[][10], int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allot[i][j];
        }
    }
}
int isSafe(int processes[], int avail[], int max[][10], int allot[][10], int n, int m) {
    int need[10][10];
    calculateNeed(need, max, allot, n, m);
    int finish[10] = {0};
    int safeSeq[10];
    int work[10];
    for (int i = 0; i < m; i++) {
        work[i] = avail[i];
    }
    int count = 0;
    while (count < n) {
        int found = 0;
        for (int p = 0; p < n; p++) {
            if (finish[p] == 0) {
                int j;
                for (j = 0; j < m; j++) {
                    if (need[p][j] > work[j]) {
                        break;
                    }
                }
                if (j == m) {
                    for (int k = 0; k < m; k++) {
                        work[k] += allot[p][k];
                    }
                    safeSeq[count++] = processes[p];
                    finish[p] = 1;
                    found = 1;
                }
            }
        }
        if (!found) {
            printf("System is not in a safe state.\n");
            return 0;
        }
    }
    printf("System is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", safeSeq[i]);
    }
    printf("\n");
    return 1;
}
int main() {
    int n, m;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resources: ");
    scanf("%d", &m);
    int processes[10], avail[10], max[10][10], allot[10][10];
    for (int i = 0; i < n; i++) {
        processes[i] = i;
    }
    printf("Enter the available resources:\n");
    for (int i = 0; i < m; i++) {
        scanf("%d", &avail[i]);
    }
    printf("Enter the maximum resources for each process:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }
    printf("Enter the allocated resources for each process:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &allot[i][j]);
        }
    }
    isSafe(processes, avail, max, allot, n, m);
    return 0;
}
Output:
Enter the number of processes: 5
Enter the number of resources: 3
Enter the available resources:
3 3 2
Enter the maximum resources for each process:
3 5 7
2 2 3
2 0 9
2 2 2
3 3 4
Enter the allocated resources for each process:
0 1 0
0 0 2
2 0 3
2 0 3
1 1 2
System is in a safe state.
Safe sequence is: 1 3 4 0 2
