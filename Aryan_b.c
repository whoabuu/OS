// FILE: b.c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    // Print in reverse order
    for (int i = argc - 1; i >= 1; i--) {
        printf("%d ", atoi(argv[i]));
    }
    printf("\n");

    int low = 1;
    int high = argc - 1;
    int found = 0;
    int num;

    printf("Enter num: ");
    scanf("%d", &num);

    // Binary search
    while (low <= high) {
        int mid = low + (high - low) / 2;
        int val = atoi(argv[mid]);

        if (val == num) {
            found = 1;
            printf("Found");
            break;
        } else if (val < num) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    if (!found) {
        printf("not Found");
    }

    printf("Finish");
    return 0;
}
