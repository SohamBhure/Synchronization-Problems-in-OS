//reader-writer using semaphore

#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>


sem_t var1, var2;
int rc=0;


void *reader()
{
    sem_wait(&var1);
    rc = rc+1;


    //for first reader entering
    if(rc==1)
        sem_wait(&var2);

    sem_post(&var1);

    printf("\nReader entered critical section. Number of readers: %d",  rc);

    sem_wait(&var1);
    rc = rc - 1;

    //for last reader exiting 
    if(rc==0)
        sem_post(&var2);
    

    sem_post(&var1);

        printf("\nReader has exited the critical section");
}


void *writer()
{
    sem_wait(&var2);

    printf("\nWriter has entered the critical section");

    sem_post(&var2);

    printf("\nWriter has exited the critical section");

}



int main()
{
    sem_init(&var1, 0, 0);
    sem_init(&var2, 0, 0);


    pthread_t thread_readers[50], thread_writers[50];
    int N;

    //pthread_create(&thread1, 0, reader, 0);
    //pthread_create(&thread2, 0, writer, 0);


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
    


    //pthread_join(thread1,NULL);
    //pthread_join(thread2,NULL);


    sem_destroy(&var1);
    sem_destroy(&var2);




}
