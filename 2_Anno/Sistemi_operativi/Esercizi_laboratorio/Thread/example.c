#include <stdio.h>
#include <pthread.h>
#include <unistd.h> //threadCreate.c

void * my_fun(void * param){
    printf("This is the thread %ld that received %d\n",
    pthread_self(),(int)param);
    //pthread_self() returns the id of the thread
    return NULL;
}

int main(void){
    pthread_t t_id;
    int arg=10;
    // We need to cast the augment to a void *.
    pthread_create(&t_id, NULL, my_fun, (void *)arg);
    printf("Executed thread with id %ld\n",t_id);
    sleep(3);
}