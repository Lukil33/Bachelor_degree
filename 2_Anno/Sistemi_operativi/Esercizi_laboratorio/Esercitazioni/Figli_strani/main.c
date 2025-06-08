#include <bits/types/sigset_t.h>
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
#define PATH_MAXLEN 60
#define CHILDREN_MAX 10
#define PIDLEN 8

int idCoda, file;

struct msg_buffer{
    long mtype;
    char mtext[100];
};

void scritturaSuFile(int){
    char messaggio[10];
    sprintf(messaggio, "SIGUSR1\n");
    write(file,messaggio,strlen(messaggio));
}

void scritturaSuCoda(int){
    struct msg_buffer s;
    s.mtype = 1;
    sprintf(s.mtext,"%d\n",getpid());
    msgsnd(idCoda, &s, strlen(s.mtext), 0);
}

void gestisciAborto(char folPath[PATH_MAXLEN]){
    struct sigaction s1; // Creo la sigaction per SIGUSR1
    s1.sa_handler = scritturaSuFile;
    s1.sa_flags = 0;
    sigemptyset(&s1.sa_mask);
    sigaction(SIGUSR1, &s1, NULL); // Applico la sigaction per SIGUSR1

    struct sigaction s2; // Creo la sigaction per SIGUSR2
    s2.sa_handler = scritturaSuCoda;
    s2.sa_flags = 0;
    sigemptyset(&s2.sa_mask);
    sigaction(SIGUSR2, &s2, NULL); // Applico la sigaction per SIGUSR2

    char filePath[PATH_MAXLEN];
    sprintf(filePath, "%s/%d.txt",folPath,getpid()); // Creo il file path
    file = open(filePath,O_WRONLY|O_CREAT,0666); // Creo il file
    while(1){pause();}// Attendo l'arrivo dei vari segnali
}

int main(int argc, char** argv){
    if(argc != 3){ // Controllo dei vincoli sul numero di elementi in input
        fprintf(stderr,"Error: input format -> ./app <path> <N>\n");
        exit(1);
    }

    if(open(argv[1],O_DIRECTORY) == -1){ // Controllo dei vincoli sul path
        fprintf(stderr,"Error: the path isn't pathing\n");
        exit(1);
    }
    int N = atoi(argv[2]);
    if( N < 1 || N > CHILDREN_MAX){ // Controllo dei vincoli su N
        fprintf(stderr,"Error: N out of bound\n");
        exit(1);
    }

    char folPath[PATH_MAXLEN], filePath[PATH_MAXLEN], messaggio[CHILDREN_MAX+8]; // Inizializzo i due path
    sprintf(folPath, "%s/info",argv[1]); // Creo il folder path
    sprintf(filePath, "%s/key.txt",folPath); // Creo il file path
    mkdir(folPath, 0755); // Creo la folder
    int file = open(filePath,O_CREAT | O_WRONLY | O_TRUNC,0755); // Creo il file
    sprintf(messaggio,"%d\n",getpid()); // Creo il messaggio per il file key
    write(file,messaggio,strlen(messaggio)); // Scrivo il messaggio sul file key
    close(file);

    key_t chiave = ftok(filePath, 32);
    if(chiave == -1){
        fprintf(stderr,"Error: DIO MERDA\n");
        exit(1);
    }
    idCoda = msgget(chiave, 0666);
    if(idCoda != -1){
        if (msgctl(idCoda, IPC_RMID, NULL) == -1) {
            fprintf(stderr,"Error: problem while removing the queue\n");
            exit(1);
        }
    }
    idCoda = msgget(chiave,IPC_CREAT | 0666);

    int padre = getpid();
    for(int i=0; i<N; i++){
        if(padre == getpid()){
            int figlio = fork();
            if(figlio == 0){
                gestisciAborto(folPath);
            }else{
                fprintf(stdout,"%d ",figlio);
                fflush(stdout);
            }
        }
    }
    if(padre == getpid()){
        fprintf(stdout,"\n");
    }

    while(wait(NULL)>0);

    return 0;
}