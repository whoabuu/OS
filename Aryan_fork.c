#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    printf("\n--- Demonstration of fork(), wait(), orphan, and zombie ---\n");

    pid = fork();   // Create child process

    if (pid < 0) {
        printf("Fork failed!\n");
        return 1;
    }

    if (pid == 0) {
        // ---------------- CHILD PROCESS ----------------
        printf("\n[CHILD] I am child process.\n");
        printf("[CHILD] My PID = %d\n", getpid());
        printf("[CHILD] My Parent PID = %d\n", getppid());

        // Make a zombie first (child exits immediately)
        printf("[CHILD] Exiting now to become zombie briefly...\n");
        return 0;   // Child exits here
    }

    else {
        // ---------------- PARENT PROCESS ----------------
        printf("\n[PARENT] I am parent process.\n");
        printf("[PARENT] My PID = %d\n", getpid());
        printf("[PARENT] Child PID = %d\n", pid);

        // Keep parent alive while child is dead -> ZOMBIE
        printf("[PARENT] Sleeping for 5 sec (child is zombie now)...\n");
        sleep(5);

        // REMOVE ZOMBIE using wait()
        printf("[PARENT] Calling wait() to clean zombie...\n");
        wait(NULL);

        // Now parent leaves early so child becomes ORPHAN
        printf("[PARENT] I will exit in 2 sec to create orphan demonstration...\n");
        sleep(2);

        printf("[PARENT] Exiting now...\n");
    }

    return 0;
}
