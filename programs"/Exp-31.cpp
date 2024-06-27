#include <stdio.h>
#include <stdbool.h>

#define FRAME_SIZE 3 // Size of the page frame (number of frames)

// Function to check if a page is already in memory
bool isInMemory(int page, int frames[], int frameSize) {
    for (int i = 0; i < frameSize; ++i) {
        if (frames[i] == page) {
            return true;
        }
    }
    return false;
}

// Function to display the current state of memory frames
void displayFrames(int frames[], int frameSize) {
    printf("Current memory state: ");
    for (int i = 0; i < frameSize; ++i) {
        if (frames[i] == -1) {
            printf("- ");
        } else {
            printf("%d ", frames[i]);
        }
    }
    printf("\n");
}

// Function to simulate FIFO page replacement algorithm
void FIFO(int pages[], int page_count, int frameSize) {
    int frames[frameSize]; // Array to store current memory frames
    int frameIndex = 0; // Index to keep track of oldest frame to replace
    int pageFaults = 0; // Count of page faults

    // Initialize frames with -1 to indicate empty frames
    for (int i = 0; i < frameSize; ++i) {
        frames[i] = -1;
    }

    // Iterate over each page in sequence
    for (int i = 0; i < page_count; ++i) {
        printf("Accessing page %d...\n", pages[i]);
        
        // If page fault occurs (page is not in memory)
        if (!isInMemory(pages[i], frames, frameSize)) {
            frames[frameIndex] = pages[i]; // Replace the oldest frame
            frameIndex = (frameIndex + 1) % frameSize; // Update oldest frame index
            pageFaults++; // Increment page fault count
            displayFrames(frames, frameSize); // Display current memory state
        } else {
            printf("Page %d is already in memory.\n", pages[i]);
            displayFrames(frames, frameSize); // Display current memory state
        }
    }

    printf("\nTotal Page Faults: %d\n", pageFaults);
}

int main() {
    int pages[] = {1, 2, 3, 4, 2, 1, 5, 6, 2, 1, 2, 3, 7, 6, 3, 2, 1, 2, 3, 6};
    int page_count = sizeof(pages) / sizeof(pages[0]);
    int frameSize = FRAME_SIZE;

    printf("Simulation of FIFO Page Replacement Algorithm:\n");
    FIFO(pages, page_count, frameSize);

    return 0;
}

