/*Simulate the SSTF, LOOK, and CSCAN disk-scheduling algorithms as follows: Your
program will service a disk with 5,000 cylinders numbered 0 to 4,999. The program will
generate a random series of 10 cylinder requests and service them according to each of the
algorithms listed earlier. The program will be passed the initial position of the disk head
(as a parameter on the command line) and will report the total number of head movements
required by each algorithm. */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 5000
#define REQ 10

void sort(int arr[], int n)
{
    for(int i=0;i<n-1;i++)
        for(int j=0;j<n-i-1;j++)
            if(arr[j] > arr[j+1])
            {
                int t = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = t;
            }
}

int sstf(int req[], int head)
{
    int visited[REQ]={0};
    int total=0;

    for(int i=0;i<REQ;i++)
    {
        int min=10000, index=-1;

        for(int j=0;j<REQ;j++)
        {
            if(!visited[j])
            {
                int dist = abs(head-req[j]);
                if(dist < min)
                {
                    min = dist;
                    index = j;
                }
            }
        }

        total += min;
        head = req[index];
        visited[index]=1;
    }

    return total;
}

int look(int req[], int head)
{
    int total=0;
    int arr[REQ];

    for(int i=0;i<REQ;i++)
        arr[i]=req[i];

    sort(arr,REQ);

    int pos;

    for(pos=0;pos<REQ;pos++)
        if(arr[pos] > head)
            break;

    for(int i=pos;i<REQ;i++)
    {
        total += abs(head-arr[i]);
        head = arr[i];
    }

    for(int i=pos-1;i>=0;i--)
    {
        total += abs(head-arr[i]);
        head = arr[i];
    }

    return total;
}

int cscan(int req[], int head)
{
    int total=0;
    int arr[REQ];

    for(int i=0;i<REQ;i++)
        arr[i]=req[i];

    sort(arr,REQ);

    int pos;

    for(pos=0;pos<REQ;pos++)
        if(arr[pos] > head)
            break;

    for(int i=pos;i<REQ;i++)
    {
        total += abs(head-arr[i]);
        head = arr[i];
    }

    total += abs(head - 4999);
    head = 0;
    total += 4999;

    for(int i=0;i<pos;i++)
    {
        total += abs(head-arr[i]);
        head = arr[i];
    }

    return total;
}

int main(int argc,char *argv[])
{
    if(argc!=2)
    {
        printf("Usage: %s <initial_head_position>\n",argv[0]);
        return 1;
    }

    int head = atoi(argv[1]);

    int req[REQ];

    srand(time(NULL));

    printf("Requests:\n");

    for(int i=0;i<REQ;i++)
    {
        req[i] = rand()%5000;
        printf("%d ",req[i]);
    }

    printf("\n");

    printf("SSTF movement: %d\n", sstf(req,head));
    printf("LOOK movement: %d\n", look(req,head));
    printf("CSCAN movement: %d\n", cscan(req,head));

    return 0;
}
