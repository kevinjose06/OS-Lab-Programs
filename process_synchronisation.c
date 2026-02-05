#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX 10
#define NPHIL 5

int buffer[MAX];
int in = 0, out = 0;
sem_t lock, empty, full;

void *producer(void *arg)
{
    int i;
    for (i = 0; i < MAX; i++)
    {
        sem_wait(&empty);
        sem_wait(&lock);

        buffer[in] = i + 1;
        in = (in + 1) % MAX;
        printf("Producer produced: %d\n", i + 1);

        sem_post(&lock);
        sem_post(&full);
    }
    return NULL;
}

void *consumer(void *arg)
{
    int i, item;
    for (i = 0; i < MAX; i++)
    {
        sem_wait(&full);
        sem_wait(&lock);

        item = buffer[out];
        out = (out + 1) % MAX;
        printf("Consumer consumed: %d\n", item);

        sem_post(&lock);
        sem_post(&empty);
    }
    return NULL;
}

void run_producer_consumer()
{
    pthread_t p, c;

    printf("\n--- PRODUCER CONSUMER ---\n");

    sem_init(&lock, 0, 1);
    sem_init(&empty, 0, MAX);
    sem_init(&full, 0, 0);

    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);

    pthread_join(p, NULL);
    pthread_join(c, NULL);

    sem_destroy(&lock);
    sem_destroy(&empty);
    sem_destroy(&full);
}

typedef struct {
    sem_t lock;
    sem_t writelock;
    int readers;
} rwlock_t;

rwlock_t rw;
int shared_data = 0;

void rwlock_init(rwlock_t *rw)
{
    rw->readers = 0;
    sem_init(&rw->lock, 0, 1);
    sem_init(&rw->writelock, 0, 1);
}

void rwlock_acquire_readlock(rwlock_t *rw)
{
    sem_wait(&rw->lock);
    rw->readers++;
    if (rw->readers == 1)
        sem_wait(&rw->writelock);
    sem_post(&rw->lock);
}

void rwlock_release_readlock(rwlock_t *rw)
{
    sem_wait(&rw->lock);
    rw->readers--;
    if (rw->readers == 0)
        sem_post(&rw->writelock);
    sem_post(&rw->lock);
}

void rwlock_acquire_writelock(rwlock_t *rw)
{
    sem_wait(&rw->writelock);
}

void rwlock_release_writelock(rwlock_t *rw)
{
    sem_post(&rw->writelock);
}

void *reader(void *arg)
{
    rwlock_acquire_readlock(&rw);
    printf("Reader reads value: %d\n", shared_data);
    rwlock_release_readlock(&rw);
    return NULL;
}

void *writer(void *arg)
{
    rwlock_acquire_writelock(&rw);
    shared_data += 10;
    printf("Writer writes value: %d\n", shared_data);
    rwlock_release_writelock(&rw);
    return NULL;
}

void run_reader_writer()
{
    pthread_t r, w;

    printf("\n--- READER WRITER ---\n");

    rwlock_init(&rw);

    pthread_create(&r, NULL, reader, NULL);
    pthread_create(&w, NULL, writer, NULL);

    pthread_join(r, NULL);
    pthread_join(w, NULL);

    sem_destroy(&rw.lock);
    sem_destroy(&rw.writelock);
}

sem_t forks[NPHIL];

void *philosopher(void *arg)
{
    int id = *(int *)arg;

    printf("Philosopher %d is thinking\n", id);
    sleep(1);

    sem_wait(&forks[id]);
    sem_wait(&forks[(id + 1) % NPHIL]);

    printf("Philosopher %d is eating\n", id);
    sleep(1);

    sem_post(&forks[id]);
    sem_post(&forks[(id + 1) % NPHIL]);

    printf("Philosopher %d finished eating\n", id);
    return NULL;
}

void run_dining_philosophers()
{
    pthread_t phil[NPHIL];
    int ids[NPHIL];
    int i;

    printf("\n--- DINING PHILOSOPHERS ---\n");

    for (i = 0; i < NPHIL; i++)
        sem_init(&forks[i], 0, 1);

    for (i = 0; i < NPHIL; i++)
    {
        ids[i] = i;
        pthread_create(&phil[i], NULL, philosopher, &ids[i]);
    }

    for (i = 0; i < NPHIL; i++)
        pthread_join(phil[i], NULL);

    for (i = 0; i < NPHIL; i++)
        sem_destroy(&forks[i]);
}

int main()
{
    run_producer_consumer();
    run_reader_writer();
    run_dining_philosophers();
    return 0;
}
