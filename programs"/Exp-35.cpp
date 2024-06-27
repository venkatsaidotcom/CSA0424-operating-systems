#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 100
#define MAX_FILES 10

// Structure to represent a file
struct File {
    int indexBlock[MAX_BLOCKS];  // Array to hold index block entries
    int numBlocks;               // Number of blocks allocated to the file
};

// Function to initialize a file with empty index blocks
void initializeFile(struct File *file) {
    file->numBlocks = 0;
    for (int i = 0; i < MAX_BLOCKS; ++i) {
        file->indexBlock[i] = -1;  // Initialize all index block entries to -1 (indicating empty)
    }
}

// Function to allocate blocks to a file
void allocateBlocks(struct File *file, int numAllocated) {
    if (file->numBlocks + numAllocated > MAX_BLOCKS) {
        printf("Error: File size exceeds maximum block limit.\n");
        return;
    }

    // Allocate blocks by updating index block entries
    for (int i = 0; i < numAllocated; ++i) {
        file->indexBlock[file->numBlocks + i] = file->numBlocks + i;
    }

    file->numBlocks += numAllocated;
}

// Function to display allocated blocks of a file
void displayFileBlocks(struct File *file) {
    printf("Allocated blocks for the file:\n");
    for (int i = 0; i < file->numBlocks; ++i) {
        printf("%d ", file->indexBlock[i]);
    }
    printf("\n");
}

int main() {
    struct File files[MAX_FILES];
    int choice, fileIndex, numBlocks;

    // Initialize all files
    for (int i = 0; i < MAX_FILES; ++i) {
        initializeFile(&files[i]);
    }

    do {
        printf("\nFile Allocation Menu\n");
        printf("1. Allocate blocks to a file\n");
        printf("2. Display allocated blocks of a file\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter file index (0 to %d): ", MAX_FILES - 1);
                scanf("%d", &fileIndex);
                printf("Enter number of blocks to allocate: ");
                scanf("%d", &numBlocks);
                allocateBlocks(&files[fileIndex], numBlocks);
                break;
            case 2:
                printf("Enter file index (0 to %d): ", MAX_FILES - 1);
                scanf("%d", &fileIndex);
                displayFileBlocks(&files[fileIndex]);
                break;
            case 3:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please enter again.\n");
        }
    } while (choice != 3);

    return 0;
}

