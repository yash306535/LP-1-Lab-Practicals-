#include <iostream>
using namespace std;

int findOptimal(int current_index, int refString[], int currentPages[], int window, int len) {
    int max_index = -1, farthest = current_index;

    for (int i = 0; i < window; i++) {
        int j;
        for (j = current_index + 1; j < len; j++) {
            if (currentPages[i] == refString[j]) {
                if (j > farthest) {
                    farthest = j;
                    max_index = i;
                }
                break;
            }
        }
        if (j == len) { 
            return i;  // Page not used again
        }
    }
    return (max_index == -1) ? 0 : max_index;
}

void Optimal(int refString[], int len, int window) {
    int hit = 0, miss = 0;
    int currentPages[20];

    // Initialize frames to -1 (empty)
    for (int i = 0; i < window; i++) {
        currentPages[i] = -1;
    }

    for (int i = 0; i < len; i++) {
        bool hitFlag = false;

        // Check for hit
        for (int j = 0; j < window; j++) {
            if (currentPages[j] == refString[i]) {
                hit++;
                hitFlag = true;
                break;
            }
        }

        // If miss
        if (!hitFlag) {
            miss++;
            bool emptyFound = false;

            // Place in empty frame if available
            for (int j = 0; j < window; j++) {
                if (currentPages[j] == -1) {
                    currentPages[j] = refString[i];
                    emptyFound = true;
                    break;
                }
            }

            // Replace using Optimal if no empty frame
            if (!emptyFound) {
                int optimal_index = findOptimal(i, refString, currentPages, window, len);
                currentPages[optimal_index] = refString[i];
            }
        }
    }

    cout << "\n----- OPTIMAL PAGE REPLACEMENT -----";
    cout << "\nNumber of hits: " << hit;
    cout << "\nNumber of misses: " << miss;
    cout << "\nCurrent pages are:\t";
    for (int i = 0; i < window; i++) {
        cout << currentPages[i] << " ";
    }
    cout << endl;
}

int main() {
    int len, window;
    cout << "Enter number of pages in reference string: ";
    cin >> len;

    int refString[50];
    cout << "Enter reference string: ";
    for (int i = 0; i < len; i++) {
        cin >> refString[i];
    }

    cout << "Enter window size: ";
    cin >> window;

    Optimal(refString, len, window);

    return 0;
}
