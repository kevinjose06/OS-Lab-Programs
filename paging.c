/*Simulate the FIFO, LRU, and optimal page-replacement algorithms as follows: First,
generate a random page-reference string where page numbers range from 0 to 9. Apply the
random page-reference string to each algorithm, and record the number of page faults
incurred by each algorithm. Assume that demand paging is used. The length of the
reference string and the number of page frames (varying from 1 to 7) are to be received as
command line arguments. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int search(int key, int frame[], int f)
{
    for(int i=0;i<f;i++)
        if(frame[i]==key)
            return 1;
    return 0;
}

int fifo(int ref[], int n, int f)
{
    int frame[f];
    int faults=0;
    int index=0;

    for(int i=0;i<f;i++)
        frame[i] = -1;

    for(int i=0;i<n;i++)
    {
        if(!search(ref[i], frame, f))
        {
            frame[index] = ref[i];
            index = (index+1)%f;
            faults++;
        }
    }

    return faults;
}

int lru(int ref[], int n, int f)
{
    int frame[f];
    int time[f];
    int faults=0, counter=0;

    for(int i=0;i<f;i++)
        frame[i] = -1;

    for(int i=0;i<n;i++)
    {
        int found = 0;

        for(int j=0;j<f;j++)
        {
            if(frame[j]==ref[i])
            {
                counter++;
                time[j] = counter;
                found = 1;
                break;
            }
        }

        if(!found)
        {
            int pos=0;

            for(int j=1;j<f;j++)
                if(time[j] < time[pos])
                    pos = j;

            frame[pos] = ref[i];
            counter++;
            time[pos] = counter;
            faults++;
        }
    }

    return faults;
}

int optimal(int ref[], int n, int f)
{
    int frame[f];
    int faults=0;

    for(int i=0;i<f;i++)
        frame[i] = -1;

    for(int i=0;i<n;i++)
    {
        if(search(ref[i],frame,f))
            continue;

        int pos=-1, farthest=i;

        for(int j=0;j<f;j++)
        {
            int k;
            for(k=i+1;k<n;k++)
                if(frame[j]==ref[k])
                    break;

            if(k>farthest)
            {
                farthest=k;
                pos=j;
            }
        }

        if(pos==-1)
            pos=0;

        frame[pos]=ref[i];
        faults++;
    }

    return faults;
}

int main(int argc,char *argv[])
{
    if(argc!=3)
    {
        printf("Usage: %s <reference_length> <frames>\n",argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    int f = atoi(argv[2]);

    if(f<1 || f>7)
    {
        printf("Frames must be between 1 and 7\n");
        return 1;
    }

    int ref[n];

    srand(time(NULL));

    printf("Reference string:\n");

    for(int i=0;i<n;i++)
    {
        ref[i] = rand()%10;
        printf("%d ",ref[i]);
    }

    printf("\n");

    printf("FIFO faults: %d\n", fifo(ref,n,f));
    printf("LRU faults: %d\n", lru(ref,n,f));
    printf("Optimal faults: %d\n", optimal(ref,n,f));

    return 0;
}