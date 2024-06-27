#include <stdio.h>
#include <stdlib.h>

// Function to sort the request array in ascending order
void sort_requests(int *requests, int num_requests) {
    int i, j, temp;
    for (i = 0; i < num_requests - 1; i++) {
        for (j = 0; j < num_requests - i - 1; j++) {
            if (requests[j] > requests[j + 1]) {
                temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }
}

// Function to simulate the SCAN disk scheduling algorithm
void scan_disk(int *requests, int num_requests, int head_position, int direction, int disk_size) {
    int total_movement = 0;
    int current_position = head_position;

    // Sort requests
    sort_requests(requests, num_requests);

    // Find index of current head position in sorted array
    int i;
    for (i = 0; i < num_requests; i++) {
        if (requests[i] >= head_position) {
            break;
        }
    }

    // If direction is 0, simulate right scan
    if (direction == 0) {
        printf("Sequence of head movements: %d -> ", current_position);
        for (; i < num_requests; i++) {
            printf("%d -> ", requests[i]);
            total_movement += abs(requests[i] - current_position);
            current_position = requests[i];
        }
        printf("%d -> %d\n", disk_size - 1, 0);
        total_movement += disk_size - 1 - current_position;
        current_position = 0;
        for (i = 0; i < num_requests && requests[i] < head_position; i++) {
            printf("%d -> ", requests[i]);
            total_movement += abs(requests[i] - current_position);
            current_position = requests[i];
        }
    } else {
        // If direction is 1, simulate left scan
        printf("Sequence of head movements: %d -> ", current_position);
        for (; i >= 0; i--) {
            printf("%d -> ", requests[i]);
            total_movement += abs(requests[i] - current_position);
            current_position = requests[i];
        }
        printf("0 -> ");
        total_movement += current_position;
        current_position = 0;
        for (i = num_requests - 1; i >= 0 && requests[i] > head_position; i--) {
            printf("%d -> ", requests[i]);
            total_movement += abs(requests[i] - current_position);
            current_position = requests[i];
        }
    }
    printf("\nTotal head movement: %d\n", total_movement);
}

int main() {
    int requests[] = {98, 183, 37, 122, 14, 124, 65, 67};  // Example request array
    int num_requests = sizeof(requests) / sizeof(requests[0]);
    int head_position = 53;  // Starting head position
    int direction = 0;  // 0 for right, 1 for left
    int disk_size = 200;  // Total size of the disk

    printf("SCAN Disk Scheduling Algorithm Simulation\n");
    printf("Initial head position: %d\n", head_position);
    printf("Disk size: %d\n", disk_size);
    scan_disk(requests, num_requests, head_position, direction, disk_size);

    return 0;
}

