#include <iostream>
using namespace std;

int main() {
    int window, n;

    cout << "Enter number of pages in reference string: ";
    cin >> n;

    int refString[n];
    cout << "Enter the reference string (space separated): ";
    for (int i = 0; i < n; i++) {
        cin >> refString[i];
    }

    cout << "Enter window size: ";
    cin >> window;

    int currentPages[window], lastUsed[window];
    int hit = 0, miss = 0;

    // Initialize frames
    for (int i = 0; i < window; i++) {
        currentPages[i] = -1;
        lastUsed[i] = -1;
    }

    // Function to find least recently used index
    auto findLRU = [&](int window) 
    {
        int min_index = 0;
        for (int i = 1; i < window; i++) {
            if (lastUsed[i] < lastUsed[min_index]) {
                min_index = i;
            }
        }
        return min_index;
    };

    // LRU page replacement logic
    for (int i = 0; i < n; i++) 
    {
        bool hitFlag = false;

        // Check for page hit
        for (int j = 0; j < window; j++) 
        {
            if (currentPages[j] == refString[i])
            {
                hit++;
                hitFlag = true;
                lastUsed[j] = i; // Update last used position
                break;
            }
        }

        // If miss occurs
        if (!hitFlag) 
        {
            miss++;
            bool emptyFound = false;

            // If there is an empty frame
            for (int j = 0; j < window; j++) {
                if (currentPages[j] == -1) {
                    emptyFound = true;
                    currentPages[j] = refString[i];
                    lastUsed[j] = i;
                    break;
                }
            }

            // If no empty frame, replace least recently used page
            if (!emptyFound) {
                int lru_index = findLRU(window);
                currentPages[lru_index] = refString[i];
                lastUsed[lru_index] = i;
            }
        }
    }

    // Display result
    cout << "\n----- LRU ------";
    cout << "\nNumber of hits: " << hit;
    cout << "\nNumber of misses: " << miss;
    cout << "\nCurrent pages are:\t";
    for (int i = 0; i < window; i++) {
        cout << currentPages[i] << " ";
    }
    cout << endl;

    return 0;
}
