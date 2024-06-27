#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 100   // Maximum number of disk requests

// Function to simulate FCFS disk scheduling algorithm
void fcfs(int requests[], int num_requests, int initial_position) {
    int current_position = initial_position;
    int total_head_movement = 0;

    printf("FCFS Disk Scheduling:\n");
    printf("Initial Head Position: %d\n", initial_position);
    printf("Sequence of head movement:\n");
    
    // Process each request in the order they are received
    for (int i = 0; i < num_requests; ++i) {
        int current_request = requests[i];
        printf("Move from %d to %d\n", current_position, current_request);
        total_head_movement += abs(current_request - current_position);
        current_position = current_request;
    }

    printf("Total Head Movement: %d\n", total_head_movement);
}

int main() {
    int requests[MAX_REQUESTS];
    int num_requests;
    int initial_position;

    // Input number of requests
    printf("Enter number of disk requests: ");
    scanf("%d", &num_requests);

    // Input disk requests
    printf("Enter the disk requests:\n");
    for (int i = 0; i < num_requests; ++i) {
        scanf("%d", &requests[i]);
    }

    // Input initial head position
    printf("Enter initial head position: ");
    scanf("%d", &initial_position);

    // Perform FCFS scheduling
    fcfs(requests, num_requests, initial_position);

    return 0;
}

