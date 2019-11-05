#include<stdio.h>
#define _BSD_SOURCE
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<ctype.h>
#include<string.h>
int SharedVariable=0;

// initializing thread related variables
pthread_mutex_t lock;
pthread_barrier_t barrier;

// Thread function to modify the shared variable
void* SimpleThread(void  *arg)
{
    int which=*(int*)arg;
    int num,val;
    for (num=0; num<20; num++)
    {
        //entering thread locks this critical section
        pthread_mutex_lock(&lock);

        val=SharedVariable;
        printf("*** thread %d sees value %d\n",which,val);
        SharedVariable=val+1;
        //entering thread unlocks the critical section and go to sleep
        pthread_mutex_unlock(&lock);
        if(random()>RAND_MAX/2)
        {
            usleep(500);
        }
        //entering thread is waiting for other threads to complete it's own execution
        pthread_barrier_wait(&barrier);

    }
    val=SharedVariable;
    printf("....................................................\n");
    printf("Thread %d sees final values %d\n",which,val);
}

int main(int argc,char **argv)
{
    // checking whether user has given correct input for no of threads
    int flag=1;
    if(argc<2 )
    {
        printf("Please enter the no of threads.\n");
        exit(-1);
    }
    else
    {//check whether the command line argument is integer or not
        for( int i=0; i<strlen(argv[1]); i++)
        {

            if(isdigit(argv[1][i])==0)
            {
                printf("You entered a character.Enter an integer for threads.\n");
                flag=0;
                break;
            }
        }
        // user entered a character, so exit
        if(flag==0)exit(-1);

        int number_of_threads=atoi(argv[1]);
        int thread_ids[number_of_threads];
        pthread_t threads[number_of_threads];
        pthread_mutex_init(&lock,NULL);
        pthread_barrier_init(&barrier,NULL,number_of_threads);
        // creating pool of threads
        for (int i=0; i<number_of_threads; i++)
        {
            thread_ids[i]=i;
            int error=pthread_create(&threads[i],NULL,SimpleThread,&thread_ids[i]);
            if( error!=0)
            {
                printf("Thread %d is not created",i);
            }
        }
        // waiting for all the threads to finish
        for (int i=0; i<number_of_threads; i++)
        {
            pthread_join(threads[i],NULL);
        }
        pthread_barrier_destroy(&barrier);
    }

    return 0;

}
