#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define MAX 20
using namespace std;

void bubbleAsc(int arr[], int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
}

void bubbleDesc(int arr[], int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] < arr[j + 1])
                swap(arr[j], arr[j + 1]);
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        cout << "\t" << arr[i];
    cout << "\n\n";
}

int main() {
    int n, arr[MAX];
    cout << "\nHOW MANY NOS DO YOU WANT IN ARRAY: ";
    cin >> n;

    cout << "ENTER ARRAY ELEMENTS: ";
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    pid_t pid = fork();

    if (pid == 0) {
        // Child process → Orphan state
        cout << "\n\t********** ORPHAN STATE **********\n";
        sleep(5);
        cout << "\n\tCHILD PID: " << getpid();
        cout << "\n\tPARENT PID (after becoming orphan): " << getppid() << endl;
        system("ps -el | grep init");
        cout << "\n\nARRAY IN ASCENDING ORDER: ";
        bubbleAsc(arr, n);
        printArray(arr, n);
    }
    else if (pid > 0) {
        // Parent process → Zombie state
        cout << "\n\t********** ZOMBIE STATE **********\n";
        system("ps -el | grep Z");
        int f = wait(0);
        cout << "\n\tTERMINATED CHILD PID: " << f;
        cout << "\n\tPARENT PID (MAIN): " << getpid();
        cout << "\n\tPARENT'S PARENT (BASH) PID: " << getppid();
        cout << "\n\nARRAY IN DESCENDING ORDER: ";
        bubbleDesc(arr, n);
        printArray(arr, n);
    }
    else {
        cerr << "\nERROR IN FORK!!" << endl;
    }

    return 0;
}
