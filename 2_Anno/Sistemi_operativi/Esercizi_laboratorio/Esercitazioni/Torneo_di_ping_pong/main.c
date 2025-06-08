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

int n;
char pathArbitro[100];

struct msg_buffer{
    long mtype;
    char mtext[100];
};

void manage_message(int, siginfo_t* info,void*){
    int avversario = info->si_value.sival_int; // Prendo l'ID avversario dal payload
    printf("Gioco contro %d\n",avversario);
    fflush(stdout);

    // Lettura dei vari elo
    char pathAvv[20],eloAvv[10],pathMio[20],eloMio[10];
    sprintf(pathMio,"/tmp/%d.txt",getpid()); // Creo il Path del mio file
    sprintf(pathAvv,"/tmp/%d.txt",avversario); // Creo il Path del file del mio avversario
    int mioFile = open(pathMio,O_RDONLY,0666); // Apro il mio file
    if(mioFile == -1){ // In caso di errore
        fprintf(stderr, "Error: file dati miei non trovato\n");
        fflush(stdout);
        exit(50);
    }
    int avvFile = open(pathAvv,O_RDONLY,0666); // Apro il file del mio avversario
    if(avvFile == -1){ // In caso di errore
        fprintf(stderr, "Error: file dati avversario non trovato\n");
        fflush(stdout);
        exit(50);
    }
    read(mioFile,&eloMio,sizeof(eloMio)); // Leggo il mio elo
    read(avvFile,&eloAvv,sizeof(eloMio)); // Leggo l'elo del mio avversario
    close(mioFile); // Chiudo il mio file
    close(avvFile); // Chiudo il file dell'avversario

    // Controllo e segnalo chi ha vinto
    if(atoi(eloMio) > atoi(eloAvv)){
        printf("%d Vinco\n",getpid());
        fflush(stdout);
    }else if(atoi(eloMio) == atoi(eloAvv)){
        printf("%d Pareggio\n",getpid());
        fflush(stdout);
    }else{
        printf("%d Perdo\n",getpid());
        fflush(stdout);
    }

    // Scambio il punteggio finale
    char pathFIFO[20]; // Creo il path della fifo
    if(getpid() > avversario){ 
        sprintf(pathFIFO, "/tmp/%d%d",getpid(),atoi(eloMio));
    }else{
        sprintf(pathFIFO, "/tmp/%d%d",avversario,atoi(eloAvv));
    }
    mkfifo(pathFIFO, S_IRUSR|S_IWUSR); // Creo la fifo
    int fifo;
    int punteggio;
    if(atoi(eloMio)<atoi(eloAvv)){ // Scambio il punteggio del perdente
        fifo = open(pathFIFO, O_WRONLY, 0666);
        punteggio = rand()%11;
        write(fifo, &punteggio, sizeof(punteggio));
        close(fifo);
    }else{
        fifo = open(pathFIFO, O_RDONLY, 0666);
        read(fifo, &punteggio, sizeof(punteggio));
        close(fifo);
    }
    
    // Trasmetto il segnale del perdente alla queue
    key_t queueKey = ftok(pathArbitro,n);
    int queueID = msgget(queueKey,0666);
    struct msg_buffer msgB;
    if(atoi(eloMio)<atoi(eloAvv)){ // Scambio il punteggio del perdente
        sprintf(msgB.mtext,"%d-%d-11",getpid(),punteggio);
    }else{
        sprintf(msgB.mtext,"%d-11-%d",getpid(),punteggio);
    }
    msgsnd(queueID, msgB.mtext, strlen(msgB.mtext), 0);

    // Modifica elo
    if(atoi(eloMio) > atoi(eloAvv)){
        int newElo = atoi(eloMio) + (atoi(eloAvv)/4);
        printf("%d nuovo ELO: %d\n",getpid(),newElo);
        fflush(stdout);

        int fileT = open(pathMio,O_WRONLY,0666);
        char dati[10];
        sprintf(dati,"%d\n",newElo);
        write(fileT,dati,strlen(dati));
        close(fileT);
    }else if(atoi(eloMio) < atoi(eloAvv)){
        exit(0);
    }
}

void create_player(){
    srand(time(0)^getpid()); // Faccio in modo che rand() sia randomico

    sigset_t s; // Creo la subnet Mask
    sigaddset(&s,SIGUSR1); // Aggiungo SIGUSR1 alla mask
    sigprocmask(SIG_BLOCK, &s, NULL);

    struct sigaction sig;
    sig.sa_sigaction = manage_message;
    sig.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR2, &sig, NULL);

    // Creo il file ed inserisco le informazioni necessarie
    char percorso[20];
    sprintf(percorso,"/tmp/%d.txt",getpid());
    creat(percorso,0666);
    int fileT = open(percorso, O_WRONLY);
    char dati[10];
    int ELO = ((rand()%40)+1)*100;
    sprintf(dati,"%d\n",ELO);
    write(fileT,dati,strlen(dati));
    close(fileT);

    while(pause());
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
    strcpy(pathArbitro, argv[1]);
    if(arbitro == -1){
        fprintf(stderr, "Error: il file arbitro non esiste\n");
        fflush(stdout);
        exit(50);
    }
    n = atoi(argv[2]);
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
    close(arbitro);
    while(wait(NULL) > 0);
}