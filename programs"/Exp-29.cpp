#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 10

// Buffer and its associated variables
int buffer[BUFFER_SIZE];
int count = 0;
int in = 0;
int out = 0;

// Semaphores and mutex
sem_t empty;
sem_t full;
pthread_mutex_t mutex;

// Producer function
void *producer(void *param) {
    int item;
    while (1) {
        // Produce an item
        item = rand() % 100;
        
        // Wait if buffer is full
        sem_wait(&empty);
        
        // Lock the buffer
        pthread_mutex_lock(&mutex);
        
        // Add the item to the buffer
        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;
        count++;
        printf("Producer produced: %d\n", item);
        
        // Unlock the buffer
        pthread_mutex_unlock(&mutex);
        
        // Signal that buffer is not empty
        sem_post(&full);
        
        // Simulate time taken to produce an item
        sleep(rand() % 3);
    }
}

// Consumer function
void *consumer(void *param) {
    int item;
    while (1) {
        // Wait if buffer is empty
        sem_wait(&full);
        
        // Lock the buffer
        pthread_mutex_lock(&mutex);
        
        // Remove the item from the buffer
        item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        count--;
        printf("Consumer consumed: %d\n", item);
        
        // Unlock the buffer
        pthread_mutex_unlock(&mutex);
        
        // Signal that buffer is not full
        sem_post(&empty);
        
        // Simulate time taken to consume an item
        sleep(rand() % 3);
    }
}

int main() {
    pthread_t producer_thread, consumer_thread;
    
    // Initialize semaphores
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    
    // Initialize mutex
    pthread_mutex_init(&mutex, NULL);
    
    // Create producer and consumer threads
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);
    
    // Wait for the threads to finish (they actually run indefinitely in this example)
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);
    
    // Destroy semaphores and mutex (unreachable in this example)
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);
    
    return 0;
}

