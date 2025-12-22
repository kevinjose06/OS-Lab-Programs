/*Write a multithreaded program that calculates the mean, median, and standard deviation
for a list of integers. This program should receive a series of integers on the command line
and will then create three separate worker threads. The first thread will determine the
mean value, the second will determine the median and the third will calculate the standard
deviation of the integers. The variables representing the mean, median, and standard
deviation values will be stored globally. The worker threads will set these values, and the
parent thread will output the values once the workers have exited.*/

#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<math.h>

double mean,median,sd;
int n;
int *nums;

void * cal_mean(void * args)
{
	int i,s = 0;

	for(i = 0;i < n;i++)
	{
		s += nums[i];
	}
	mean = (double)s/n;
	return NULL;
}

void * cal_median(void * args)
{
	int i,j,k;

	for(i = 1;i < n;i++)
	{
		k = nums[i];
		j = i -1;

		while((j >= 0)&&(nums[j] > k))
		{
			nums[j+1] = nums[j];
			j -= 1;
		}
		nums[j+1] = k;
	}
	if(n % 2 != 0)
	{
		median = nums[n/2];
	}
	else
	{
		median = (nums[n/2 - 1] + nums[n/2]) / 2.0;
	}

	return NULL;
}

void * cal_sd(void * args)
{
	int i;
	double sum = 0;
	for(i = 0;i < n;i++)
	{
		sum += pow((nums[i] - mean),2);
	}
	sum = (double)sum / n;
	sd = sqrt(sum);

	return NULL;
}

int main(int argc,char * argv[])
{
	pthread_t tid1,tid2,tid3;
	int i;
	n = argc - 1;
	nums = malloc(n * sizeof(int));

	for(i = 0;i < n;i++)
	{
		nums[i] = atoi(argv[i+1]);
	}

	if(pthread_create(&tid1,NULL,cal_mean,NULL) != 0)
	{
		printf("Error!Process 1 failed");
		return -1;
	}
	else
	{
		pthread_join(tid1,NULL);
	}
	if(pthread_create(&tid2,NULL,cal_median,NULL) != 0)
	{
		printf("Error!Process 2 failed");
		return -1;
	}
	if(pthread_create(&tid3,NULL,cal_sd,NULL) != 0)
	{
		printf("Error!Process 3 failed");
		return -1;
	}

	pthread_join(tid2,NULL);
	pthread_join(tid3,NULL);
	
	printf("Thread ID : %ld\tMean : %f\n",tid1,mean);
	printf("Thread ID : %ld\tMedian : %f\n",tid2,median);
	printf("Thread ID : %ld\tStandard Deviation : %f\n",tid3,sd);

	return 0;
}

/*
    1)Compilation command : gcc <filename> -pthread -lm
    2)Make sure to join thread 1 before executing thread 3 as,if not joined it may cause errors in the 
    standrd deviation calculation
*/