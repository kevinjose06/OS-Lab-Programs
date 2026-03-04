/*Input a list of processes, their CPU burst times (integral values), arrival times, and
priorities. Then simulate FCFS, SRTF, non-preemptive priority (a larger priority number
implies a higher priority), and RR (quantum = 3 units) scheduling algorithms on the
process mix, determining which algorithm results in the minimum average waiting time
(over all processes).
*/

#include <stdio.h>

float fcfs(int n, int at[], int bt[], int pid[])
{
    int ct[50], wt[50], tat[50], rt[50];
    int time = 0;
    int i;
    float avg = 0;

    for (i = 0; i < n; i++)
    {
        if (time < at[i])
        {
            time = at[i];
        }

        rt[i] = time - at[i];
        time = time + bt[i];

        ct[i] = time;
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        avg = avg + wt[i];
    }

    printf("\nFCFS\n");
    printf("PID AT BT CT TAT WT RT\n");

    for (i = 0; i < n; i++)
    {
        printf("%d %d %d %d %d %d %d\n",
               pid[i], at[i], bt[i],
               ct[i], tat[i], wt[i], rt[i]);
    }

    avg = avg / n;
    printf("Average Waiting Time = %.2f\n", avg);

    return avg;
}

float priority_np(int n, int at[], int bt[], int pr[], int pid[])
{
    int ct[50], wt[50], tat[50], rt[50];
    int done[50];
    int time = 0;
    int completed = 0;
    int i;
    float avg = 0;

    for (i = 0; i < n; i++)
    {
        done[i] = 0;
    }

    while (completed < n)
    {
        int max = -1;
        int p = -1;

        for (i = 0; i < n; i++)
        {
            if (done[i] == 0 && at[i] <= time)
            {
                if (pr[i] > max)
                {
                    max = pr[i];
                    p = i;
                }
            }
        }

        if (p == -1)
        {
            time++;
        }
        else
        {
            rt[p] = time - at[p];
            time = time + bt[p];

            ct[p] = time;
            tat[p] = ct[p] - at[p];
            wt[p] = tat[p] - bt[p];

            avg = avg + wt[p];

            done[p] = 1;
            completed++;
        }
    }

    printf("\nPriority Non Preemptive\n");
    printf("PID AT BT CT TAT WT RT\n");

    for (i = 0; i < n; i++)
    {
        printf("%d %d %d %d %d %d %d\n",
               pid[i], at[i], bt[i],
               ct[i], tat[i], wt[i], rt[i]);
    }

    avg = avg / n;
    printf("Average Waiting Time = %.2f\n", avg);

    return avg;
}

float srtf(int n, int at[], int bt[], int pid[])
{
    int rem_bt[50], ct[50], wt[50], tat[50], rt[50];
    int i;
    int time = 0;
    int completed = 0;
    float avg = 0;

    for (i = 0; i < n; i++)
    {
        rem_bt[i] = bt[i];
        rt[i] = -1;
    }

    while (completed < n)
    {
        int min = 9999;
        int p = -1;

        for (i = 0; i < n; i++)
        {
            if (at[i] <= time && rem_bt[i] > 0)
            {
                if (rem_bt[i] < min)
                {
                    min = rem_bt[i];
                    p = i;
                }
            }
        }

        if (p == -1)
        {
            time++;
        }
        else
        {
            if (rt[p] == -1)
            {
                rt[p] = time - at[p];
            }

            rem_bt[p]--;
            time++;

            if (rem_bt[p] == 0)
            {
                ct[p] = time;
                tat[p] = ct[p] - at[p];
                wt[p] = tat[p] - bt[p];

                avg = avg + wt[p];
                completed++;
            }
        }
    }

    printf("\nSRTF\n");
    printf("PID AT BT CT TAT WT RT\n");

    for (i = 0; i < n; i++)
    {
        printf("%d %d %d %d %d %d %d\n",
               pid[i], at[i], bt[i],
               ct[i], tat[i], wt[i], rt[i]);
    }

    avg = avg / n;
    printf("Average Waiting Time = %.2f\n", avg);

    return avg;
}

float rr(int n, int at[], int bt[], int pid[])
{
    int rem_bt[50], ct[50], wt[50], tat[50], rt[50];
    int queue[100];
    int visited[50];

    int front = 0;
    int rear = 0;
    int time = 0;
    int completed = 0;
    int i;
    int q = 3;
    float avg = 0;

    for (i = 0; i < n; i++)
    {
        rem_bt[i] = bt[i];
        visited[i] = 0;
        rt[i] = -1;
    }

    while (completed < n)
    {
        for (i = 0; i < n; i++)
        {
            if (at[i] <= time && visited[i] == 0)
            {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }

        if (front == rear)
        {
            time++;
            continue;
        }

        int p = queue[front++];

        if (rt[p] == -1)
        {
            rt[p] = time - at[p];
        }

        int run;

        if (rem_bt[p] > q)
        {
            run = q;
        }
        else
        {
            run = rem_bt[p];
        }

        rem_bt[p] -= run;
        time += run;

        for (i = 0; i < n; i++)
        {
            if (at[i] <= time && visited[i] == 0)
            {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }

        if (rem_bt[p] > 0)
        {
            queue[rear++] = p;
        }
        else
        {
            ct[p] = time;
            tat[p] = ct[p] - at[p];
            wt[p] = tat[p] - bt[p];
            avg += wt[p];
            completed++;
        }
    }

    printf("\nRound Robin (q = 3)\n");
    printf("PID AT BT CT TAT WT RT\n");

    for (i = 0; i < n; i++)
    {
        printf("%d %d %d %d %d %d %d\n",
               pid[i], at[i], bt[i],
               ct[i], tat[i], wt[i], rt[i]);
    }

    avg = avg / n;
    printf("Average Waiting Time = %.2f\n", avg);

    return avg;
}

int main()
{
    int n;
    int i;

    int pid[50];
    int at[50];
    int bt[50];
    int pr[50];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++)
    {
        pid[i] = i + 1;

        printf("\nProcess %d\n", i + 1);

        printf("Arrival Time: ");
        scanf("%d", &at[i]);

        printf("Burst Time: ");
        scanf("%d", &bt[i]);

        printf("Priority: ");
        scanf("%d", &pr[i]);
    }

    float a1 = fcfs(n, at, bt, pid);
    float a2 = srtf(n, at, bt, pid);
    float a3 = priority_np(n, at, bt, pr, pid);
    float a4 = rr(n, at, bt, pid);

    float min = a1;
    char best[30] = "FCFS";

    if (a2 < min)
    {
        min = a2;
        sprintf(best, "SRTF");
    }

    if (a3 < min)
    {
        min = a3;
        sprintf(best, "Priority Non Preemptive");
    }

    if (a4 < min)
    {
        min = a4;
        sprintf(best, "Round Robin");
    }

    printf("\nBest Scheduling Algorithm : %s\n", best);

    return 0;
}