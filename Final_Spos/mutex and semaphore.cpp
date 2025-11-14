#include <iostream>
using namespace std;

class syn {
    int a[10];      // buffer
    int mutex;      // for critical section
    int empty;      // number of empty slots
    int full;       // number of filled slots
    int in;         // producer index
    int out;        // consumer index
    int data;       // input data

    void wait(int &x) {
        if (x > 0) x--;
    }

    void signal1(int &x) {
        x++;
    }

public:
    syn() : mutex(1), full(0), empty(10), in(0), out(0) {}

    void producer() {
        if (empty > 0 && mutex == 1) {
            wait(empty);
            wait(mutex);

            cout << "\nEnter data to be produced: ";
            cin >> data;
            a[in] = data;
            cout << "Produced: " << data << " at position " << in << endl;
            in = (in + 1) % 10;

            signal1(mutex);
            signal1(full);
        } else {
            cout << "\nBuffer is full. Cannot produce!\n";
        }
    }

    void consumer() {
        if (full > 0 && mutex == 1) {
            wait(full);
            wait(mutex);

            cout << "\nData consumed: " << a[out] << endl;
            out = (out + 1) % 10;

            signal1(mutex);
            signal1(empty);
        } else {
            cout << "\nBuffer is empty. Cannot consume!\n";
        }
    }

    void display() {
        cout << "\n----- BUFFER STATUS -----\n";
        if (full == 0) {
            cout << "Buffer is empty.\n";
            return;
        }

        cout << "Current buffer contents:\n";
        int index=out;
        for(int i=0;i<full;i++)
        {
            cout<<a[index]<<"  "<<endl;
            index=(index+1)%10;
        }
        cout<<endl;
    }
};

int main() {
    int choice;
    syn s;

    do {
        cout << "\n1. Producer";
        cout << "\n2. Consumer";
        cout << "\n3. Display Buffer";
        cout << "\n4. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: s.producer(); break;
            case 2: s.consumer(); break;
            case 3: s.display(); break;
            case 4: cout << "\nExiting...\n"; break;
            default: cout << "\nPlease enter a valid choice.\n";
        }
    } while (choice != 4);

    return 0;
}
