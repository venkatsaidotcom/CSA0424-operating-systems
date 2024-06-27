#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>

void demo_fcntl(const char *filename) {
    int fd = open(filename, O_RDWR);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Get file descriptor flags
    int flags = fcntl(fd, F_GETFL);
    if (flags == -1) {
        perror("fcntl");
        close(fd);
        exit(EXIT_FAILURE);
    }
    printf("File descriptor flags: %d\n", flags);

    // Set file descriptor flags
    if (fcntl(fd, F_SETFL, flags | O_APPEND) == -1) {
        perror("fcntl");
        close(fd);
        exit(EXIT_FAILURE);
    }
    printf("File descriptor flags set to O_APPEND.\n");

    close(fd);
}

void demo_lseek(const char *filename) {
    int fd = open(filename, O_RDWR);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Seek to the end of the file
    off_t offset = lseek(fd, 0, SEEK_END);
    if (offset == (off_t)-1) {
        perror("lseek");
        close(fd);
        exit(EXIT_FAILURE);
    }
    printf("File size: %ld bytes\n", offset);

    close(fd);
}

void demo_stat(const char *filename) {
    struct stat sb;

    if (stat(filename, &sb) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    printf("File type:                ");

    switch (sb.st_mode & S_IFMT) {
        case S_IFBLK:  printf("block device\n");            break;
        case S_IFCHR:  printf("character device\n");        break;
        case S_IFDIR:  printf("directory\n");               break;
        case S_IFIFO:  printf("FIFO/pipe\n");               break;
        case S_IFLNK:  printf("symlink\n");                 break;
        case S_IFREG:  printf("regular file\n");            break;
        case S_IFSOCK: printf("socket\n");                  break;
        default:       printf("unknown?\n");                break;
    }

    printf("I-node number:            %ld\n", (long) sb.st_ino);
    printf("Mode:                     %lo (octal)\n", (unsigned long) sb.st_mode);
    printf("Link count:               %ld\n", (long) sb.st_nlink);
    printf("Ownership:                UID=%ld   GID=%ld\n", (long) sb.st_uid, (long) sb.st_gid);
    printf("Preferred I/O block size: %ld bytes\n", (long) sb.st_blksize);
    printf("File size:                %lld bytes\n", (long long) sb.st_size);
    printf("Blocks allocated:         %lld\n", (long long) sb.st_blocks);
}

void demo_readdir(const char *dirpath) {
    DIR *dir;
    struct dirent *entry;

    if ((dir = opendir(dirpath)) == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <filename> <directory>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *filename = argv[1];
    const char *directory = argv[2];

    printf("Demonstrating fcntl:\n");
    demo_fcntl(filename);

    printf("\nDemonstrating lseek:\n");
    demo_lseek(filename);

    printf("\nDemonstrating stat:\n");
    demo_stat(filename);

    printf("\nDemonstrating readdir:\n");
    demo_readdir(directory);

    return 0;
}

