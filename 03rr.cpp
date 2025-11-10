#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    int numberOfProcesses;               // Total number of processes
    int timeQuantum;                     // Fixed time CPU gives to each process
    int burstTime[10];                   // Burst Time: total time required by each process
    int remainingTime[10];               // Remaining Time: how much time is left for each process
    int waitingTime[10] = {0};           // Waiting Time: total waiting time for each process
    int turnaroundTime[10] = {0};        // Turnaround Time: total time from arrival to completion

    // Input number of processes
    cout << "Enter number of processes: ";
    cin >> numberOfProcesses;

    // Input burst time for each process
    cout << "Enter burst times:\n";
    for (int i = 0; i < numberOfProcesses; i++) {
        cout << "P" << i + 1 << ": ";
        cin >> burstTime[i];
        remainingTime[i] = burstTime[i]; // Initially remaining time = burst time
    }

    // Input Time Quantum
    cout << "Enter Time Quantum: ";
    cin >> timeQuantum;

    int currentTime = 0; // Keeps track of total time elapsed
    bool allDone;        // Flag to check if all processes are finished

    // Round Robin Scheduling Simulation
    do {
        allDone = true; // Assume all processes are done initially

        for (int i = 0; i < numberOfProcesses; i++) {
            if (remainingTime[i] > 0) {          // If process still needs CPU
                allDone = false;                 // There’s at least one process left

                if (remainingTime[i] > timeQuantum) {
                    // Process runs for full time quantum
                    currentTime += timeQuantum;
                    remainingTime[i] -= timeQuantum;
                } 
                else {
                    // Process finishes before or exactly at time quantum
                    currentTime += remainingTime[i];
                    waitingTime[i] = currentTime - burstTime[i]; // Time spent waiting
                    remainingTime[i] = 0; // Process completed
                }
            }
        }
    } while (!allDone); // Repeat until all processes finish

    // Calculate and display results
    float totalWaitingTime = 0, totalTurnaroundTime = 0;

    cout << "\nProcess\tWaiting Time\tTurnaround Time\n";
    for (int i = 0; i < numberOfProcesses; i++) {
        turnaroundTime[i] = burstTime[i] + waitingTime[i];
        totalWaitingTime += waitingTime[i];
        totalTurnaroundTime += turnaroundTime[i];

        cout << "P" << i + 1 << "\t\t" 
             << waitingTime[i] << "\t\t" 
             << turnaroundTime[i] << "\n";
    }

    // Display averages
    cout << fixed << setprecision(2);
    cout << "\nAverage Waiting Time = " << totalWaitingTime / numberOfProcesses;
    cout << "\nAverage Turnaround Time = " << totalTurnaroundTime / numberOfProcesses << endl;

    return 0;
}
