#include <stdio.h>

int main() {
    int n, i, qt, time = 0, flag = 0;
    int bt[10], wt[10], tat[10], at[10], rem_bt[10], ct[10];
    float avgwt = 0, avgtat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Input arrival times
    printf("Enter Arrival Times for all processes:\n");
    for (i = 0; i < n; i++) {
        printf("P%d Arrival Time: ", i + 1);
        scanf("%d", &at[i]);
    }

    // Input burst times
    printf("Enter Burst Times for all processes:\n");
    for (i = 0; i < n; i++) {
        printf("P%d Burst Time: ", i + 1);
        scanf("%d", &bt[i]);
        rem_bt[i] = bt[i];
    }

    // Input time quantum
    printf("Enter Time Quantum: ");
    scanf("%d", &qt);

    // Round Robin algorithm
    while (1) {
        flag = 0;
        for (i = 0; i < n; i++) {
            if (at[i] <= time && rem_bt[i] > 0) {
                flag = 1;
                if (rem_bt[i] > qt) {
                    time += qt;
                    rem_bt[i] -= qt;
                } else {
                    time += rem_bt[i];
                    rem_bt[i] = 0;
                    ct[i] = time;               // Completion time
                    tat[i] = ct[i] - at[i];     // Turnaround time
                    wt[i] = tat[i] - bt[i];     // Waiting time
                }
            }
        }
        if (flag == 0)
            break; // All processes completed
    }

    // Output results (simple table)
    printf("\nProcess\tAT\tBT\tCT\tWT\tTAT\n");
    for (i = 0; i < n; i++) {
        avgwt += wt[i];
        avgtat += tat[i];
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], ct[i], wt[i], tat[i]);
    }

    avgwt /= n;
    avgtat /= n;

    printf("\nAverage Waiting Time = %.2f", avgwt);
    printf("\nAverage Turnaround Time = %.2f\n", avgtat);

    return 0;
}
