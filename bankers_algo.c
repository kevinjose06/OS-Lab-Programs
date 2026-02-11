#include <stdio.h>
#include <stdbool.h>

void inputAvailable(int m, int Available[]) 
{
    printf("\nEnter Available resources:\n");
    for (int j = 0; j < m; j++) 
    {
        scanf("%d", &Available[j]);
    }
}

void inputMatrix(int n, int m, int matrix[n][m], char name[]) 
{
    printf("\nEnter %s matrix:\n", name);
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < m; j++) 
        {
            scanf("%d", &matrix[i][j]);
        }
    }
}

void calculateNeed(int n, int m,
                   int Max[n][m],
                   int Allocation[n][m],
                   int Need[n][m]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            Need[i][j] = Max[i][j] - Allocation[i][j];
        }
    }
}

bool isSafeState(int n, int m,
                 int Available[],
                 int Allocation[n][m],
                 int Need[n][m],
                 int SafeSeq[]) {

    int Work[m];
    bool Finish[n];
    int count = 0;

    for (int j = 0; j < m; j++)
        Work[j] = Available[j];

    for (int i = 0; i < n; i++)
        Finish[i] = false;

    while (count < n) {
        bool found = false;

        for (int i = 0; i < n; i++) {
            if (!Finish[i]) {
                bool possible = true;

                for (int j = 0; j < m; j++) {
                    if (Need[i][j] > Work[j]) {
                        possible = false;
                        break;
                    }
                }

                if (possible) {
                    for (int k = 0; k < m; k++) {
                        Work[k] += Allocation[i][k];
                    }
                    SafeSeq[count++] = i;
                    Finish[i] = true;
                    found = true;
                }
            }
        }

        if (!found)
            return false;
    }

    return true;
}

void printSafeSequence(int n, int SafeSeq[]) {
    printf("\nSystem is in a SAFE state.\nSafe sequence: ");
    for (int i = 0; i < n; i++) {
        printf("P%d ", SafeSeq[i]);
    }
    printf("\n");
}

int main() {
    int n, m;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    int Available[m];
    int Max[n][m];
    int Allocation[n][m];
    int Need[n][m];
    int SafeSeq[n];

    inputAvailable(m, Available);
    inputMatrix(n, m, Max, "Max");
    inputMatrix(n, m, Allocation, "Allocation");

    calculateNeed(n, m, Max, Allocation, Need);

    if (isSafeState(n, m, Available, Allocation, Need, SafeSeq)) {
        printSafeSequence(n, SafeSeq);
    } else {
        printf("\nSystem is NOT in a safe state.\n");
    }

    return 0;
}
