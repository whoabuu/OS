#include <stdio.h>
#include <stdbool.h>

#define MAX_FRAMES 10
#define MAX_PAGES 100

// Function prototypes
int findInFrames(int frames[], int n, int page);
void displayFrames(int frames[], int n);
int fifo(int pages[], int n, int frame_size);
int lru(int pages[], int n, int frame_size);
int optimal(int pages[], int n, int frame_size);

int main() {
    int pages[MAX_PAGES], n, frame_size;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter page sequence: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    // Frame size minimum 3 as per requirement
    do {
        printf("Enter frame size (minimum 3, max %d): ", MAX_FRAMES);
        scanf("%d", &frame_size);
    } while (frame_size < 3 || frame_size > MAX_FRAMES);

    printf("\n============================\n");
    printf(" FIFO (FCFS) Page Replacement\n");
    printf("============================\n");
    int faults_fifo = fifo(pages, n, frame_size);
    printf("Total Page Faults = %d\n", faults_fifo);

    printf("\n============================\n");
    printf(" LRU Page Replacement\n");
    printf("============================\n");
    int faults_lru = lru(pages, n, frame_size);
    printf("Total Page Faults = %d\n", faults_lru);

    printf("\n============================\n");
    printf(" Optimal Page Replacement\n");
    printf("============================\n");
    int faults_opt = optimal(pages, n, frame_size);
    printf("Total Page Faults = %d\n", faults_opt);

    return 0;
}

// -----------------------------------------------
// Helper Functions
// -----------------------------------------------

int findInFrames(int frames[], int n, int page) {
    for (int i = 0; i < n; i++) {
        if (frames[i] == page)
            return i;
    }
    return -1;
}

void displayFrames(int frames[], int n) {
    for (int i = 0; i < n; i++) {
        if (frames[i] == -1)
            printf("- ");
        else
            printf("%d ", frames[i]);
    }
    printf("\n");
}

// -----------------------------------------------
// FIFO Page Replacement
// -----------------------------------------------
int fifo(int pages[], int n, int frame_size) {
    int frames[MAX_FRAMES];
    int page_faults = 0;
    int front = 0;

    for (int i = 0; i < frame_size; i++)
        frames[i] = -1;

    for (int i = 0; i < n; i++) {
        if (findInFrames(frames, frame_size, pages[i]) == -1) {
            frames[front] = pages[i];
            front = (front + 1) % frame_size;
            page_faults++;
            printf("Page %d caused a fault. Frames: ", pages[i]);
        } else {
            printf("Page %d hit. Frames: ", pages[i]);
        }
        displayFrames(frames, frame_size);
    }
    return page_faults;
}

// -----------------------------------------------
// LRU Page Replacement
// -----------------------------------------------
int lru(int pages[], int n, int frame_size) {
    int frames[MAX_FRAMES];
    int time[MAX_FRAMES];
    int page_faults = 0;
    int counter = 0;

    for (int i = 0; i < frame_size; i++) {
        frames[i] = -1;
        time[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        counter++;
        int idx = findInFrames(frames, frame_size, pages[i]);
        if (idx == -1) {
            page_faults++;
            int lru_index = 0;
            int min_time = time[0];
            for (int j = 1; j < frame_size; j++) {
                if (time[j] < min_time) {
                    min_time = time[j];
                    lru_index = j;
                }
            }
            frames[lru_index] = pages[i];
            time[lru_index] = counter;
            printf("Page %d caused a fault. Frames: ", pages[i]);
        } else {
            time[idx] = counter;
            printf("Page %d hit. Frames: ", pages[i]);
        }
        displayFrames(frames, frame_size);
    }
    return page_faults;
}

// -----------------------------------------------
// Optimal Page Replacement
// -----------------------------------------------
int optimal(int pages[], int n, int frame_size) {
    int frames[MAX_FRAMES];
    int page_faults = 0;

    for (int i = 0; i < frame_size; i++)
        frames[i] = -1;

    for (int i = 0; i < n; i++) {
        if (findInFrames(frames, frame_size, pages[i]) == -1) {
            page_faults++;
            int replace_index = -1;

            // Check if any frame is empty
            bool empty_found = false;
            for (int j = 0; j < frame_size; j++) {
                if (frames[j] == -1) {
                    replace_index = j;
                    empty_found = true;
                    break;
                }
            }

            if (!empty_found) {
                int farthest = i, max_dist = -1;
                for (int j = 0; j < frame_size; j++) {
                    int k;
                    for (k = i + 1; k < n; k++) {
                        if (frames[j] == pages[k])
                            break;
                    }
                    if (k == n) { // Not used again
                        replace_index = j;
                        break;
                    } else if (k > max_dist) {
                        max_dist = k;
                        replace_index = j;
                    }
                }
            }

            frames[replace_index] = pages[i];
            printf("Page %d caused a fault. Frames: ", pages[i]);
        } else {
            printf("Page %d hit. Frames: ", pages[i]);
        }
        displayFrames(frames, frame_size);
    }

    return page_faults;
}
