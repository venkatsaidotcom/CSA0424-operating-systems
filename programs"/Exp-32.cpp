#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_FRAMES 3  // Maximum number of frames in memory

// Function declarations
int lruPageReplacement(int pages[], int n, int capacity);

int main() {
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};  // Reference string example
    int n = sizeof(pages) / sizeof(pages[0]);
    int capacity = MAX_FRAMES;

    int pageFaults = lruPageReplacement(pages, n, capacity);

    printf("Total page faults: %d\n", pageFaults);

    return 0;
}

// Function to simulate LRU page replacement algorithm
int lruPageReplacement(int pages[], int n, int capacity) {
    int pageFaults = 0;
    int frames[capacity];
    int time[capacity];  // To store the time of last use of each frame

    for (int i = 0; i < capacity; i++) {
        frames[i] = -1;  // Initialize frames with -1 indicating empty
        time[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        bool found = false;

        // Check if page is already in memory
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == pages[i]) {
                found = true;
                time[j] = i;  // Update time of last use to current reference index
                break;
            }
        }

        // If page is not present in memory, replace the least recently used page
        if (!found) {
            int lruIndex = 0;
            // Find the frame with the least recently used page
            for (int j = 1; j < capacity; j++) {
                if (time[j] < time[lruIndex]) {
                    lruIndex = j;
                }
            }

            frames[lruIndex] = pages[i];  // Replace the least recently used page
            time[lruIndex] = i;  // Update time of last use to current reference index
            pageFaults++;
        }

        // Print the current state of frames after each page reference
        printf("Current frames: ");
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == -1) {
                printf(" - ");
            } else {
                printf(" %d ", frames[j]);
            }
        }
        printf("\n");
    }

    return pageFaults;
}

