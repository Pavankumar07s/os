#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
using namespace std;

sem_t x, wsem;
int readcount = 0;

void* reader(void* arg) {
    int id = (intptr_t)arg; // Reader ID

    while (true) {
        sem_wait(&x); //ye lock karta hai
        readcount++;
        if (readcount == 1)
            sem_wait(&wsem); // first reader locks writer

        ////ye hai crucial part
        sem_post(&x); //unlock karta hai
        cout << "Reader " << id << " is reading" << endl;
        sleep(1);
        sem_wait(&x); //yaha phir se lock karta hai
        readcount--;
        // yaha crucial part ends 


        if (readcount == 0)
            sem_post(&wsem); // last reader unlocks writer
        sem_post(&x);        //unlock karta hai

        sleep(1);
    }
    return nullptr;
}

void* writer(void* arg) {
    int id = (intptr_t)arg; // Writer ID

    while (true) {
        sem_wait(&wsem);
        cout << "\tWriter " << id << " is writing" << endl;
        sleep(2);
        sem_post(&wsem);
        sleep(1);
    }
    return nullptr;
}

int main() {
    pthread_t rtid1, rtid2, rtid3, wtid1, wtid2;

    sem_init(&x, 0, 1);
    sem_init(&wsem, 0, 1);

    // Create 3 readers and 2 writers
    pthread_create(&rtid1, nullptr, reader, (void*)1);
    pthread_create(&rtid2, nullptr, reader, (void*)2);
    pthread_create(&rtid3, nullptr, reader, (void*)3);
    pthread_create(&wtid1, nullptr, writer, (void*)1);
    pthread_create(&wtid2, nullptr, writer, (void*)2);

    // Wait for threads to complete (they run infinitely)
    pthread_join(rtid1, nullptr);
    pthread_join(rtid2, nullptr);
    pthread_join(rtid3, nullptr);
    pthread_join(wtid1, nullptr);
    pthread_join(wtid2, nullptr);

    sem_destroy(&x);
    sem_destroy(&wsem);

    return 0;
}
