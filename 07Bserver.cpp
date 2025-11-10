#include <bits/stdc++.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
using namespace std;

int main() {
    key_t key = ftok("shmfile", 65);   // Same key as server
    int shmid = shmget(key, 1024, 0666); // Locate same shared memory
    
    char *str = (char*) shmat(shmid, NULL, 0); // Attach

    cout << "Data read from memory: " << str << endl;

    shmdt(str); // Detach
    shmctl(shmid, IPC_RMID, NULL); // Remove memory
    return 0;
}
