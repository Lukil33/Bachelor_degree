#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <stdint.h>
#include <pthread.h>
#include <sys/stat.h>
#include <errno.h>

struct msg_buffer{
    long priority;
    char message[100];
};

int main(){
    srand(time(0));
    // Creo la mia coda utilizzando una chiave randomica
    int ID_coda = msgget(IPC_PRIVATE,0666);
    
    //Inserisco all'interno della cosa i miei messaggi
    for(int i=0; i<20; i++){
        struct msg_buffer messaggio;
        messaggio.priority = (rand()%20)+1;
        sprintf(messaggio.message,"Palle %d",i);
        msgsnd(ID_coda,&messaggio,sizeof(messaggio),0);
    }
    
    int i = 1;
    while(i<=20){
        struct msg_buffer messaggio;
        int res = msgrcv(ID_coda,&messaggio,sizeof(messaggio),i,O_NONBLOCK);
        if(res != -1){
            printf("MessaggioRicevuto: Priorità %ld - Messaggio %s\n",messaggio.priority,messaggio.message);
        }else{
            i += 1;
            printf("Aumentato i\n");
        }
    }

    // Infine elimino la mia coda
    msgctl(ID_coda,IPC_RMID,NULL);
}