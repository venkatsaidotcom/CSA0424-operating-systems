#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 100
#define MAX_FILES 10

// Structure to represent a block on disk
struct DiskBlock {
    int data;                // Data stored in the block (for simplicity)
    struct DiskBlock *next;  // Pointer to the next block in the file
};

// Structure to represent a file
struct File {
    struct DiskBlock *firstBlock;  // Pointer to the first block of the file
    struct DiskBlock *lastBlock;   // Pointer to the last block of the file
};

// Function to initialize a file
void initializeFile(struct File *file) {
    file->firstBlock = NULL;
    file->lastBlock = NULL;
}

// Function to add a block to the end of the file
void addBlock(struct File *file, struct DiskBlock *block) {
    if (file->firstBlock == NULL) {
        file->firstBlock = block;
        file->lastBlock = block;
        block->next = NULL;
    } else {
        file->lastBlock->next = block;
        file->lastBlock = block;
        block->next = NULL;
    }
}

// Function to display blocks of a file
void displayFileBlocks(struct File *file) {
    printf("Blocks of the file:\n");
    struct DiskBlock *current = file->firstBlock;
    while (current != NULL) {
        printf("%p -> ", (void *)current);
        current = current->next;
    }
    printf("NULL\n");
}

int main() {
    struct File files[MAX_FILES];
    struct DiskBlock diskBlocks[MAX_BLOCKS];
    int choice, fileIndex;
    int blockIndex = 0;

    // Initialize all files
    for (int i = 0; i < MAX_FILES; ++i) {
        initializeFile(&files[i]);
    }

    do {
        printf("\nLinked Allocation Menu\n");
        printf("1. Allocate blocks to a file\n");
        printf("2. Display blocks of a file\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (blockIndex >= MAX_BLOCKS) {
                    printf("Error: Maximum number of blocks reached.\n");
                    break;
                }
                printf("Enter file index (0 to %d): ", MAX_FILES - 1);
                scanf("%d", &fileIndex);
                // Allocate a new block
                struct DiskBlock *newBlock = &diskBlocks[blockIndex++];
                printf("Allocating block %p to file %d.\n", (void *)newBlock, fileIndex);
                addBlock(&files[fileIndex], newBlock);
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

