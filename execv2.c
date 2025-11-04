#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // Display all numbers in reverse order
    printf("Numbers in reverse order: ");
    for (int i = argc - 1; i >= 1; i--) {
        printf("%d ", atoi(argv[i]));
    }
    printf("\n");

    // Binary search
    int low = 1;
    int high = argc - 1;
    int found = 0;
    int num;

    printf("Enter number to search: ");
    scanf("%d", &num);

    while (low <= high) {
        int mid = low + (high - low) / 2;
        int val = atoi(argv[mid]);

        if (val == num) {
            found = 1;
            printf("Found %d at position %d\n", num, mid);
            break;
        } else if (val < num) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    if (!found) {
        printf("%d not found\n", num);
    }

    printf("Finish\n");
    return 0;
}
