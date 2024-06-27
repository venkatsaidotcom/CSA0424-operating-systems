#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RECORDS 100   // Maximum number of records
#define MAX_LENGTH 100    // Maximum length of each record

struct File {
    char records[MAX_RECORDS][MAX_LENGTH];
    int num_records;
};

// Function to initialize the file
void initializeFile(struct File *file) {
    file->num_records = 0;
}

// Function to add a record to the file
void addRecord(struct File *file, const char *record) {
    if (file->num_records < MAX_RECORDS) {
        strcpy(file->records[file->num_records], record);
        file->num_records++;
        printf("Record added successfully.\n");
    } else {
        printf("File is full. Cannot add more records.\n");
    }
}

// Function to display all records in the file
void displayFile(struct File *file) {
    printf("Records in the file:\n");
    for (int i = 0; i < file->num_records; ++i) {
        printf("%d: %s\n", i + 1, file->records[i]);
    }
}

int main() {
    struct File file;
    initializeFile(&file);

    int choice;
    char record[MAX_LENGTH];
    
    do {
        printf("\nFile Allocation Strategy Simulation\n");
        printf("1. Add a record\n");
        printf("2. Display all records\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter record to add: ");
                getchar(); // Clearing the input buffer
                fgets(record, MAX_LENGTH, stdin);
                record[strcspn(record, "\n")] = '\0'; // Remove trailing newline character
                addRecord(&file, record);
                break;
            case 2:
                displayFile(&file);
                break;
            case 3:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please enter again.\n");
        }
    } while (choice != 3);

    return 0;
}

