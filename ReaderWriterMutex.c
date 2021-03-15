//reader-writer using mutex

#include<stdio.h>
#include<stdlib.h>
//#include<semaphore.h>
#include<pthread.h>


//sem_t var1, var2;
pthread_mutex_t LOCK, CC;

int rc=0;


void *reader()
{
    //sem_wait(&var1);

    pthread_mutex_lock(&LOCK);

    rc = rc+1;

    if(rc==1)
        pthread_mutex_lock(&CC);

    //sem_post(&var1);
    pthread_mutex_unlock(&LOCK);

    printf("\nReader entered critical section. Number of readers: %d",  rc);

    //sem_wait(&var1);
    pthread_mutex_lock(&LOCK);
    rc = rc - 1;


    if(rc==0)
        pthread_mutex_unlock(&CC);
        //sem_post(&var2);
    

    //sem_post(&var1);
    pthread_mutex_unlock(&LOCK);

        printf("\nReader has exited the critical section");
    }


void *writer()
{
    //sem_wait(&var2);
    pthread_mutex_lock(&CC);

    printf("\nWriter has entered the critical section");

    //sem_post(&var2);
    pthread_mutex_unlock(&CC);

    printf("\nWriter has exited the critical section");

}



int main()
{
    //sem_init(&var1, 0, 0);
    //sem_init(&var2, 0, 0);

    pthread_mutex_init(&LOCK, NULL);
    pthread_mutex_init(&CC, NULL);


    pthread_t thread_readers[50], thread_writers[50];
    int N;


    printf("\nEnter Number of People Trying to access the Critical Section: ");
    scanf("%d", &N);


    for(int i=0; i<N; i++)
    {
        pthread_create(&thread_readers[i], 0, reader, 0);
        pthread_create(&thread_writers[i], 0, writer, 0);
    }

    for(int i=0; i<N; i++)
    {
        pthread_join(thread_writers[i],NULL);
        pthread_join(thread_readers[i],NULL);
    }
    


    //sem_destroy(&var1);
    //sem_destroy(&var2);

    pthread_mutex_destroy(&LOCK);
    pthread_mutex_destroy(&CC);




}
