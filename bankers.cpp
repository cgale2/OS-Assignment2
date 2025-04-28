// Charles Gale
// OS - Assignment 2
// Prompt: Implement the Banker’s algorithm to answer the following question： Is the system in a safe state? If Yes, then what is the safe sequence?

#include <iostream>
#include <vector>

using namespace std;

const int P = 5; // Number of processes
const int R = 3; // Number of resources

// Function to find if the system is in a safe state
bool isSafe(vector<int> &available, vector<vector<int>> &max, vector<vector<int>> &allocation, vector<vector<int>> &need) {
    vector<int> work = available;
    vector<bool> finish(P, false);
    vector<int> safeSequence(P);
    int count = 0;

    while (count < P) {
        bool found = false;
        for (int p = 0; p < P; p++) {
            if (!finish[p]) {
                bool canAllocate = true;
                for (int r = 0; r < R; r++) {
                    if (need[p][r] > work[r]) {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate) {
                    for (int r = 0; r < R; r++) {
                        work[r] += allocation[p][r];
                    }
                    safeSequence[count++] = p;
                    finish[p] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            cout << "System is not in a safe state." << endl;
            return false;
        }
    }

    cout << "System is in a safe state.\nSafe sequence is: ";
    for (int i = 0; i < P; i++) {
        cout << "P" << safeSequence[i];
        if (i != P - 1) cout << " -> ";
    }
    cout << endl;
    return true;
}

int main() {
    vector<int> available = {3, 3, 2}; // Available instances of resources A, B, C

    vector<vector<int>> max = {
        {7, 5, 3}, // Max demand of P0
        {3, 2, 2}, // Max demand of P1
        {9, 0, 2}, // Max demand of P2
        {2, 2, 2}, // Max demand of P3
        {4, 3, 3}  // Max demand of P4
    };

    vector<vector<int>> allocation = {
        {0, 1, 0}, // Current allocation for P0
        {2, 0, 0}, // Current allocation for P1
        {3, 0, 2}, // Current allocation for P2
        {2, 1, 1}, // Current allocation for P3
        {0, 0, 2}  // Current allocation for P4
    };

    vector<vector<int>> need(P, vector<int>(R));
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    isSafe(available, max, allocation, need);

    return 0;
}
