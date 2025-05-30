#include <iostream>
#include <cstring>
using namespace std;

struct Studente{
    char nome[31];
    char cognome[31];
    int matricola;
    float media_ponderata;
};

Studente * genera_studente(char nome[], char cognome[], int matricola, float media_ponderata);
void stampa_studente(Studente * S );

int main(){
    char nome[31], cognome[31];
    int matricola;
    float media_ponderata;
    Studente * S ;

    cin>>nome>>cognome>>matricola>>media_ponderata;

    S=genera_studente(nome, cognome, matricola, media_ponderata);
    stampa_studente(S);
    delete[] S;
    return 0;
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
    cout<<"Media: "<<S->media_ponderata<<endl;
}