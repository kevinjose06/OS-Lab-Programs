#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#define MAX 10

int buffer[MAX];
int in = 0,out = 0;
sem_t lock,full,empty;

void *producer(void *args)
{
	int i;

	for(i = 0;i < MAX;i++)
	{
		sem_wait(&empty);
		sem_wait(&lock);
		buffer[in] = (i + 1);
		in = (in + 1) % MAX;
		sem_post(&lock);
		sem_post(&full);
	}
	return NULL;
}

void *consumer(void *args)
{
	int i,item;

        for(i = 0;i < MAX;i++)
        {
                sem_wait(&full);
                sem_wait(&lock);
                item = buffer[out];
		out = (out + 1) % MAX;
                sem_post(&lock);
                sem_post(&empty);
		printf("%d ",item);
        }
	printf("\n");
	return NULL;
}

int main()
{
	pthread_t prod,cons;

	sem_init(&lock,0,1);
	sem_init(&full,0,0);
	sem_init(&empty,0,MAX);

	pthread_create(&prod,NULL,producer,NULL);
	pthread_create(&cons,NULL,consumer,NULL);

	pthread_join(prod,NULL);
	pthread_join(cons,NULL);

	sem_destroy(&lock);
	sem_destroy(&full);
	sem_destroy(&empty);

	return 0;
}