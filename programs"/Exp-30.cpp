#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Thread function to be executed
void* threadFunc(void* arg) {
    printf("Thread is running. Thread ID: %ld\n", pthread_self());
    pthread_exit(NULL);  // Exit the thread
}

int main() {
    pthread_t thread1, thread2;
    int res;

    // (i) Create a new thread
    res = pthread_create(&thread1, NULL, threadFunc, NULL);
    if (res != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }
    printf("Thread created with ID: %ld\n", thread1);

    // (ii) Join the thread (wait for it to complete)
    res = pthread_join(thread1, NULL);
    if (res != 0) {
        perror("Thread join failed");
        exit(EXIT_FAILURE);
    }
    printf("Thread joined successfully\n");

    // (iii) Create another thread to demonstrate pthread_equal
    res = pthread_create(&thread2, NULL, threadFunc, NULL);
    if (res != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }

    // Check if two thread IDs are equal
    if (pthread_equal(thread1, thread2)) {
        printf("Thread1 and Thread2 are equal\n");
    } else {
        printf("Thread1 and Thread2 are not equal\n");
    }

    // Join the second thread
    res = pthread_join(thread2, NULL);
    if (res != 0) {
        perror("Thread join failed");
        exit(EXIT_FAILURE);
    }
    printf("Thread2 joined successfully\n");

    return 0;
}

