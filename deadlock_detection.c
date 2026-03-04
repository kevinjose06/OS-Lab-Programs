/*Obtain a process mix and determine if the system is deadlocked. */

#include <stdio.h>
#include <stdbool.h>

void inputAvailable(int m, int Available[]) {
    printf("\nEnter Available resources:\n");
    for (int j = 0; j < m; j++)
        scanf("%d", &Available[j]);
}

void inputMatrix(int n, int m, int matrix[n][m], char name[]) {
    printf("\nEnter %s matrix:\n", name);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &matrix[i][j]);
}

bool detectDeadlock(int n, int m,
                    int Available[],
                    int Allocation[n][m],
                    int Request[n][m]) {

    int Work[m];
    bool Finish[n];
    int count = 0;

    for (int j = 0; j < m; j++)
        Work[j] = Available[j];

    for (int i = 0; i < n; i++) {
        bool hasAllocation = false;

        for (int j = 0; j < m; j++) {
            if (Allocation[i][j] != 0) {
                hasAllocation = true;
                break;
            }
        }

        Finish[i] = !hasAllocation;
        if (Finish[i])
            count++;
    }

    while (count < n) {
        bool found = false;

        for (int i = 0; i < n; i++) {
            if (!Finish[i]) {
                bool possible = true;

                for (int j = 0; j < m; j++) {
                    if (Request[i][j] > Work[j]) {
                        possible = false;
                        break;
                    }
                }

                if (possible) {
                    for (int j = 0; j < m; j++)
                        Work[j] += Allocation[i][j];

                    Finish[i] = true;
                    count++;
                    found = true;
                }
            }
        }

        if (!found) {
            printf("\nSystem IS deadlocked.\n");
            printf("Deadlocked processes:\n");
            for (int i = 0; i < n; i++) {
                if (!Finish[i])
                    printf("T%d ", i);
            }
            printf("\n");
            return false;
        }
    }

    printf("\nSystem is NOT deadlocked.\n");
    return true;
}

int main() {
    int n, m;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    int Available[m];
    int Allocation[n][m];
    int Request[n][m];

    inputAvailable(m, Available);
    inputMatrix(n, m, Allocation, "Allocation");
    inputMatrix(n, m, Request, "Request");

    detectDeadlock(n, m, Available, Allocation, Request);

    return 0;
}
