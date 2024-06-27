#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 100

// Function declarations
void cscan(int requests[], int n, int start, int max);

int main() {
    int requests[MAX_REQUESTS];
    int n, start, max;

    // Input number of requests
    printf("Enter the number of requests: ");
    scanf("%d", &n);

    // Input requests
    printf("Enter the disk requests:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    // Input starting position of disk head
    printf("Enter the starting position of disk head: ");
    scanf("%d", &start);

    // Input maximum disk limit
    printf("Enter the maximum disk limit: ");
    scanf("%d", &max);

    // Perform C-SCAN scheduling
    cscan(requests, n, start, max);

    return 0;
}

// Function to simulate C-SCAN disk scheduling algorithm
void cscan(int requests[], int n, int start, int max) {
    int total_seek_time = 0;
    int current_position = start;
    int direction = 1;  // 1 for moving forward, -1 for moving backward

    // Sort requests to ensure they are in ascending order
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (requests[j] > requests[j + 1]) {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }

    // Finding the position of current request
    int current_request = 0;
    for (int i = 0; i < n; i++) {
        if (requests[i] >= start) {
            current_request = i;
            break;
        }
    }

    // Perform C-SCAN scheduling
    printf("Sequence of disk accesses:\n");

    // Move to the end of the disk
    while (current_request < n) {
        printf("%d ", requests[current_request]);
        total_seek_time += abs(current_position - requests[current_request]);
        current_position = requests[current_request];
        current_request++;
    }

    // Move to the beginning of the disk
    total_seek_time += abs(current_position - max);
    current_position = max;
    printf("%d ", max);

    // Move back to the start of the requests
    for (int i = 0; i < n; i++) {
        total_seek_time += abs(current_position - requests[i]);
        current_position = requests[i];
        printf("%d ", requests[i]);
    }

    printf("\nTotal seek time: %d\n", total_seek_time);
}

