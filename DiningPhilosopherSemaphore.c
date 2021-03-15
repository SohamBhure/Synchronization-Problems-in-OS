//dining philosopher using semaphores

#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>

#define n 5

#define left (pno+4)%n
#define right (pno+1)%n

sem_t S[n];

int condition[n] = {0};
int p_num[n] = {0,1,2,3,4};


void *philospher(void *num)
{   
   
    while(1)
    {
        int *i = num;
        
        sleep(1);
        take_fork(*i);
        sleep(0);
        put_fork(*i);
    }
}

void take_fork(int pno)
{
    
    condition[pno] = 1;
    printf("%d\t\tHungry \n",pno+1);
    
    test(pno);
    sem_wait(&S[pno]);
    sleep(1);
}



void put_fork(int pno)
{
    
    condition[pno] = 0;
    printf("%d\t\tPutting down fork number %d and %d down \n",pno+1,left+1,pno+1);
    printf("%d\t\tThinking \n",pno+1);
    
    test(left);
    test(right);
}



void test(int pno)
{
    if (condition[pno] == 1 && condition[left] != 2 && condition[right] != 2)
    {
        condition[pno] = 2;
        sleep(2);
        printf("%d\t\tLifted fork number %d and %d \n",pno+1,left+1,pno+1);
        printf("%d\t\tEating \n",pno+1);
        
        sem_post(&S[pno]);
    }
}



int main()
{
    pthread_t philosophers[n];


    printf("\nPhilosopher\tState\n\n");
    
    //sem_int(&S, 0, 0);
    for(int i=0;i<n;i++)
    {
        sem_init(&S[i],0,0);
    }

    for(int i=0;i<n;i++)
    {
        pthread_create(&philosophers[i],NULL,philospher,&p_num[i]);
        //printf("Philosopher %d - Thinking \n",i+1);
    }

    for(int i=0;i<n;i++)
    {
        pthread_join(philosophers[i],NULL);
    }
}