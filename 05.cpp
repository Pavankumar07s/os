#include <iostream>
#include <iomanip>
using namespace std;

int numProcesses, numResources;
int allocation[10][10], maxNeed[10][10], need[10][10], available[10], safeSeq[10];

void inputData();
void displayData();
bool checkSafeState();

int main() {
    cout << "Enter number of processes: ";
    cin >> numProcesses;
    cout << "Enter number of resources: ";
    cin >> numResources;

    inputData();
    displayData();

    if (checkSafeState())
        cout << "\n✅ System is in a SAFE state.\n";
    else
        cout << "\n❌ System is in an UNSAFE state.\n";

    return 0;
}

void inputData() {
    cout << "\n--- Enter Allocation Matrix ---\n";
    for (int i = 0; i < numProcesses; i++) {
        cout << "Process P" << i << ": ";
        for (int j = 0; j < numResources; j++)
            cin >> allocation[i][j];
    }

    cout << "\n--- Enter Maximum Matrix ---\n";
    for (int i = 0; i < numProcesses; i++) {
        cout << "Process P" << i << ": ";
        for (int j = 0; j < numResources; j++) {
            cin >> maxNeed[i][j];
            need[i][j] = maxNeed[i][j] - allocation[i][j];
        }
    }

    cout << "\nEnter Available Resources: ";
    for (int j = 0; j < numResources; j++)
        cin >> available[j];
}

void displayData() {
    cout << "\nProcess\tAllocation\tMax\t\tNeed\n";
    for (int i = 0; i < numProcesses; i++) {
        cout << "P" << i << "\t";
        for (int j = 0; j < numResources; j++)
            cout << allocation[i][j] << " ";
        cout << "\t\t";
        for (int j = 0; j < numResources; j++)
            cout << maxNeed[i][j] << " ";
        cout << "\t\t";
        for (int j = 0; j < numResources; j++)
            cout << need[i][j] << " ";
        cout << "\n";
    }
}

bool checkSafeState() {
    int work[10], finish[10] = {0}, count = 0;

    for (int i = 0; i < numResources; i++)
        work[i] = available[i];

    while (count < numProcesses) {
        bool found = false;
        for (int i = 0; i < numProcesses; i++) {
            if (!finish[i]) {
                bool canRun = true;
                for (int j = 0; j < numResources; j++) {
                    if (need[i][j] > work[j]) {
                        canRun = false;
                        break;
                    }
                }
                if (canRun) {
                    for (int j = 0; j < numResources; j++)
                        work[j] += allocation[i][j];
                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = true;
                }
            }
        }
        if (!found)
            return false; // unsafe
    }

    cout << "\nSafe Sequence: ";
    for (int i = 0; i < numProcesses; i++)
        cout << "P" << safeSeq[i] << " ";
    cout << endl;

    return true; // safe
}
