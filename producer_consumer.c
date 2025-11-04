#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define SIZE 5

int buffer[SIZE];
int in = 0, out = 0;

// Three semaphores
sem_t empty;   // counts empty slots
sem_t full;    // counts filled slots
sem_t s;       // binary semaphore (acts like mutex)

void *producer(void *arg) {
    for (int i = 1; i <= 5; i++) {
        sem_wait(&empty);  // wait if buffer full
        sem_wait(&s);      // enter critical section

        buffer[in] = i;
        printf("Producer produced: %d\n", i);
        in = (in + 1) % SIZE;

        sem_post(&s);      // exit critical section
        sem_post(&full);   // signal that buffer has data

        sleep(1);
    }
    return NULL;
}

void *consumer(void *arg) {
    for (int i = 1; i <= 5; i++) {
        sem_wait(&full);   // wait if buffer empty
        sem_wait(&s);      // enter critical section

        int item = buffer[out];
        printf("Consumer consumed: %d\n", item);
        out = (out + 1) % SIZE;

        sem_post(&s);      // exit critical section
        sem_post(&empty);  // signal empty space available

        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t prod, cons;

    sem_init(&empty, 0, SIZE); // buffer has SIZE empty slots
    sem_init(&full, 0, 0);     // buffer starts empty
    sem_init(&s, 0, 1);        // binary semaphore for critical section

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&s);

    printf("\nAll done!\n");
    return 0;
}
