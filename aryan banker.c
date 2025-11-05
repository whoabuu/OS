#include <iostream>
using namespace std;

int main() {
    int max[5][3] = { {7,5,3}, {3,2,2}, {9,0,2}, {2,2,2}, {4,3,3} };
    int alloc[5][3] = { {0,1,0}, {2,0,0}, {3,0,2}, {2,1,1}, {0,0,2} };
    int total[3] = {10,5,7};

    int need[5][3], avail[3], sumAlloc[3]={0,0,0};
    bool finish[5]={false};
    int safeSeq[5], count=0;

    // Step 1: Calculate Need Matrix
    cout << "Need Matrix:\n";
    for(int i=0;i<5;i++){
        for(int j=0;j<3;j++){
            need[i][j] = max[i][j] - alloc[i][j];
            cout << need[i][j] << "\t";
        }
        cout << endl;
    }

    // Step 2: Calculate Available Resources
    for(int j=0;j<3;j++)
        for(int i=0;i<5;i++)
            sumAlloc[j] += alloc[i][j];

    for(int j=0;j<3;j++)
        avail[j] = total[j] - sumAlloc[j];

    cout << "\nAvailable Resources: ";
    for(int j=0;j<3;j++)
        cout << avail[j] << " ";
    cout << endl;

    // Step 3: Safety Algorithm
    while(count < 5){
        bool found = false;

        for(int i=0;i<5;i++){
            if(!finish[i]){
                int j;
                for(j=0;j<3;j++)
                    if(need[i][j] > avail[j])
                        break;

                if(j == 3){ // means process can execute
                    for(int k=0;k<3;k++)
                        avail[k] += alloc[i][k];

                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }

        if(!found){
            cout << "\nSystem is NOT in a safe state!" << endl;
            return 0;
        }
    }

    // Step 4: Print Safe Sequence
    cout << "\nSystem is SAFE.\nSafe Sequence: ";
    for(int i=0;i<5;i++)
        cout << "P" << safeSeq[i] << " ";
    cout << endl;

    return 0;
}
