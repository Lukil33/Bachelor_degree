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

void create_player(){

    // Faccio in modo oche rand() sia randomico
    srand(time(0)^getpid());

    // Controllo il numero dei figli
    //printf("Figlio %d: ID %d\n",i,getpid());

    // Creo il file ed inserisco le informazioni necessarie
    char percorso[20];
    sprintf(percorso,"/tmp/%d.txt",getpid());
    creat(percorso,0666);
    int fileT = open(percorso, O_WRONLY);
    char dati[20];
    int ELO = ((rand()%40)+1)*100;
    sprintf(dati,"%d\n%d\n",getpid(),ELO);
    write(fileT,dati,strlen(dati));

    // Controllo il valore dell'ELO per ogni figlio
    //printf("ID %d: ELO %d\n",getpid(),ELO);
    //fflush(stdout);
}

int main(int argc, char** argv){
    // Controllo il numero di valori passati per input
    if(argc != 3){
        fprintf(stderr, "Error: devi inserire ./<nome_eseguibile> <percorso_arbitro> <numeroGiocatori>\n");
        fflush(stdout);
        exit(50);
    }
    // Controllo che i valori passati in input rispettino i vincoli necessari
    int arbitro = open(argv[1], O_RDONLY);
    if(arbitro == -1){
        fprintf(stderr, "Error: il file arbitro non esiste\n");
        fflush(stdout);
        exit(50);
    }
    int n = atoi(argv[2]);
    if(n < 2 || n > 32){
        fprintf(stderr, "Error: il numero di giocatori è errato\n");
        fflush(stdout);
        exit(50);
    }

    // INIZIO fase di preparazione
    int padre = getpid();
    // Genero gli n giocatori 
    for(int i=0; i<n; i++){
        if(getpid() == padre){
            int figlio = !fork();
            if(figlio){
                create_player();
            }
        }
    }
    // FINE fase di preparazione

    // INIZIO fase di gioco

    // 
    if(getpid() == padre){

    }

    // FINE fase di gioco
    
    while(wait(NULL) > 0);
}