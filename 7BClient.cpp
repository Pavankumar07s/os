#include <bits/stdc++.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
using namespace std;

int main() {
    key_t key = ftok("shmfile", 65);   // Generate unique key
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT); // Create shared memory

    char *str = (char*) shmat(shmid, NULL, 0); // Attach memory

    cout << "Write Data: ";
    cin.getline(str, 1024); // Write into shared memory

    cout << "Data written in memory: " << str << endl;

    shmdt(str); // Detach
    return 0;
}
