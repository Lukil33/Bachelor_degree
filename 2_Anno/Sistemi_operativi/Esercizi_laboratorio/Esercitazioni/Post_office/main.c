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

char path[100];
FILE* f;

struct buffer{
    long mtype;
    char mmessage[100];
};

void resendSignal(int signal,siginfo_t* info,void*){
    kill(info -> si_pid, SIGUSR2);
}

void lavoratore(int pid){
    printf("Sono il figlio con ID %d\n",getpid());
    kill(pid, SIGTERM);
    
    struct sigaction s;
    sigemptyset(&s.sa_mask);
    s.sa_flags=SA_SIGINFO;
    s.sa_sigaction=resendSignal;
    
    sigaction(SIGUSR2, &s, NULL);

    s.sa_flags |= SA_RESETHAND;

    sigaction(SIGUSR1, &s, NULL);

    while(1){
        pause();
    }
}

void sendfile(int){
    key_t chiave = ftok(path,getpid());
    int idCoda = msgget(chiave, IPC_CREAT | 0777);
    struct buffer b;
    while(fprintf(f,"%s\n",b.mmessage)){
        
    }
}

int main(int argc, char** argv){
    if(argc != 4){
        fprintf(stderr,"Error: <executable> <n> <path/to/file.txt> <pidInput>\n");
        return 1;
    }

    int n = atoi(argv[1]);
    if(n < 1 || n > 10){
        fprintf(stderr,"Error: n value does not respect all the bound limits\n");
        return 1;
    }

    strcpy(path, argv[2]);
    f = fopen(argv[2],"r");
    if(f == NULL){
        fprintf(stderr,"Error: a problem occurred while searching for the file in the path\n");
        return 1;
    }

    int pid = atoi(argv[3]);
    if(kill(pid,0) == -1){
        fprintf(stderr,"Error: the pid given is not active\n");
        return 1;
    }

    int padre = getpid();
    for(int i=0; i<n; i++){
        if(getpid() == padre){
            int figlio = fork();
            if(figlio == 0){
                lavoratore(pid);
            }
        }
    }

    if(getpid() == padre){
        struct sigaction si;
        si.sa_handler = sendfile;
        si.sa_flags = 0;
        sigaction(SIGWINCH, &si, NULL);

        while(1){
            pause();
        }
    }
    return 0;
}