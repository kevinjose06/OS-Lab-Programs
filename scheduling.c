/*Input a list of processes, their CPU burst times (integral values), arrival times, and
priorities. Then simulate FCFS, SRTF, non-preemptive priority (a larger priority number
implies a higher priority), and RR (quantum = 3 units) scheduling algorithms on the
process mix, determining which algorithm results in the minimum average waiting time
(over all processes).
*/

#include<stdio.h>
#include<stdlib.h>

struct process
{
	int pid,at,bt,pr,rt,ct,tt,wt,c;
};

struct stat
{
	float art,act,att,awt;
};

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

	return res;

}

int main()
{
	int n,i;
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
		printf("Enter priority of the process : ");
		scanf("%d",&p[i].pr);
		p[i].c = 0;
	}

	fcfs_avg = fcfs(p,n);
/*	srtf_avg = srtf(p,n);
	priority_avg = priority(p,n);
	rr_avg = rr(p,n);
*/
	return 0;
}