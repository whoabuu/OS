#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define FIFO1 "fifo1"
#define FIFO2 "fifo2"
#define OUTPUT_FILE "output.txt"

int main() {   // <-- fixed: "wint" → "int"
    int fd1, fd2;
    char sentence[1000];
    char result[200];
    FILE *fp;

    // Create FIFOs (ignore if they already exist)
    mkfifo(FIFO1, 0666);
    mkfifo(FIFO2, 0666);

    printf("Process 2 ready. Waiting for messages...\n");

    while (1) {
        // Read sentence from FIFO1
        fd1 = open(FIFO1, O_RDONLY);
        read(fd1, sentence, sizeof(sentence));
        close(fd1);

        // Exit condition
        if (strncmp(sentence, "exit", 4) == 0) {
            printf("Process 2 exiting...\n");
            break;
        }

        // Count characters, words, and lines
        int chars = 0, words = 0, lines = 0;
        int inWord = 0;
        for (int i = 0; sentence[i] != '\0'; i++) {
            char ch = sentence[i];
            chars++;
            if (ch == '\n')
                lines++;
            if (ch == ' ' || ch == '\n' || ch == '\t')
                inWord = 0;
            else if (inWord == 0) {
                inWord = 1;
                words++;
            }
        }

        // Write result to output.txt
        fp = fopen(OUTPUT_FILE, "w");
        if (fp == NULL) {
            perror("File open failed");
            exit(1);
        }
        fprintf(fp, "Characters: %d\nWords: %d\nLines: %d\n", chars, words, lines);
        fclose(fp);

        // Read back file content
        fp = fopen(OUTPUT_FILE, "r");
        if (fp == NULL) {
            perror("File read failed");
            exit(1);
        }
        size_t len = fread(result, sizeof(char), sizeof(result) - 1, fp);
        result[len] = '\0';   // ensure null-termination
        fclose(fp);

        // Send result back to Process 1
        fd2 = open(FIFO2, O_WRONLY);
        write(fd2, result, strlen(result) + 1);
        close(fd2);

        printf("Processed and sent back:\n%s\n", result);
    }

    // Clean up
    unlink(FIFO1);
    unlink(FIFO2);
    return 0;
}
