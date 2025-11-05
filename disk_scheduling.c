#include <stdio.h>
#include <stdlib.h>

void print_sequence(int seq[], int n) {
    for (int i = 0; i < n; ++i) {
        if (i) printf(" -> ");
        printf("%d", seq[i]);
    }
    printf("\n");
}

// SSTF (Shortest Seek Time First)
void sstf(int head, int req[], int n) {
    int visited[1000] = {0};
    int pos = head;
    int seq[1005];
    seq[0] = head;
    int idx = 1;
    int total = 0;

    for (int served = 0; served < n; served++) {
        int best = -1;
        int bestdist = 1 << 30;
        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                int d = abs(req[i] - pos);
                if (d < bestdist) { bestdist = d; best = i; }
            }
        }
        visited[best] = 1;
        total += bestdist;
        pos = req[best];
        seq[idx++] = pos;
    }

    printf("SSTF Sequence:\n");
    print_sequence(seq, idx);
    printf("Total head movement = %d\n\n", total);
}

// SCAN (Elevator Algorithm)
void scan_algo(int head, int req[], int n, int end_track) {
    int right[1000], left[1000];
    int rcount = 0, lcount = 0;

    for (int i = 0; i < n; ++i) {
        if (req[i] >= head)
            right[rcount++] = req[i];
        else
            left[lcount++] = req[i];
    }

    // Sort right ascending
    for (int i = 0; i < rcount - 1; ++i)
        for (int j = i + 1; j < rcount; ++j)
            if (right[i] > right[j]) {
                int t = right[i]; right[i] = right[j]; right[j] = t;
            }

    // Sort left descending
    for (int i = 0; i < lcount - 1; ++i)
        for (int j = i + 1; j < lcount; ++j)
            if (left[i] < left[j]) {
                int t = left[i]; left[i] = left[j]; left[j] = t;
            }

    int seq[2005];
    int idx = 0, pos = head, total = 0;
    seq[idx++] = pos;

    // Move toward higher tracks
    for (int i = 0; i < rcount; ++i) {
        total += abs(right[i] - pos);
        pos = right[i];
        seq[idx++] = pos;
    }

    // Go to end of disk
    total += abs(end_track - pos);
    pos = end_track;
    seq[idx++] = pos;

    // Reverse and service left
    for (int i = 0; i < lcount; ++i) {
        total += abs(left[i] - pos);
        pos = left[i];
        seq[idx++] = pos;
    }

    printf("SCAN Sequence (move towards higher tracks first, then reverse):\n");
    print_sequence(seq, idx);
    printf("Total head movement = %d\n\n", total);
}

// C-LOOK (Circular LOOK)
void c_look(int head, int req[], int n) {
    int right[1000], left[1000];
    int rcount = 0, lcount = 0;

    for (int i = 0; i < n; ++i) {
        if (req[i] >= head)
            right[rcount++] = req[i];
        else
            left[lcount++] = req[i];
    }

    // Sort right ascending
    for (int i = 0; i < rcount - 1; ++i)
        for (int j = i + 1; j < rcount; ++j)
            if (right[i] > right[j]) {
                int t = right[i]; right[i] = right[j]; right[j] = t;
            }

    // Sort left ascending
    for (int i = 0; i < lcount - 1; ++i)
        for (int j = i + 1; j < lcount; ++j)
            if (left[i] > left[j]) {
                int t = left[i]; left[i] = left[j]; left[j] = t;
            }

    int seq[2005], idx = 0, pos = head, total = 0;
    seq[idx++] = pos;

    // Service higher tracks first
    for (int i = 0; i < rcount; ++i) {
        total += abs(right[i] - pos);
        pos = right[i];
        seq[idx++] = pos;
    }

    // Jump to the lowest request (circular move)
    if (lcount > 0) {
        total += abs(pos - left[0]);
        pos = left[0];
        seq[idx++] = pos;

        for (int i = 1; i < lcount; ++i) {
            total += abs(left[i] - pos);
            pos = left[i];
            seq[idx++] = pos;
        }
    }

    printf("C-LOOK Sequence (move to higher tracks, then circularly to smallest pending request):\n");
    print_sequence(seq, idx);
    printf("Total head movement = %d\n\n", total);
}

// ----------------------
// Main Program
// ----------------------
int main() {
    int n;
    printf("Enter number of requests: ");
    scanf("%d", &n);

    int req[1000];
    printf("Enter request queue (space separated):\n");
    for (int i = 0; i < n; ++i)
        scanf("%d", &req[i]);

    int head;
    printf("Enter initial head position: ");
    scanf("%d", &head);

    int disk_end = 199;  // Assuming disk track range 0–199

    printf("\n--- Results ---\n\n");
    sstf(head, req, n);
    scan_algo(head, req, n, disk_end);
    c_look(head, req, n);

    return 0;
}
