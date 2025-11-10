#include <stdio.h>

int numProcesses, numResources;
int allocation[10][10], maxNeed[10][10], need[10][10], available[10], safeSeq[10];

void inputData();
void displayData();
int checkSafeState();

int main() {
    printf("Enter number of processes: ");
    scanf("%d", &numProcesses);
    printf("Enter number of resources: ");
    scanf("%d", &numResources);

    inputData();
    displayData();

    if (checkSafeState())
        printf("\n✅ System is in a SAFE state.\n");
    else
        printf("\n❌ System is in an UNSAFE state.\n");

    return 0;
}

void inputData() {
    printf("\n--- Enter Allocation Matrix ---\n");
    for (int i = 0; i < numProcesses; i++) {
        printf("Process P%d: ", i);
        for (int j = 0; j < numResources; j++)
            scanf("%d", &allocation[i][j]);
    }

    printf("\n--- Enter Maximum Matrix ---\n");
    for (int i = 0; i < numProcesses; i++) {
        printf("Process P%d: ", i);
        for (int j = 0; j < numResources; j++) {
            scanf("%d", &maxNeed[i][j]);
            need[i][j] = maxNeed[i][j] - allocation[i][j];
        }
    }

    printf("\nEnter Available Resources: ");
    for (int j = 0; j < numResources; j++)
        scanf("%d", &available[j]);
}

void displayData() {
    printf("\nProcess\tAllocation\tMax\t\tNeed\n");
    for (int i = 0; i < numProcesses; i++) {
        printf("P%d\t", i);
        for (int j = 0; j < numResources; j++)
            printf("%d ", allocation[i][j]);
        printf("\t\t");
        for (int j = 0; j < numResources; j++)
            printf("%d ", maxNeed[i][j]);
        printf("\t\t");
        for (int j = 0; j < numResources; j++)
            printf("%d ", need[i][j]);
        printf("\n");
    }
}

int checkSafeState() {
    int work[10], finish[10] = {0}, count = 0;

    // Copy available to work
    for (int i = 0; i < numResources; i++)
        work[i] = available[i];

    while (count < numProcesses) {
        int found = 0;
        for (int i = 0; i < numProcesses; i++) {
            if (!finish[i]) {
                int canRun = 1;
                for (int j = 0; j < numResources; j++) {
                    if (need[i][j] > work[j]) {
                        canRun = 0;
                        break;
                    }
                }

                if (canRun) {
                    for (int j = 0; j < numResources; j++)
                        work[j] += allocation[i][j];
                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found)
            return 0; // unsafe
    }

    printf("\nSafe Sequence: ");
    for (int i = 0; i < numProcesses; i++)
        printf("P%d ", safeSeq[i]);
    printf("\n");
    return 1; // safe
}
