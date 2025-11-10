#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
using namespace std;

#define SIZE 5

int buffer[SIZE];
int in = 0, out = 0;
sem_t empty_sem, full;
pthread_mutex_t mutex;

void* producer(void* arg) {
    for (int i = 1; i <= 10; i++) {
        sem_wait(&empty_sem);              // Wait for empty slot
        pthread_mutex_lock(&mutex);    // Enter critical section

        buffer[in] = i;
        cout << "Producer produced: " << i << endl;
        in = (in + 1) % SIZE;

        pthread_mutex_unlock(&mutex);  // Exit critical section
        sem_post(&full);               // Signal that a slot is full
        sleep(1);                      // Simulate production delay
    }
    return nullptr;
}

void* consumer(void* arg) {
    for (int i = 1; i <= 10; i++) {
        sem_wait(&full);               // Wait for full slot
        pthread_mutex_lock(&mutex);    // Enter critical section

        int item = buffer[out];
        cout << "\tConsumer consumed: " << item << endl;
        out = (out + 1) % SIZE;

        pthread_mutex_unlock(&mutex);  // Exit critical section
        sem_post(&empty_sem);              // Signal that a slot is empty
        sleep(2);                      // Simulate consumption delay
    }
    return nullptr;
}

int main() {
    pthread_t prod, cons;

    sem_init(&empty_sem, 0, SIZE);  // Initially, buffer has SIZE empty slots
    sem_init(&full, 0, 0);      // Initially, buffer has 0 full slots
    pthread_mutex_init(&mutex, nullptr);

    // Create producer and consumer threads
    pthread_create(&prod, nullptr, producer, nullptr);
    pthread_create(&cons, nullptr, consumer, nullptr);

    // Wait for threads to complete
    pthread_join(prod, nullptr);
    pthread_join(cons, nullptr);

    // Cleanup
    sem_destroy(&empty_sem);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
