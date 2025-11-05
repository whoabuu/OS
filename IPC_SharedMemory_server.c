#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

struct data {
    char buff[512];
    int flag;
};

int main() {
    // Create a unique key
    key_t key = ftok("new.txt", 'A');

    // Create shared memory segment
    int id = shmget(key, 1024, 0666 | IPC_CREAT);

    // Attach the shared memory segment
    struct data *p = (struct data *) shmat(id, (void *)0, 0);

    // Initialize flag
    p->flag = 0;

    // Input data from server
    printf("Enter data to share with client:\n");
    fgets(p->buff, sizeof(p->buff), stdin);

    // Mark that data is ready for the client
    p->flag = 1;

    // Wait until client reads the data (client sets flag = 0)
    while (p->flag != 0) {
        printf("\nServer waiting for client to read the data...\n");
        sleep(2);
    }

    // Detach shared memory
    shmdt(p);

    printf("\nData successfully read by client. Server exiting.\n");
    return 0;
}
