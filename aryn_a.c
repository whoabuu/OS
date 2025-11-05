// FILE: a.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    char *temp[9] = {"./b.out", "5", "4", "5", "8", "1", "0", "2", NULL};

    // Bubble sort (unchanged)
    for (int i = 1; i <= 7 - 1; i++) {
        for (int j = 1; j <= 7 - i; j++) {
            if (atoi(temp[j]) > atoi(temp[j + 1])) {
                char *swap = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = swap;
            }
        }
    }

    pid_t pid;
    int status;

    pid = fork();

    if (pid == 0) {
        // ✅ ORPHAN demonstration
       // printf("Child started: PID = %d, PPID = %d\n", getpid(), getppid());
        sleep(5);  // Parent will finish (if not waited) → child becomes orphan
        //printf("After sleep, child PPID = %d (If 1 → orphan)\n", getppid());

        // Execv demonstration (unchanged)
        printf("Child now calling execv...\n");
        execv(temp[0], temp);
        perror("execv failed");
    } 
    else {
        // ✅ ZOMBIE demonstration
        //printf("Parent started: PID = %d, Child PID = %d\n", getpid(), pid);
        //printf("Parent sleeping 10 seconds (child becomes zombie until wait)...\n");
        sleep(10);

        // Parent cleans zombie
        wait(&status);
        printf("Parent collected child. No zombie now.\n");
    }

    return 0;
}
