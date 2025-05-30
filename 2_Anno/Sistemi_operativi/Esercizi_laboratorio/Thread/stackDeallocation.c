#include <stdio.h>
#include <pthread.h>
#include <unistd.h> //thJoinStack.c

void * my_fun(void * param){
    int val = 34;
    pthread_exit((void *)&val); //or ‘return (void *) val;’
}

int main(void){
    pthread_t t_id;
    void * retFromThread; //This must be a pointer to void!
    pthread_create(&t_id, NULL, my_fun, (void *)&t_id); //Create
    pthread_join(t_id,&retFromThread); // wait thread
    printf("Thread %ld returned '%d'\n",t_id,*(int *)retFromThread);
}