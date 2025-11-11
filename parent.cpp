// parent.cpp
#include <bits/stdc++.h> // Includes iostream, vector, algorithm, etc.
using namespace std;

// C headers for OS system calls
// These are still needed for POSIX functions
#include <unistd.h>     // For fork(), execve()
#include <sys/wait.h>   // For wait()
#include <cstdlib>      // For exit(), perror(), malloc()
#include <cstdio>       // For sprintf()

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    sort(arr.begin(), arr.end());

    cout << "Parent sorted array: ";
    for (int val : arr) {
        cout << val << " ";
    }
    cout << endl;

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid == 0) {
        char *args[n + 2];
        args[0] = (char*)"./child";

        for (int i = 0; i < n; i++) {
            char *buf = (char*)malloc(12);
            sprintf(buf, "%d", arr[i]);
            args[i + 1] = buf;
        }
        args[n + 1] = NULL;

        execve("./child", args, NULL);

    } else {
        wait(NULL);
        cout << "Parent: Child process finished." << endl;
    }
    return 0;
}