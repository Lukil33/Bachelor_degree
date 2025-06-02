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
#define COLOR_RED "\x1b[31m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_RESET "\x1b[0m"

int yourlevel = -1;

void creaFigli(int, siginfo_t*, void*);
void uccidiFigli(int, siginfo_t*, void*);
void print(int);
void waitforsignal();

int main(){
    struct sigaction ign; // Creo una sigaction per ignorare i segnali
    ign.sa_handler = SIG_IGN;
    ign.sa_flags = 0;
    sigemptyset(&ign.sa_mask); // Svuoto la mask per evitare problemi successivi
    sigaction(SIGUSR1,&ign,NULL); // Ignoro il segnale SIGUSR1 per il processo master
    sigaction(SIGUSR2,&ign,NULL); // Ignoro il segnale SIGUSR2 per il processo master
    sigaction(SIGRTMAX,&ign,NULL); // Ignoro il segnale SIGRTMAX per il processo master

    int child = fork(); // Creo il processo di livello 0
    if(!child){
        waitforsignal(); // Inizializzo il processo di livello 0
    }else{
        // Inizializzo le variabili utili per la gestione dell'input
        char input[10];
        char command;
        int level,livelloMassimo = 0;

        // Come processo principale gestisco le varie tipologie di input
        do{
            sleep(1);
            printf("Next command: "); // Prendo in input il comando dall'utente
            scanf("%s",input);

            if(input[0] == 'c'){ // Caso in cui voglio creare nuovi figli
                sscanf(input,"%c%d",&command,&level); // divido l'input

                printf("Creating child at level %d\n",level);
                if(level < 1 || level > livelloMassimo+1){ // Controllo la correttezza dell'input
                    fprintf(stderr,COLOR_RED"An error occurred while creating children\n"COLOR_RESET);
                }else{
                    if(level == livelloMassimo+1){ // Gestisco il livello massimo per controllare successivamente la correttezza
                        livelloMassimo += 1;
                    }

                    union sigval payload; // Creo un payload inizializzato con il livello da creare
                    payload.sival_int = level;

                    if(sigqueue(-getpgid(0),SIGUSR1,payload) < 0){ // Invio il segnale SIGUSR1 a tutti i nodi del mio gruppo (fornisce ERRORE: No such process, non so perchè)
                        fprintf(stderr,"Errore %s\n", strerror(errno));
                    }
                }
            }else if(input[0] == 'k'){ // Caso in cui voglio eliminare figli
                sscanf(input,"%c%d",&command,&level); // Divido l'input

                if(level < 1 || level > livelloMassimo){ // Controllo la correttezza dell'input
                    fprintf(stderr,COLOR_RED"An error occurred while killing children\n"COLOR_RESET);
                }else{
                    livelloMassimo = level-1; // Gestisco il livello massimo per controllare successivamente la correttezza

                    union sigval payload; // Creo un payload inizializzato con il livello da eliminare
                    payload.sival_int = level;

                    if(sigqueue(-getpgid(0),SIGUSR2,payload) < 0){ // Invio il segnale SIGUSR2 a tutti i nodi del mio gruppo (fornisce ERRORE: No such process, non so perchè)
                        fprintf(stderr,"Errore %s\n", strerror(errno));
                    }
                }
            }else if(input[0] == 'p'){ // Caso in cui voglio eliminare figli
                printf("Stampa:\n");
                kill(-getpgid(0),SIGRTMAX); // Invio il segnale SIGRTMAX a tutti i nodi del mio gruppo
            }else if(input[0] != 'q'){ // Caso in cui l'input è errato
                fprintf(stderr,COLOR_RED "Invalid parameter\n" COLOR_RESET);
            }
        }while(input[0] != 'q'); // Caso in cui devo terminare il programma

        printf("Terminating...\n");

        union sigval payload; // Creo un payload per eliminare tutti i nodi figli
        payload.sival_int = 0;

        sigqueue(-getpgid(0),SIGUSR2,payload); // Invio il segnale SIGUSR2 a tutti i nodi del mio gruppo (fornisce ERRORE: No such process, non so perchè)
        while(wait(NULL)>0); // Aspetto che i figli muoiano e poi termino il processo
    }
}

void creaFigli(int, siginfo_t* val, void*){ // Funzione con lo scopo di creare i figli di un livello inferioire
    if(val->si_value.sival_int == yourlevel+1){ // Solo per i nodi del livello precedente rispetto a quello da creare
        int figlio = !fork();
        if(figlio){ // Se siamo il figlio inizializziamoci
            waitforsignal();
        }
    }
}

void uccidiFigli(int, siginfo_t* val, void*){ // Funzione con lo scopo di terminare i figli dei livelli inferioiri e noi stessi
    if(val->si_value.sival_int <= yourlevel){ // Se il processo ha un livello superiore o uguale a quello fornito
        while(wait(NULL)>0); // Aspetta che tutti i processi figlio siano terminati
        exit(0); // termina il processo
    }
}

void print(int){ // Funzione con lo scopo di stampare il processo con i dati importanti
    for(int i=0; i<yourlevel; i++){
        printf(" ");
    }
    printf("[ID %d - Parent: %d] depth %d\n",getpid(),getppid(),yourlevel);
}

void waitforsignal(){ // Funzione con lo scopo di inizializzare i processi
    yourlevel += 1; // Setta il tuo livello a 1 in più rispetto a quello del processo padre
    printf("I'm new child at level %d with pid = %d, ppid = %d e pid_group = %d\n",yourlevel,getpid(),getppid(),getgid());

    struct sigaction sa1; // Azione da intraprendere al ricevimento di SIGUSR1
    sigemptyset(&sa1.sa_mask);
    sa1.sa_sigaction = creaFigli;
    sa1.sa_flags     = SA_SIGINFO;
    sigaction(SIGUSR1, &sa1, NULL);

    struct sigaction sa2; // Azione da intraprendere al ricevimento di SIGUSR2
    sigemptyset(&sa2.sa_mask);
    sa2.sa_sigaction = uccidiFigli;
    sa2.sa_flags     = SA_SIGINFO;
    sigaction(SIGUSR2, &sa2, NULL);

    struct sigaction sa3; // Azione da intraprendere al ricevimento di SIGRTMAX
    sigemptyset(&sa3.sa_mask);
    sa3.sa_handler  = print;
    sa3.sa_flags = 0;
    sigaction(SIGRTMAX, &sa3, NULL);

    while(1){ // Aspetta un nuovo segnale
        pause();
    }
}