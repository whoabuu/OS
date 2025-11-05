#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

struct data {
    char buff[512];
    int flag;
};

int main() {
    key_t key = ftok("new.txt", 'A');
    int id = shmget(key, 1024, 0666 | IPC_CREAT);

    struct data *p = (struct data *) shmat(id, (void *)0, 0);

    while (p->flag != 1) {
        printf("Client waiting for Server to enter value...\n");
        sleep(2);
    }

    printf("\nData in shared memory is:\n%s\n", p->buff);

    p->flag = 0; // reset flag so server can reuse

    shmdt(p);
    shmctl(id, IPC_RMID, NULL);

    return 0;
}
