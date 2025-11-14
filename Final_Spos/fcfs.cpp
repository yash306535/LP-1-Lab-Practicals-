#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;

struct Process {
    int pid, arrival, burst, completion, waiting, turn, response, start;
};

bool cmp(Process a, Process b) {
    return a.arrival < b.arrival;
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    Process p[n];

    for(int i = 0; i < n; i++) {
        p[i].pid = i;
        cout << "Enter arrival time of P" << i << ": ";
        cin >> p[i].arrival;
        cout << "Enter burst time of P" << i << ": ";
        cin >> p[i].burst;
    }

    sort(p, p+n, cmp);
    int time = 0;

    // Calculate scheduling values
    for(int i = 0; i < n; i++) {
        if(time < p[i].arrival) time = p[i].arrival; // idle case
        p[i].start = time;
        time += p[i].burst;
        p[i].completion = time;
        p[i].turn = p[i].completion - p[i].arrival;
        p[i].waiting = p[i].turn - p[i].burst;
        p[i].response = p[i].start - p[i].arrival;
    }

    // Print GANTT CHART
    cout << "\nGantt Chart:\n";

    cout << "+";
    for(int i=0;i<n;i++)
        cout << "-----+";
    cout << "\n|";

    for(int i=0;i<n;i++)
        cout << " P" << p[i].pid << "  |";
    cout << "\n+";

    for(int i=0;i<n;i++)
        cout << "-----+";
    cout << "\n";

    // Print timeline
    int t = 0;
    cout << p[0].start;
    for(int i=0;i<n;i++){
        if(p[i].start > t) t = p[i].start;
        t += p[i].burst;
        cout << setw(6) << t;
    }
    cout << "\n";

    // Display table
    cout << "\nP\tAT\tBT\tCT\tWT\tTAT\tRT\n";
    float avgWT=0, avgTAT=0, avgCT=0;

    for(int i = 0; i < n; i++) {
        avgWT += p[i].waiting;
        avgTAT += p[i].turn;
        avgCT += p[i].completion;

        cout << "P" << p[i].pid << "\t"
             << p[i].arrival << "\t"
             << p[i].burst << "\t"
             << p[i].completion << "\t"
             << p[i].waiting << "\t"
             << p[i].turn << "\t"
             << p[i].response << "\n";
    }

    cout << "\nAverage Waiting Time: " << avgWT / n;
    cout << "\nAverage Turnaround Time: " << avgTAT / n;
    cout << "\nAverage Completion Time: " << avgCT / n << endl;

    return 0;
}
