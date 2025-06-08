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
#include <time.h>

void funzione(int idScrittura, int idLettura){
    srand(time(0)^getpid());
    int check = 1;
    while(check){
        char messaggio;
        int risposta;
        read(idLettura, &messaggio, sizeof(char));
        if(messaggio == 'q'){
            close(idScrittura);
            close(idLettura);
            printf("Child terminating...\n");
            fflush(stdout);
            check = 0;
        }else if(messaggio == 'i'){
            printf("Child sending own pid...\n");
            fflush(stdout);
            risposta = getpid();
        }else if(messaggio == 'r'){
            printf("Child computing random...\n");
            fflush(stdout);
            risposta = rand();
        }
        write(idScrittura, &risposta, sizeof(int));
    }
}

int main(int argc, char** argv){
    if(argc != 2){
        fprintf(stderr, "Error: ./a.out <N>\n");
        fflush(stderr);
        exit(1);
    }

    const int N = atoi(argv[1]);
    int** pip = (int**)malloc(sizeof(int*)*N);
    for(int i=0; i<N; i++){
        pip[i] = (int*)malloc(sizeof(int)*2);
    }

    int padre = getpid();
    for(int i=0; i < N; i++){
        if(padre == getpid()){
            int pipeLettura[2], pipeScrittura[2];
            pipe(pipeLettura);
            pipe(pipeScrittura);
            pip[i][0] = pipeLettura[0];
            pip[i][1] = pipeScrittura[1];
            int figlio = fork();
            if(figlio == 0){
                funzione(pipeLettura[1],pipeScrittura[0]);
            }
        }
    }

    if(padre == getpid()){
        char input[10],carattere;
        int numero;
        do{
            printf("new command: ");
            fflush(stdout);
            scanf("%s",input);
            if(input[0] == 'i' || input[0] == 'r'){
                sscanf(input, "%c%d",&carattere,&numero);
                if(numero > N || numero < 1){
                    fprintf(stderr, "Error: wrong target\n");
                    fflush(stderr);
                }else{
                    int risposta;
                    numero -= 1;
                    write(pip[numero][1], &carattere, sizeof(char));
                    read(pip[numero][0], &risposta, sizeof(risposta));
                    printf("Child %d told me: %d\n", numero+1, risposta);
                    fflush(stdout);
                }
            }else if(input[0] != 'q'){
                fprintf(stderr, "Error: wrong parameter\n");
                fflush(stderr);
            }else{
                for(int i=0; i<N; i++){
                    write(pip[i][1], &input[0], sizeof(char));
                }
            }
        }while(input[0] != 'q');

        for(int i=0; i<N; i++){
            close(pip[i][0]);
            close(pip[i][1]);
        }
    }

    while(wait(NULL)>0);

    for(int i=0; i<N; i++){
        free(pip[i]);
    }
    free(pip);
    
    return 0;
}