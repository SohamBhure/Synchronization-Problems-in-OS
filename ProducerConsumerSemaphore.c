// producer consumer problem using semaphore

#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>


//binary semaphore
sem_t BS;
sem_t bufferFull, bufferEmpty;

int data[10];
int ptr = 0;



void* producer()
{
    int new_item = rand()%100;

    //down(bufferEmpty)
    //down(BS)

    sem_wait(&bufferEmpty);
    sem_wait(&BS);

    //int new_item = rand()%100;
    printf("\nProducer inside the Critical Section"); // produced: %d", new_item);
    data[ptr] = new_item;
    ptr++;

    sem_post(&BS);
    sem_post(&bufferFull);
    printf("\nProducer outside the Critical Section.");


}


void* consumer()
{
    sem_wait(&bufferFull);
    sem_wait(&BS);

    int item = data[ptr-1];
    ptr--;

    printf("\nConsumer Inside the Critical Section, consumed: %d", item);

    sem_post(&bufferEmpty);
    sem_post(&BS);

    printf("\nConsumer Outside the Critical Section");


}




int main()
{
    sem_init(&bufferEmpty, 0, 10);
    sem_init(&bufferFull, 0, 0);
    sem_init(&BS, 0, 1);



    pthread_t thread_producers[50], thread_consumers[50];
    int N;


    printf("\nEnter Number of People Trying to access the Critical Section: ");
    scanf("%d", &N);


    for(int i=0; i<N; i++)
    {
        pthread_create(&thread_producers[i], 0, producer, 0);
        pthread_create(&thread_consumers[i], 0, consumer, 0);
    }


/*
    for(int i=0; i<5; i++)
    {
        pthread_create(&thread_consumers[i], 0, consumer, 0);
    }
*/

    for(int i=0; i<N; i++)
    {
        pthread_join(thread_producers[i],NULL);
        pthread_join(thread_consumers[i],NULL);
    }



    //pthread_join(thread1,NULL);
    //pthread_join(thread2,NULL);


    sem_destroy(&bufferEmpty);
    sem_destroy(&bufferFull);
    sem_destroy(&BS);




}