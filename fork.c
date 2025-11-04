#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    pid = fork();   // create child process

    if (pid < 0) {
        printf("Fork failed!\n");
        return 1;
    }

    if (pid == 0) {
        // ---- CHILD PROCESS ----
        printf("\nThis is the child process.\n");
        printf("My PID: %d\n", getpid());
        printf("My Parent PID: %d\n", getppid());

        printf("\nSleeping for 5 seconds (to become orphan if parent exits)...\n");
        sleep(5);

        printf("\nAfter 5 sec, my new Parent PID: %d\n", getppid());
        printf("Child exiting now.\n");
    }
    else {
        // ---- PARENT PROCESS ----
        printf("\nThis is the parent process.\n");
        printf("My PID: %d\n", getpid());
        printf("Child PID: %d\n", pid);

        printf("\nSleeping for 2 seconds before exiting (child still alive)...\n");
        sleep(2);

        printf("\nParent exiting now (child becomes orphan)...\n");
        // Uncomment next two lines to demonstrate zombie instead of orphan
        // wait(NULL);
        // printf("\n[PARENT] Child finished, no zombie created.\n");
    }

    return 0;
}
