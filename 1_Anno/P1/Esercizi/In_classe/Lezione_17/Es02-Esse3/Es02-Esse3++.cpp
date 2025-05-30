#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

struct Studente{
    char nome[31];
    char cognome[31];
    int matricola;
    float media_ponderata;
};

void genera_database(int argc, char* argv[], Studente *database[]);
Studente * genera_studente(char nome[], char cognome[], int matricola, float media_ponderata);

void stampa_studente(Studente * S );

int main(int argc, char * argv[]){
    Studente ** database;
    database= new Studente*[atoi(argv[2])];

    genera_database(argc, argv, database);

    for(int i=0; i<atoi(argv[2]); i++){
        stampa_studente(database[i]);
        delete[] database[i];
    }
    delete[] database;
    return 0;
}

void genera_database(int argc, char* argv[], Studente *database[]){
    fstream file;
    file.open(argv[1], ios::in);
    if(file.fail()){
        cerr<<"Non funziona un cazzo dio caro"<<endl;
        exit(1);
    }

    char nome[31], cognome[31];
    int matricola;
    float media_ponderata;

    for(int i=0; i<atoi(argv[2]); i++){
        file>>nome>>cognome>>matricola>>media_ponderata;
        database[i]=genera_studente(nome, cognome, matricola, media_ponderata);
    }
}

Studente * genera_studente(char nome[], char cognome[], int matricola, float media_ponderata){
    Studente * puntatore;
    puntatore = new (nothrow) Studente;

    if(puntatore == NULL){
        return NULL;
    }

    puntatore->matricola=matricola;
    puntatore->media_ponderata=media_ponderata;
    strcpy(puntatore->nome, nome);
    strcpy(puntatore->cognome, cognome);

    return puntatore;
}

void stampa_studente(Studente * S ){
    if(S==NULL){
        cerr<<"Lo studente non esiste"<<endl;
    }

    cout<<"Nome: "<<S->nome<<endl;
    cout<<"Cognome: "<<S->cognome<<endl;
    cout<<"Matricola: "<<S->matricola<<endl;
    cout<<"Media: "<<S->media_ponderata<<endl<<endl;
}