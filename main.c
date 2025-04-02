#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t lock; // Mutex lock for shared variable
int shared_data = 0; // Shared variable

void* writer_thread(void* arg) {
    for (int i = 1; i <= 5; i++) {
        pthread_mutex_lock(&lock);
        shared_data = i * 10; // Writing new value
        printf("Writer Thread: Wrote %d\n", shared_data);
        pthread_mutex_unlock(&lock);
        sleep(1); // Simulating delay
    }
    return NULL;
}

void* reader_thread(void* arg) {
    for (int i = 1; i <= 5; i++) {
        pthread_mutex_lock(&lock);
        printf("Reader Thread: Read %d\n", shared_data);
        pthread_mutex_unlock(&lock);
        sleep(1); // Simulating delay
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;

    // Initialize mutex
    if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("Mutex init failed\n");
        return 1;
    }

    // Create threads
    pthread_create(&t1, NULL, writer_thread, NULL);
    pthread_create(&t2, NULL, reader_thread, NULL);

    // Wait for threads to complete
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    // Destroy mutex
    pthread_mutex_destroy(&lock);

    printf("Program finished.\n");
    return 0;
}