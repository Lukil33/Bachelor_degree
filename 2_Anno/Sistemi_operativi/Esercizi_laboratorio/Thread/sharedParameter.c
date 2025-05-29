#include <stdio.h>
#include <pthread.h>
#include <unistd.h> //threadCreate.c

int globalVar = 3; //It is shared among all threads!

void * my_fun(void * param){
    printf("This is a thread that received %d\n", *(int *)param);
    *(int *)param = 6;
    sleep(5);
    printf("This is a thread that received %d\n", *(int *)param);
    return (void *)3;
}

int main(void){
    pthread_t t_id;
    int arg=10;
    pthread_create(&t_id, NULL, my_fun, (void *)&arg);
    sleep(1);
    printf("This is the main function with the value param of %d\n", arg);
    arg=20; //This changes the value also for the thread!
    sleep(6);
}