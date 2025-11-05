#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define FIFO1 "fifo1"
#define FIFO2 "fifo2"

int main() {
    int fd1, fd2;
    char sentence[1000], result[1000];

    // Create FIFOs (ignore error if already exist)
    mkfifo(FIFO1, 0666);
    mkfifo(FIFO2, 0666);

    printf("Process 2 ready. Waiting for messages...\n");

    while (1) {
        // Read message from FIFO1
        fd1 = open(FIFO1, O_RDONLY);
        read(fd1, sentence, sizeof(sentence));
        close(fd1);

        // Check for exit condition
        if (strncmp(sentence, "exit", 4) == 0) {
            printf("Exit command received. Shutting down Process 2.\n");
            break;
        }

        // Process: Convert to uppercase (you can change logic here)
        for (int i = 0; sentence[i] != '\0'; i++) {
            if (sentence[i] >= 'a' && sentence[i] <= 'z')
                result[i] = sentence[i] - 32;  // convert to uppercase
            else
                result[i] = sentence[i];
        }
        result[strlen(sentence)] = '\0';

        // Write the result to FIFO2
        fd2 = open(FIFO2, O_WRONLY);
        write(fd2, result, strlen(result) + 1);
        close(fd2);

        printf("Processed and sent back: %s\n", result);
    }

    unlink(FIFO1);
    unlink(FIFO2);
    return 0;
}
