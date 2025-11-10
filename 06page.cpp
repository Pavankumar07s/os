#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// ---------- FIFO ----------
void fifo(vector<int> pages, int framesCount) {
    vector<int> frames;
    int faults = 0, index = 0;

    cout << "\nFIFO Page Replacement:\n";
    for (int page : pages) {
        if (find(frames.begin(), frames.end(), page) == frames.end()) {
            if (frames.size() < framesCount)
                frames.push_back(page);
            else
            frames[index] = page;
            index = (index + 1) % framesCount;
            faults++;
        }

        cout << "Page " << page << " -> ";
        for (int f : frames) cout << f << " ";
        cout << "\n";
    }
    cout << "Total Page Faults: " << faults << "\n";
}

// ---------- LRU ----------
void lru(vector<int> pages, int framesCount) {
    vector<int> frames;
    int faults = 0;

    cout << "\nLRU Page Replacement:\n";
    for (int i = 0; i < pages.size(); i++) {
        int page = pages[i];
        auto it = find(frames.begin(), frames.end(), page);

        if (it == frames.end()) {
            if (frames.size() < framesCount)
                frames.push_back(page);
            else {
               int lruIndex = 0;
               int earliestUse = i; 
                // Loop through each frame to find which one was used longest ago
                for (int j = 0; j < frames.size(); j++) {
                    int lastUse = -1;
                    // Look backwards from the current page to find the last time this frame was used
                    for (int k = i - 1; k >= 0; k--) {
                        if (pages[k] == frames[j]) {
                            lastUse = k;
                            break;
                        }
                        
                    }
                    // If we found a page that was used even earlier, update our choice
                    if (lastUse < earliestUse) {
                        earliestUse = lastUse;
                        lruIndex = j;
                    }
                }
                frames[lruIndex] = page;
            }
            faults++;
        }

        cout << "Page " << page << " -> ";
        for (int f : frames) cout << f << " ";
        cout << "\n";
    }
    cout << "Total Page Faults: " << faults << "\n";
}

// ---------- OPTIMAL ----------
void optimal(vector<int> pages, int framesCount) {
    vector<int> frames;
    int faults = 0;

    cout << "\nOptimal Page Replacement:\n";
    for (int i = 0; i < pages.size(); i++) {
        int page = pages[i];
        auto it = find(frames.begin(), frames.end(), page);

        if (it == frames.end()) {
            if (frames.size() < framesCount)
                frames.push_back(page);
            else {
                int farthest = i, replaceIndex = 0;
                for (int j = 0; j < framesCount; j++) {
                    int nextUse = pages.size();
                    for (int k = i + 1; k < pages.size(); k++) {
                        if (frames[j] == pages[k]) {
                            nextUse = k;
                            break;
                        }
                    }
                    if (nextUse > farthest) {
                        farthest = nextUse;
                        replaceIndex = j;
                    }
                }
                frames[replaceIndex] = page;
            }
            faults++;
        }

        cout << "Page " << page << " -> ";
        for (int f : frames) cout << f << " ";
        cout << "\n";
    }
    cout << "Total Page Faults: " << faults << "\n";
}

// ---------- MAIN ----------
int main() {
    int n, framesCount, choice;
    cout << "Enter number of pages: ";
    cin >> n;

    vector<int> pages(n);
    cout << "Enter page reference string: ";
    for (int i = 0; i < n; i++) cin >> pages[i];

    cout << "Enter number of frames: ";
    cin >> framesCount;

    do {
        cout << "\nMENU:\n1. FIFO\n2. LRU\n3. Optimal\n4. Exit\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: fifo(pages, framesCount); break;
            case 2: lru(pages, framesCount); break;
            case 3: optimal(pages, framesCount); break;
            case 4: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 4);

    return 0;
}
