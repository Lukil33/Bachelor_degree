#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

struct Studente{
    char nome[31];
    char cognome[31];
    int matricola;
    float media;
};

void crea_database(int DIM, char * argv[], Studente ** database);
Studente * crea_persona(char nome[], char cognome[], int matricola, float media);

int cerca_matricola(Studente ** database, int matricola, int DIM);

int cerca_nome_e_cognome(Studente ** database, char * nome, char * cognome, int DIM);

int studente_top_media(Studente ** database, int DIM);

void stampa_studenti(Studente * cristiano);

int main(int argc, char * argv[]){

    if(argc!=3){
        cerr<<"Hai inserito un numero incorretto di elementi"<<endl;
        return -1;
    }

    int DIM=atoi(argv[2]);

    Studente ** database;
    database=new Studente*[DIM];

    crea_database(DIM, argv, database);

    int matricola;
    cout<<"Inserisci la matricola dello studente cercato: ";
    cin>>matricola;
    int num_database=cerca_matricola(database, matricola, DIM);
    if(num_database!=DIM+1){
        stampa_studenti(database[num_database]);
    }

    char nome[31], cognome[31];
    cout<<"Inserisci il nome dello studente cercato: ";
    cin>>nome;
    cout<<"Inserisci il cognome dello studente cercato: ";
    cin>>cognome;
    num_database=cerca_nome_e_cognome(database, nome, cognome, DIM);
    if(num_database!=DIM+1){
        stampa_studenti(database[num_database]);
    }

    num_database=studente_top_media(database, DIM);
    stampa_studenti(database[num_database]);

    for(int i=0; i<DIM; i++){
        delete[] database[i];
    }
    delete[] database;
    return 0;
}

void crea_database(int DIM, char * argv[], Studente ** database){
    fstream file;
    file.open(argv[1],ios::in);
    if(file.fail()){
        cerr<<"Non funziona un cazzo dio caro"<<endl;
        exit(1);
    }

    char nome[31], cognome[31];
    int matricola;
    float media;

    for(int i=0; i<DIM; i++){
        file>>nome>>cognome>>matricola>>media;
        database[i] = crea_persona(nome, cognome, matricola, media);
    }
}

Studente * crea_persona(char nome[], char cognome[], int matricola, float media){
    Studente * puntatore;
    puntatore=new Studente;

    strcpy(puntatore->nome, nome);
    strcpy(puntatore->cognome, cognome);
    puntatore->matricola=matricola;
    puntatore->media=media;

    return puntatore;
}

void stampa_studenti(Studente * cristiano){
    cout<<"Nome: "<<cristiano->nome<<endl;
    cout<<"Cognome: "<<cristiano->cognome<<endl;
    cout<<"Matricola: "<<cristiano->matricola<<endl;
    cout<<"Media: "<<cristiano->media<<endl<<endl;
}

int cerca_matricola(Studente ** database, int matricola, int DIM){
    for(int i=0; i<DIM; i++){
        if(database[i]->matricola==matricola){
            return i;
        }
    }
    cerr<<"Non esistono studenti con tale matricola"<<endl<<endl;
    return DIM+1;
}

int cerca_nome_e_cognome(Studente ** database, char * nome, char * cognome, int DIM){
    for(int i=0; i<DIM; i++){
        if((strcmp(database[i]->nome, nome)==0)&&(strcmp(database[i]->cognome, cognome)==0)){
            return i;
        }
    }
    cerr<<"Non esistono studenti con tale nome e cognome"<<endl;
    for(int g=0; g<DIM; g++){
        if((strcmp(database[g]->cognome, cognome)==0)){
            cout<<"Forse intendevi:"<<endl;
            return g;
        }
    }
    for(int i=0; i<DIM; i++){
        if((strcmp(database[i]->nome, nome)==0)){
            cout<<"Forse intendevi:"<<endl;
            return i;
        }
    }
    return DIM+1;
}

int studente_top_media(Studente ** database, int DIM){
    float top_media=database[0]->media;
    int nerd=0;
    for(int i=0; i<DIM; i++){
        if(database[i]->media>top_media){
            top_media=database[i]->media;
            nerd=i;
        }
    }
    cout<<"Lo studente piu' secchione e':"<<endl;
    return nerd;
}