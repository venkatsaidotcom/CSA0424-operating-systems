#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    char filename[] = "testfile.txt";
    int fd;

    // Create a file with read and write permissions for owner, read-only for others
    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd == -1) {
        perror("Failed to create file");
        return 1;
    }

    printf("File '%s' created successfully.\n", filename);
    close(fd);

    // Change file permissions to read-only for owner, group, and others
    if (chmod(filename, S_IRUSR | S_IRGRP | S_IROTH) == -1) {
        perror("Failed to change file permissions");
        return 1;
    }

    printf("File permissions changed successfully.\n");

    // Check current user's effective UID and GID
    printf("Current user's effective UID: %d\n", geteuid());
    printf("Current user's effective GID: %d\n", getegid());

    // Attempt to open the file for writing
    fd = open(filename, O_WRONLY);
    if (fd == -1) {
        perror("Failed to open file for writing");
        return 1;
    }

    // Write to the file
    if (write(fd, "Hello, World!\n", 14) != 14) {
        perror("Write error");
        return 1;
    }

    printf("Data written to file successfully.\n");

    close(fd);

    return 0;
}

