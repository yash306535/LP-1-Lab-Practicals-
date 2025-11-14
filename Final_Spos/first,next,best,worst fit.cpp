 #include <iostream>
using namespace std;

int main() {
    int blkSize, prSize;

    cout << "Enter number of memory blocks: ";
    cin >> blkSize;

    int blocks[50]; // assume max 50 blocks
    cout << "Enter sizes of " << blkSize << " blocks:\n";
    for (int i = 0; i < blkSize; i++) {
        cin >> blocks[i];
    }

    cout << "\nEnter number of processes: ";
    cin >> prSize;

    int processes[50]; // assume max 50 processes
    cout << "Enter sizes of " << prSize << " processes:\n";
    for (int i = 0; i < prSize; i++) {
        cin >> processes[i];
    }

    int tempBlocks[50]; // to store original block sizes
    for (int i = 0; i < blkSize; i++) {
        tempBlocks[i] = blocks[i];
    }

    // ---------- FIRST FIT ----------
    cout << "\n----- FIRST FIT -----";
    for (int i = 0; i < blkSize; i++) blocks[i] = tempBlocks[i]; // reset
    for (int i = 0; i < prSize; i++) {
        bool allocated = false;
        for (int j = 0; j < blkSize; j++) {
            if (blocks[j] >= processes[i]) {
                cout << "\nProcess " << processes[i] << " allocated to Block " << j + 1;
                blocks[j] -= processes[i];
                allocated = true;
                break;
            }
        }
        if (!allocated) cout << "\nProcess " << processes[i] << " not allocated.";
    }

    // ---------- NEXT FIT ----------
    cout << "\n\n----- NEXT FIT -----";
    for (int i = 0; i < blkSize; i++) blocks[i] = tempBlocks[i]; // reset
    int j = 0;
    for (int i = 0; i < prSize; i++) {
        bool allocated = false;
        for (int k = 0; k < blkSize; k++) {
            if (blocks[j] >= processes[i]) {
                cout << "\nProcess " << processes[i] << " allocated to Block " << j + 1;
                blocks[j] -= processes[i];
                allocated = true;
                break;
            }
            j = (j + 1) % blkSize;
        }
        if (!allocated) cout << "\nProcess " << processes[i] << " not allocated.";
    }

    // ---------- BEST FIT ----------
    cout << "\n\n----- BEST FIT -----";
    for (int i = 0; i < blkSize; i++) blocks[i] = tempBlocks[i]; // reset
    for (int i = 0; i < prSize; i++) {
        int bestIdx = -1;
        for (int j = 0; j < blkSize; j++) {
            if (blocks[j] >= processes[i]) {
                if (bestIdx == -1 || blocks[j] < blocks[bestIdx])
                    bestIdx = j;
            }
        }
        if (bestIdx != -1) {
            cout << "\nProcess " << processes[i] << " allocated to Block " << bestIdx + 1;
            blocks[bestIdx] -= processes[i];
        } else {
            cout << "\nProcess " << processes[i] << " not allocated.";
        }
    }

    // ---------- WORST FIT ----------
    cout << "\n\n----- WORST FIT -----";
    for (int i = 0; i < blkSize; i++) blocks[i] = tempBlocks[i]; // reset
    for (int i = 0; i < prSize; i++) {
        int worstIdx = -1;
        for (int j = 0; j < blkSize; j++) {
            if (blocks[j] >= processes[i]) {
                if (worstIdx == -1 || blocks[j] > blocks[worstIdx])
                    worstIdx = j;
            }
        }
        if (worstIdx != -1) {
            cout << "\nProcess " << processes[i] << " allocated to Block " << worstIdx + 1;
            blocks[worstIdx] -= processes[i];
        } else {
            cout << "\nProcess " << processes[i] << " not allocated.";
        }
    }

    cout << "\n";
    return 0;
}
