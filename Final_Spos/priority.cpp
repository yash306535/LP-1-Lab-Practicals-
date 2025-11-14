#include<iostream>
#include<limits.h>
#include<vector>
#include<iomanip>
using namespace std;

struct Process {
    int id, arrival, burst, priority;
    int completion, waiting, turnaround, response;
    bool done;
};

Process meh[30];

class Scheduler {
public:
    int n;

    void input() {
        cout << "Enter number of processes: ";
        cin >> n;
        for(int i=1; i<=n; i++) {
            meh[i].id = i;
            cout << "Enter arrival time of P" << i << ": ";
            cin >> meh[i].arrival;
            cout << "Enter burst time of P" << i << ": ";
            cin >> meh[i].burst;
            cout << "Enter priority of P" << i << ": ";
            cin >> meh[i].priority;
            meh[i].done = false;
            meh[i].response = -1;
        }

        cout << "\n  | Arrival | Burst | Priority\n";
        for(int i=1;i<=n;i++)
            cout << "P" << i << " | " << meh[i].arrival
                 << "       | " << meh[i].burst
                 << "     | " << meh[i].priority << "\n";
    }

    void schedule() {
        int time = 0, completed = 0;
        vector<int> seq;       // Process order
        vector<int> timeline;  // Time stamps

        while(completed < n) {
            int highest = INT_MAX, idx = -1;
            for(int i=1;i<=n;i++) {
                if(!meh[i].done && meh[i].arrival <= time && meh[i].priority < highest) {
                    highest = meh[i].priority;
                    idx = i;
                }
            }

            if(idx != -1) {
                if(meh[idx].response == -1)
                    meh[idx].response = time - meh[idx].arrival;

                seq.push_back(idx);
                timeline.push_back(time);

                time += meh[idx].burst;
                meh[idx].completion = time;
                meh[idx].turnaround = meh[idx].completion - meh[idx].arrival;
                meh[idx].waiting = meh[idx].turnaround - meh[idx].burst;
                meh[idx].done = true;
                completed++;
            } else {
                // CPU idle
                seq.push_back(0);
                timeline.push_back(time);
                time++;
            }
        }

        timeline.push_back(time);

        // Print Gantt Chart in desired format
        cout << "\nGantt Chart:\n";

        cout << "+";
        for(int x : seq)
            cout << "-----+";
        cout << "\n|";

        for(int x : seq) {
            if(x==0) cout << " IDLE|";
            else cout << " P" << x << " |";
        }
        cout << "\n+";
        for(int x : seq)
            cout << "-----+";
        cout << "\n";

        for(int t : timeline)
            cout << setw(5) << t;
        cout << "\n";
    }

    void displayMetrics() {
        double totalWT=0, totalTAT=0, totalCT=0;
        cout << "\n  | Completion | Waiting | Turnaround | Response\n";
        for(int i=1;i<=n;i++){
            totalWT += meh[i].waiting;
            totalTAT += meh[i].turnaround;
            totalCT += meh[i].completion;
            cout << "P" << i << " | " << setw(10) << meh[i].completion
                 << " | " << setw(7) << meh[i].waiting
                 << " | " << setw(10) << meh[i].turnaround
                 << " | " << setw(8) << meh[i].response << "\n";
        }

        cout << "\nAverage Completion Time: " << totalCT/n;
        cout << "\nAverage Waiting Time: " << totalWT/n;
        cout << "\nAverage Turnaround Time: " << totalTAT/n << "\n";
    }
};

int main() {
    Scheduler s;
    s.input();
    s.schedule();
    s.displayMetrics();
    return 0;
}
