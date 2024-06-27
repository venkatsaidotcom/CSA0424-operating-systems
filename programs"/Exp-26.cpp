#include <stdio.h>
#include <stdlib.h>

void createFile(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error creating file");
        exit(EXIT_FAILURE);
    }
    printf("File '%s' created successfully.\n", filename);
    fclose(file);
}

void writeFile(const char *filename, const char *content) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error writing to file");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "%s", content);
    printf("Content written to file '%s' successfully.\n", filename);
    fclose(file);
}

void readFile(const char *filename) {
    char ch;
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error reading file");
        exit(EXIT_FAILURE);
    }
    printf("Reading file '%s':\n", filename);
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }
    printf("\n");
    fclose(file);
}

void deleteFile(const char *filename) {
    if (remove(filename) == 0) {
        printf("File '%s' deleted successfully.\n", filename);
    } else {
        perror("Error deleting file");
    }
}

int main() {
    const char *filename = "example.txt";
    const char *content = "Hello, world!";

    // Create a file
    createFile(filename);

    // Write to the file
    writeFile(filename, content);

    // Read from the file
    readFile(filename);

    // Delete the file
    deleteFile(filename);

    return 0;
}

