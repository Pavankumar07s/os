
#include <iostream> 


using namespace std; 


int main()
{

    int Max[10][10], need[10][10], alloc[10][10], avail[10], completed[10], safeSequence[10];
    int p, r, i, j, process, count;
    count = 0;


    cout << "Enter the no of processes : ";
    cin >> p;

    for(i = 0; i < p; i++)
        completed[i] = 0;

    cout << "\n\nEnter the no of resources : ";
    cin >> r;

    cout << "\n\nEnter the Max Matrix for each process : ";
    for(i = 0; i < p; i++)
    {
        cout << "\nFor process " << (i + 1) << " : ";
        for(j = 0; j < r; j++)
            cin >> Max[i][j];
    }

    cout << "\n\nEnter the allocation for each process : ";
    for(i = 0; i < p; i++)
    {
        cout << "\nFor process " << (i + 1) << " : ";
        for(j = 0; j < r; j++)
            cin >> alloc[i][j];
    }

    cout << "\n\nEnter the Available Resources : ";
    for(i = 0; i < r; i++)
        cin >> avail[i];

    // --- Need Matrix Calculation (identical) ---
    for(i = 0; i < p; i++)
        for(j = 0; j < r; j++)
            need[i][j] = Max[i][j] - alloc[i][j];

    // --- Safety Algorithm (logic is identical) ---
    do
    {
        // Print current state (using cout)
        cout << "\n Max matrix:\tAllocation matrix:\n";
        for(i = 0; i < p; i++)
        {
            for(j = 0; j < r; j++)
                cout << Max[i][j] << " ";
            
            cout << "\t\t";
            
            for(j = 0; j < r; j++)
                cout << alloc[i][j] << " ";
            
            cout << "\n";
        }

        process = -1; // Reset process flag

        // Find a safe process to run
        for(i = 0; i < p; i++)
        {
            if(completed[i] == 0) // if not completed
            {
                process = i;
                for(j = 0; j < r; j++)
                {
                    if(avail[j] < need[i][j])
                    {
                        process = -1; // Cannot run this process
                        break;
                    }
                }
            }
            if(process != -1) // Found a process
                break;
        }

        // If a safe process was found
        if(process != -1)
        {
            cout << "\nProcess " << (process + 1) << " runs to completion!";
            safeSequence[count] = process + 1;
            count++;

            // Release its resources
            for(j = 0; j < r; j++)
            {
                avail[j] += alloc[process][j];
                alloc[process][j] = 0;
                Max[process][j] = 0;
                completed[process] = 1;
            }
        }
    } while(count != p && process != -1); // Continue if not all done and not deadlocked

   
    if(count == p)
    {
        cout << "\nThe system is in a safe state!!\n";
        cout << "Safe Sequence : < ";
        for(i = 0; i < p; i++)
            cout << safeSequence[i] << " ";
        cout << ">\n";
    }
    else
    {
        cout << "\nThe system is in an unsafe state!!";
    }

    return 0; 
}