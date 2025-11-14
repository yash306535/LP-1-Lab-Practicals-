#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

struct Process {
    int id, arr, bur, orgBur;
    int comp, wait, turn;
};

Process meh[30];

class SJF {
public:
    int n;

    void getIn() {
        cout << "Enter number of processes: ";
        cin >> n;
        for(int i = 0; i < n; i++) {
            cout << "\nEnter arrival time for process " << i << ": ";
            cin >> meh[i].arr;
            cout << "Enter burst time for process " << i << ": ";
            cin >> meh[i].bur;
            meh[i].orgBur = meh[i].bur;
            meh[i].id = i;
        }
    }

    void process() {
        int k = 0; // current time
        int completed = 0;
        vector<int> seq;       // process execution order
        vector<int> timeline;  // timestamps

        while(completed < n) {
            int burst = 9999;
            int idd = -1;

            for(int i = 0; i < n; i++) {
                if(meh[i].arr <= k && meh[i].bur > 0) {
                    if(meh[i].bur < burst) {
                        burst = meh[i].bur;
                        idd = i;
                    }
                }
            }

            if(idd != -1) {
                seq.push_back(idd);
                timeline.push_back(k);

                // Execute for 1 unit
                k++;
                meh[idd].bur--;

                if(meh[idd].bur == 0) {
                    meh[idd].comp = k;
                    meh[idd].turn = meh[idd].comp - meh[idd].arr;
                    meh[idd].wait = meh[idd].turn - meh[idd].orgBur;
                    completed++;
                }
            } else {
                // CPU idle
                seq.push_back(-1);
                timeline.push_back(k);
                k++;
            }
        }

        timeline.push_back(k); // last timestamp

        // Print Gantt chart
        printGanttChart(seq, timeline);
    }

    void printGanttChart(vector<int>& seq, vector<int>& timeline) {
        int boxWidth = 5;

        cout << "\nGantt Chart:\n";
        cout << "+";
        for(int i=0;i<seq.size();i++)
            cout << string(boxWidth,'-') << "+";
        cout << "\n|";

        for(int x: seq) {
            string pid = (x==-1) ? "IDLE" : "P"+to_string(x);
            int padding = boxWidth - pid.size();
            int padLeft = padding/2;
            int padRight = padding - padLeft;
            cout << string(padLeft,' ') << pid << string(padRight,' ') << "|";
        }

        cout << "\n+";
        for(int i=0;i<seq.size();i++)
            cout << string(boxWidth,'-') << "+";
        cout << "\n";

        for(int i=0;i<timeline.size();i++) {
            if(i==0) cout << timeline[i];
            else cout << setw(boxWidth) << timeline[i];
        }
        cout << "\n";
    }

    void display() {
        double totalTurn = 0, totalWait = 0, totalComp = 0;
        cout << "\n  | Completion | Waiting | Turnaround\n";

        for(int i = 0; i < n; i++) {
            totalComp += meh[i].comp;
            totalTurn += meh[i].turn;
            totalWait += meh[i].wait;
            cout << "P" << i << " | " << setw(10) << meh[i].comp
                 << " | " << setw(7) << meh[i].wait
                 << " | " << setw(10) << meh[i].turn << "\n";
        }

        cout << "\nAverage Completion Time: " << totalComp/n;
        cout << "\nAverage Turnaround Time: " << totalTurn/n;
        cout << "\nAverage Waiting Time: " << totalWait/n << "\n";
    }
};

int main() {
    SJF ob;
    ob.getIn();
    ob.process();
    ob.display();
    return 0;
}
