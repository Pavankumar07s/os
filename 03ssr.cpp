#include <iostream>
#include <iomanip>
#include <climits> // for INT_MAX
using namespace std;

int main() {
    int numberOfProcesses;
    cout << "Enter number of processes: ";
    cin >> numberOfProcesses;

    int arrivalTime[10], burstTime[10], remainingTime[10];
    int waitingTime[10] = {0}, turnaroundTime[10] = {0};
    int processCompleted = 0, currentTime = 0, smallestProcess;

    // Input process data
    for (int i = 0; i < numberOfProcesses; i++) {
        cout << "Enter Arrival Time and Burst Time for Process P" << i + 1 << ": ";
        cin >> arrivalTime[i] >> burstTime[i];
        remainingTime[i] = burstTime[i]; // Initially, remaining time = burst time
    }

    float totalWaitingTime = 0, totalTurnaroundTime = 0;

    // Simulation: run until all processes are completed
    while (processCompleted < numberOfProcesses) {
        smallestProcess = -1;
        int minimumRemainingTime = INT_MAX;

        // Find the process with the smallest remaining time among those that have arrived
        for (int i = 0; i < numberOfProcesses; i++) {
            if (arrivalTime[i] <= currentTime && remainingTime[i] > 0 && remainingTime[i] < minimumRemainingTime) {
                minimumRemainingTime = remainingTime[i];
                smallestProcess = i;
            }
        }

        // If no process has arrived yet, move time forward
        if (smallestProcess == -1) {
            currentTime++;
            continue;
        }

        // Execute the selected process for 1 unit of time
        remainingTime[smallestProcess]--;
        currentTime++;

        // When the process finishes
        if (remainingTime[smallestProcess] == 0) {
            processCompleted++;

            int completionTime = currentTime;
            turnaroundTime[smallestProcess] = completionTime - arrivalTime[smallestProcess];
            waitingTime[smallestProcess] = turnaroundTime[smallestProcess] - burstTime[smallestProcess];

            totalWaitingTime += waitingTime[smallestProcess];
            totalTurnaroundTime += turnaroundTime[smallestProcess];

            cout << "P" << smallestProcess + 1
                 << " completed at time " << completionTime
                 << " | WT = " << waitingTime[smallestProcess]
                 << " | TAT = " << turnaroundTime[smallestProcess] << endl;
        }
    }

    // Display averages
    cout << fixed << setprecision(2);
    cout << "\nAverage Waiting Time = " << totalWaitingTime / numberOfProcesses;
    cout << "\nAverage Turnaround Time = " << totalTurnaroundTime / numberOfProcesses << endl;

    return 0;
}
