#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    // arguments for execv — first element is program name
    char *temp[9] = {"./execv2.out", "5", "4", "5", "8", "1", "0", "2", NULL};

    // Sort numbers (ascending) from index 1 to 7
    for (int i = 1; i < 7; i++) {
        for (int j = 1; j < 7 - i; j++) {
            if (atoi(temp[j]) > atoi(temp[j + 1])) {
                char *swap = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = swap;
            }
        }
    }

    printf("Sorted arguments: ");
    for (int i = 1; i <= 7; i++) {
        printf("%s ", temp[i]);
    }
    printf("\n");

    pid_t pid;
    int status;

    pid = fork(); // create child

    if (pid == 0) {
        // Child process
        printf("This is the child process (PID = %d)\n", getpid());
        execv(temp[0], temp);  // execute b.out with sorted arguments
        perror("execv failed"); // prints only if execv fails
        exit(1);
    } else if (pid > 0) {
        // Parent process
        wait(&status);
        printf("This is the parent process (PID = %d)\n", getpid());
        printf("Child process finished with status %d\n", WEXITSTATUS(status));
    } else {
        perror("fork failed");
        exit(1);
    }

    return 0;
}
