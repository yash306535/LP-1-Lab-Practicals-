#include<iostream>
#include<queue>
#include<iomanip>
#include<vector>
using namespace std;

struct Process{
    int id, burst, arrival, remaining, completion, waiting, turnaround, response;
};

Process processes[30];

class RoundRobin{
public:
    int n, timeQuantum;

    void input(){
        cout << "\nEnter number of processes: ";
        cin >> n;
        for(int i = 0; i < n; i++){
            cout << "\nEnter arrival time of P" << i << ": ";
            cin >> processes[i].arrival;
            cout << "Enter burst time of P" << i << ": ";
            cin >> processes[i].burst;
            processes[i].id = i;
            processes[i].remaining = processes[i].burst;
            processes[i].response = -1;
        }
        cout << "\nEnter time quantum: ";
        cin >> timeQuantum;
    }

    void schedule(){
        int currentTime = 0;
        queue<int> q;
        bool inQueue[30] = {false};
        int completedProcesses = 0;

        vector<int> seq;       // process execution order for Gantt chart
        vector<int> timeline;  // time stamps for Gantt chart

        while(completedProcesses < n){
            // Add arriving processes to queue
            for(int i=0;i<n;i++){
                if(!inQueue[i] && processes[i].arrival <= currentTime && processes[i].remaining > 0){
                    q.push(i);
                    inQueue[i] = true;
                }
            }

            if(q.empty()){
                // CPU Idle
                seq.push_back(-1);
                timeline.push_back(currentTime);
                currentTime++;
                continue;
            }

            int idx = q.front();
            q.pop();

            // Record response time
            if(processes[idx].response == -1){
                processes[idx].response = currentTime - processes[idx].arrival;
            }

            // Record Gantt chart start time
            seq.push_back(idx);
            timeline.push_back(currentTime);

            // Execute process
            if(processes[idx].remaining <= timeQuantum){
                currentTime += processes[idx].remaining;
                processes[idx].remaining = 0;
                processes[idx].completion = currentTime;
                processes[idx].turnaround = processes[idx].completion - processes[idx].arrival;
                processes[idx].waiting = processes[idx].turnaround - processes[idx].burst;
                completedProcesses++;
            } else {
                currentTime += timeQuantum;
                processes[idx].remaining -= timeQuantum;
            }

            // Add newly arrived processes to queue
            for(int i=0;i<n;i++){
                if(!inQueue[i] && processes[i].arrival <= currentTime && processes[i].remaining > 0){
                    q.push(i);
                    inQueue[i] = true;
                }
            }

            // If process not finished, push back to queue
            if(processes[idx].remaining > 0)
                q.push(idx);
        }

        // Final timeline for last process
        timeline.push_back(currentTime);

        // Print Gantt Chart in box format
        cout << "\nGantt Chart:\n";
        cout << "+";
        for(int x: seq)
            cout << "-----+";
        cout << "\n|";
        for(int x: seq){
            if(x == -1) cout << " IDLE|";
            else cout << " P" << x << " |";
        }
        cout << "\n+";
        for(int x: seq)
            cout << "-----+";
        cout << "\n";
        for(int t: timeline)
            cout << setw(5) << t;
        cout << "\n";
    }

    void displayMetrics(){
        double totalWaiting = 0, totalTurnaround = 0, totalCompletion = 0;

        cout << "\n  | Completion | Waiting | Turnaround | Response\n";
        for(int i=0;i<n;i++){
            totalWaiting += processes[i].waiting;
            totalTurnaround += processes[i].turnaround;
            totalCompletion += processes[i].completion;

            cout << "P" << i << " | " << setw(10) << processes[i].completion
                 << " | " << setw(7) << processes[i].waiting
                 << " | " << setw(10) << processes[i].turnaround
                 << " | " << setw(8) << processes[i].response << "\n";
        }

        cout << "\nAverage Completion Time: " << totalCompletion/n;
        cout << "\nAverage Waiting Time: " << totalWaiting/n;
        cout << "\nAverage Turnaround Time: " << totalTurnaround/n << "\n";
    }
};

int main(){
    RoundRobin rr;
    rr.input();
    rr.schedule();
    rr.displayMetrics();
    return 0;
}
