#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 3    // Maximum number of frames in memory
#define MAX_PAGES 20    // Maximum number of pages referenced

int main() {
    int reference_string[MAX_PAGES] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};  // Reference string
    int num_pages = 12;  // Number of pages in the reference string

    int frames[MAX_FRAMES];  // Array to store the frames in memory
    int page_faults = 0;     // Counter for page faults
    int i, j, k;

    // Initialize frames as empty (-1 indicates no page loaded)
    for (i = 0; i < MAX_FRAMES; i++)
        frames[i] = -1;

    printf("Reference String: ");
    for (i = 0; i < num_pages; i++)
        printf("%d ", reference_string[i]);
    printf("\n");

    // Simulating the optimal page replacement algorithm
    for (i = 0; i < num_pages; i++) {
        int page = reference_string[i];
        int page_found = 0;

        // Check if page is already in frames
        for (j = 0; j < MAX_FRAMES; j++) {
            if (frames[j] == page) {
                page_found = 1;
                break;
            }
        }

        // If page is not in frames, replace a page using optimal replacement strategy
        if (!page_found) {
            page_faults++;

            // Find the page that will not be used for the longest time in the future
            int farthest = i;
            int replace_page = -1;
            for (j = 0; j < MAX_FRAMES; j++) {
                int current_page = frames[j];
                int found_future = 0;
                for (k = i + 1; k < num_pages; k++) {
                    if (current_page == reference_string[k]) {
                        found_future = 1;
                        if (k > farthest) {
                            farthest = k;
                            replace_page = j;
                        }
                        break;
                    }
                }
                if (!found_future) {
                    replace_page = j;
                    break;
                }
            }

            // Replace the selected page
            frames[replace_page] = page;
        }

        // Print current frames
        printf("Frames: ");
        for (j = 0; j < MAX_FRAMES; j++) {
            if (frames[j] == -1)
                printf("- ");
            else
                printf("%d ", frames[j]);
        }
        printf("\n");
    }

    printf("Total Page Faults: %d\n", page_faults);

    return 0;
}

