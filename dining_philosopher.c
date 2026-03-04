#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <time.h>

#define N 5

sem_t forks[N], room;

void *philosopher(void *arg)
{
    while (1)
    {
        int i = *(int *)arg;

        printf("Philosopher %d is thinking\n", i);
        sleep(rand() % 3 + 1);

        sem_wait(&room);
        sem_wait(&forks[i]);
        sem_wait(&forks[(i + 1) % N]);

        printf("Philosopher %d is eating\n", i);
        sleep(2);

        printf("Philosopher %d finished eating\n", i);

        sem_post(&room);
        sem_post(&forks[i]);
        sem_post(&forks[(i + 1) % N]);

        sleep(rand() % 3 + 1);
    }

    return NULL;
}

int main()
{
    srand(time(NULL));

    pthread_t p[N];
    int id[N];

    sem_init(&room, 0, N - 1);

    for (int i = 0; i < N; i++)
    {
        sem_init(&forks[i], 0, 1);
    }

    for (int i = 0; i < N; i++)
    {
        id[i] = i;
        pthread_create(&p[i], NULL, philosopher, &id[i]);
    }

    for (int i = 0; i < N; i++)
    {
        pthread_join(p[i], NULL);
    }

    return 0;
}
