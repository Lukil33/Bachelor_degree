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

char path[100];
FILE* f;

struct buffer{
    long mtype;
    char mmessage[50];
};

struct args{
    char first_arg[50];
    char second_arg[50];
};

void* sendkill(void* arg){
    kill(atoi(((struct args *)arg)->second_arg),atoi(((struct args *)arg)->first_arg));
    printf("Processo %d killato con flag %d\n",((struct args *)arg)->second_arg),atoi(((struct args *)arg)->first_arg);
    return NULL;
}

void* sendqueue(void* arg){
    printf("Messaggio inviato alla coda\n");
    key_t chiave = ftok(path, 1);
    int idCoda = msgget(chiave,IPC_CREAT | 0666);
    struct buffer b;
    b.mtype = atol(((struct args *)arg)->first_arg);
    strcpy(b.mmessage, ((struct args *)arg)->second_arg);
    msgsnd(idCoda, &b, strlen(b.mmessage), 0);
    return NULL;
}

void* sendfifo(void* arg){
    printf("Messaggio inviato alla fifo\n");
    mkfifo(((struct args *)arg) -> first_arg, S_IRUSR|S_IWUSR);
    int fifo = open(((struct args *)arg) -> first_arg, O_WRONLY);
    write(fifo, ((struct args *)arg)->second_arg, strlen(((struct args *)arg)->second_arg));
    close(fifo);
    return NULL;
}

void manageInput(int){
    char messaggio[100];
    struct args a;
    fscanf(f,"%s %s %s\n",messaggio,a.first_arg,a.second_arg);
    pthread_t p;
    printf("messaggio: %s\narg1: %s\narg2: %s\n",messaggio,a.first_arg,a.second_arg);
    if(messaggio[0] == 'k'){
        pthread_create(&p, NULL, sendkill, (void*)&a);
    }else if(messaggio[0] == 'q'){
        pthread_create(&p, NULL, sendqueue, (void*)&a);
    }else if(messaggio[0] == 'f'){
        pthread_create(&p, NULL, sendkill, (void*)&a);
    }else{
        fprintf(stderr,"Error: a problem occurred while reading file\n");
        exit(1);
    }
    sleep(1);
}

int main(int argc, char** argv){
    if(argc != 2){
        fprintf(stderr,"Error: <exectuable> <pathToFile>\n");
        exit(1);
    }

    strcpy(path, argv[1]);

    f = fopen(path,"r");
    if(f == NULL){
        fprintf(stderr,"Error: a problem occurred while opening file\n");
        exit(1);
    }

    struct sigaction sa;
    sa.sa_handler = manageInput;
    sa.sa_flags=0;
    sigaction(SIGUSR1, &sa, NULL);
    while(1){
        printf("PID: %d\n",getpid());
        pause();
    }
    return 0;
}