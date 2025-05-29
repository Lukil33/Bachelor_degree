#include <stdio.h>
#include <pthread.h>
#include <unistd.h> //threadCreate.c

void * thread1(void * param){
    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE,NULL); //Change mode
    printf("Thread %ld started\n",*(pthread_t *)param);
    sleep(3);

    printf("Thread %ld finished\n",*(pthread_t *)param);
}

void * thread2(void * param){
    printf("Thread %ld started\n",*(pthread_t *)param);
    sleep(3);

    printf("Thread %ld finished\n",*(pthread_t *)param);
}

int main(void){
    pthread_t t_id1, t_id2;
    pthread_create(&t_id1, NULL, thread1, (void *)&t_id1);
    sleep(1); //Create

    pthread_cancel(t_id1); //Cancel
    printf("Sent cancellation request for thread %ld\n",t_id1);
    pthread_create(&t_id2, NULL, thread2, (void *)&t_id2);
    sleep(1); //Create

    pthread_cancel(t_id2); //Cancel
    printf("Sent cancellation request for thread %ld\n",t_id2);
    sleep(5);

    printf("Terminating program\n");
}