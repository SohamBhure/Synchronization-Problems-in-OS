// producer consumer problem using mutex

#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>


pthread_mutex_t LOCK; 
pthread_mutex_t bufferFull, bufferEmpty;

int data[10];
int ptr = 0;


void* producer()
{
    int new_item = rand()%100;

    if(ptr!=9) 
    {
        pthread_mutex_lock(&LOCK);
        //pthread_mutex_lock(&bufferEmpty);
    }
    else
        sleep(1);

    //pthread_mutex_lock(&LOCK);

    //int new_item = rand()%100;
    printf("\nProducer inside the Critical Section"); // produced: %d", new_item);
    data[ptr] = new_item;
    ptr++;


    pthread_mutex_unlock(&LOCK);
    //pthread_mutex_unlock(&bufferFull);
    

    printf("\nProducer outside the Critical Section.");


}



void* consumer()
{

    if(ptr!=0)
    {
        //pthread_mutex_lock(&bufferFull);
        pthread_mutex_lock(&LOCK);
    }
    else
        sleep(1);

    //pthread_mutex_lock(&LOCK);

    int item = data[ptr-1];
    ptr--;

    printf("\nConsumer Inside the Critical Section, consumed: %d", item);

    
    pthread_mutex_unlock(&LOCK);
    //pthread_mutex_unlock(&bufferEmpty);

    printf("\nConsumer Outside the Critical Section");
}



int main()
{

    
    pthread_mutex_init(&LOCK, NULL);
    //pthread_mutex_init(&bufferFull, NULL);
    //pthread_mutex_init(&bufferEmpty, NULL);


    pthread_t thread_producers[50], thread_consumers[50];
    int N;


    printf("\nEnter Number of People Trying to access the Critical Section: ");
    scanf("%d", &N);


    for(int i=0; i<N; i++)
    {
        pthread_create(&thread_producers[i], 0, producer, 0);
        pthread_create(&thread_consumers[i], 0, consumer, 0);
    }


    for(int i=0; i<N; i++)
    {
        pthread_join(thread_producers[i],NULL);
        pthread_join(thread_consumers[i],NULL);
    }


    pthread_mutex_destroy(&LOCK);
    //pthread_mutex_destroy(&bufferEmpty);
    //pthread_mutex_destroy(&bufferFull);


}



