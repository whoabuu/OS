#include <stdio.h>

int main() {
    int n, i, j, smallest, time = 0, end;
    int at[10], bt[10], temp[10], ct[10], tat[10], wt[10];
    float avgwt = 0, avgtat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Input all arrival times
    printf("\nEnter Arrival Times for all processes:\n");
    for (i = 0; i < n; i++) {
        printf("P%d Arrival Time: ", i + 1);
        scanf("%d", &at[i]);
    }

    // Input all burst times
    printf("\nEnter Burst Times for all processes:\n");
    for (i = 0; i < n; i++) {
        printf("P%d Burst Time: ", i + 1);
        scanf("%d", &bt[i]);
        temp[i] = bt[i]; // store original burst time
    }

    bt[9] = 9999; // sentinel value (large number for comparison)

    // Preemptive SJF scheduling
    for (time = 0; ; time++) {
        smallest = 9; // assume last index as smallest initially

        // find process with smallest remaining burst time
        for (i = 0; i < n; i++) {
            if (at[i] <= time && bt[i] < bt[smallest] && bt[i] > 0)
                smallest = i;
        }

        bt[smallest]--; // process executes for 1 unit of time

        // if process finished execution
        if (bt[smallest] == 0) {
            end = time + 1;
            ct[smallest] = end;                       // completion time
            tat[smallest] = ct[smallest] - at[smallest]; // turnaround time
            wt[smallest] = tat[smallest] - temp[smallest]; // waiting time
        }

        // check if all processes are completed
        int done = 1;
        for (j = 0; j < n; j++) {
            if (bt[j] > 0)
                done = 0;
        }
        if (done)
            break;
    }

    // Display output
    printf("\nProcess\tAT\tBT\tCT\tWT\tTAT\n");
    for (i = 0; i < n; i++) {
        avgwt += wt[i];
        avgtat += tat[i];
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], temp[i], ct[i], wt[i], tat[i]);
    }

    avgwt /= n;
    avgtat /= n;

    printf("\nAverage Waiting Time = %.2f", avgwt);
    printf("\nAverage Turnaround Time = %.2f\n", avgtat);

    return 0;
}
