/*Input a list of processes, their CPU burst times (integral values), arrival times, and
priorities. Then simulate FCFS, SRTF, non-preemptive priority (a larger priority number
implies a higher priority), and RR (quantum = 3 units) scheduling algorithms on the
process mix, determining which algorithm results in the minimum average waiting time
(over all processes).
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct process
{
	int pid,at,bt,pr,rt,ct,tt,wt,remt,flag;
};

struct stat
{
	float art,act,att,awt;
};

void print(struct process *p,struct stat res,int n)
{
	int i;

	printf("---------------------------------------------------------------------------------------\n");
	printf("| %-5s | %-5s | %-5s | %-5s | %-5s | %-5s | %-5s |\n","PID","AT","BT","RT","CT","TT","WT");
	printf("---------------------------------------------------------------------------------------\n");

	for(i = 0;i < n;i++)
	{
		printf("| %-5d | %-5d | %-5d | %-5d | %-5d | %-5d | %-5d |\n",p[i].pid,p[i].at,p[i].bt,p[i].rt,p[i].ct,p[i].tt,p[i].wt);
	}

	printf("Average Response Time   : %.2f\n",res.art);
	printf("Average Completion Time : %.2f\n",res.act);
	printf("Average Turnaround Time : %.2f\n",res.att);
	printf("Average Waiting Time    : %.2f\n",res.awt);
}

void reset(struct process *p, int n)
{
    for (int i = 0; i < n; i++)
    {
        p[i].rt = 0;
        p[i].ct = 0;
        p[i].tt = 0;
        p[i].wt = 0;
        p[i].remt = p[i].bt;
        p[i].flag = 0;
    }
}

struct stat fcfs(struct process *p,int n)
{
	int t = 0,i;
	struct stat res = {0};

	for(i = 0;i < n;i++)
	{
		int st = (t > p[i].at) ? t : p[i].at;

		p[i].rt = (st - p[i].at);
		p[i].ct = (st + p[i].bt);
		p[i].tt = (p[i].ct - p[i].at);
		p[i].wt = (p[i].tt - p[i].bt);
		t = p[i].ct;

		res.art += p[i].rt;
		res.act += p[i].ct;
		res.att += p[i].tt;
		res.awt += p[i].wt;
	}
	res.art /= n;
	res.act /= n;
	res.att /= n;
	res.awt /= n;

	printf("\n\t-------------------------------------------FISRT COME FIRST SERVE------------------------------------------\n\n");
	print(p,res,n);

	return res;

}

struct stat srtf(struct process *p,int n)
{
	int i,j,t = 0,c = 0,sel,next,et;
	struct stat res = {0};
	struct process temp;

	for(i = 0;i < n;i++)
	{
		for(j = (i + 1);j < n;j++)
		{
			if(p[i].at > p[j].at)
			{
				temp = p[i];
				p[i] = p[j];
				p[j] = temp;
			}
		}
	}

	while(c != n)
	{
		sel = -1;
		next = -1;

		for(i = 0;i < n;i++)
		{
			if((p[i].at <= t) && p[i].remt > 0)
			{
				if((sel == -1) || (p[i].remt < p[sel].remt))
				{
					sel = i;
				}
			}
			if(p[i].at > t)
			{
				if((next == -1) || (p[i].at < p[next].at))
				{
					next = i;
				}
			}
		}

		if (sel == -1)
		{
			t = p[next].at;
			continue;
		}

		if (!p[sel].flag)
		{
        	{
            		p[sel].rt = t - p[sel].at;
            		p[sel].flag = 1;
       	 	}
		}

		if(next == -1)
		{
			et = p[sel].remt;
		}
		else
		{
			et = (p[sel].remt < (p[next].at - t)) ? p[sel].remt : (p[next].at - t);
		}

		p[sel].remt -= et;
		t += et;


		if (p[sel].remt == 0)
		{
				p[sel].ct = t;
				c++;
		}
	}

	for (i = 0; i < n; i++)
	{
		p[i].tt = p[i].ct - p[i].at;
		p[i].wt  = p[i].tt - p[i].bt;

		res.att += p[i].tt;
		res.awt += p[i].wt;
		res.art += p[i].rt;
		res.act += p[i].ct;
	}

	res.att /= n;
	res.awt /= n;
	res.art /= n;
	res.act /= n;

	printf("\n\t-------------------------------------------SHORTEST REMAINING TIME FIRST------------------------------------------\n\n");
	print(p,res,n);

	return res;

}

struct stat priority(struct process *p, int n)
{
    int i, j, t = 0, c = 0, sel;
    struct stat res = {0};
    struct process temp;

    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (p[i].at > p[j].at)
            {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    while (c < n)
    {
        sel = -1;

        for (i = 0; i < n; i++)
        {
            if (p[i].at <= t && p[i].flag == 0)
            {
                if (sel == -1 || p[i].pr > p[sel].pr)
                {
                    sel = i;
                }
            }
        }

        if (sel == -1)
        {
            t++;
            continue;
        }

        p[sel].rt = t - p[sel].at;

        t += p[sel].bt;
        p[sel].ct = t;
        p[sel].flag = 1;
        c++;
    }

    for (i = 0; i < n; i++)
    {
        p[i].tt = p[i].ct - p[i].at;
        p[i].wt = p[i].tt - p[i].bt;

        res.art += p[i].rt;
        res.act += p[i].ct;
        res.att += p[i].tt;
        res.awt += p[i].wt;
    }

    res.art /= n;
    res.act /= n;
    res.att /= n;
    res.awt /= n;

    printf("\n\t-------------------------------------------NON-PREEMPTIVE PRIORITY------------------------------------------\n\n");
    print(p,res,n);

    return res;
}

struct stat rr(struct process *p, int n)
{
    int i, t = 0, c = 0;
    int q = 3;               
    struct stat res = {0};
    struct process temp;

    for (i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (p[i].at > p[j].at)
            {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    while (c < n)
    {
        int executed = 0;

        for (i = 0; i < n; i++)
        {
            if (p[i].at <= t && p[i].remt > 0)
            {
                if (!p[i].flag)
                {
                    p[i].rt = t - p[i].at;
                    p[i].flag = 1;
                }

                int et = (p[i].remt < q) ? p[i].remt : q;

                p[i].remt -= et;
                t += et;
                executed = 1;

                if (p[i].remt == 0)
                {
                    p[i].ct = t;
                    c++;
                }
            }
        }

        if (!executed)
            t++;
    }

    for (i = 0; i < n; i++)
    {
        p[i].tt = p[i].ct - p[i].at;
        p[i].wt = p[i].tt - p[i].bt;

        res.art += p[i].rt;
        res.act += p[i].ct;
        res.att += p[i].tt;
        res.awt += p[i].wt;
    }

    res.art /= n;
    res.act /= n;
    res.att /= n;
    res.awt /= n;

    printf("\n\t-------------------------------------------ROUND ROBIN------------------------------------------\n\n");
    print(p,res,n);

    return res;
}

int main()
{
	int n,i;
	float wait;
	struct stat fcfs_avg,srtf_avg,priority_avg,rr_avg;

	printf("Enter the number of proceses : ");
	scanf("%d",&n);

	struct process *p = malloc(n * sizeof(struct process));

	for(i = 0;i < n;i++)
	{
		printf("Enter process ID of process %d : ",(i + 1));
		scanf("%d",&p[i].pid);
		printf("Enter the process arrival time : ");
		scanf("%d",&p[i].at);
		printf("Enter burst time of the process : ");
		scanf("%d",&p[i].bt);
		p[i].remt = p[i].bt;
		printf("Enter priority of the process : ");
		scanf("%d",&p[i].pr);
		p[i].flag = 0;
	}

	fcfs_avg = fcfs(p,n);

	reset(p,n);
	srtf_avg = srtf(p,n);

	reset(p,n);
	priority_avg = priority(p,n);

	reset(p,n);
	rr_avg = rr(p,n);

	wait = fcfs_avg.awt;
	
	char best[] = "FCFS is the best option\n";

	if(srtf_avg.awt < wait)
	{
		wait = srtf_avg.awt;
		strcpy(best,"SRTF is the best option");
	}
	if(priority_avg.awt < wait)
	{
		wait = priority_avg.awt;
		strcpy(best,"Priority scheduling is the best option");
	}
	if(rr_avg.awt < wait)
	{
		wait = rr_avg.awt;
		strcpy(best,"Priority scheduling is the best option");
	}

	printf("%s\n",best);

	return 0;

}