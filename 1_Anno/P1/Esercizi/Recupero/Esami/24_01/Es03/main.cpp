#include <iostream>
#include "lista.h"

using namespace std;

const int POS_AL_SECONDO = 2;
const int DIM_COLORI = 4;
const int MAX_BAMBINI = 10;

const char* nomi[18] = {"Marco", "Luca", "Anna", "Sabrina", "Veronica", "Simone", "Mario", "Luigi", "Antonio", "Francesca", "Giovanni", "Letizia", "Lucrezia", "Carolina", "Luca", "Annalisa", "Susanna", "Licia"};
const color colori[DIM_COLORI] = {rosso, verde, blu, giallo};

// Inserire QUI sotto la dichirazione delle funzioni coloraPartecipante e cerca.
lista cerca(lista, char*);
lista coloraPartecipante(lista, int, int);
// Inserire QUI sopra la dichirazione delle funzioni coloraPartecipante e cerca.

int main() {
    lista cerchio = NULL;
    
    unsigned int seed = time(NULL);
    // Commentare la riga sotto per non avere sempre lo stesso seed
    seed = 1703945587;
    std::cout << "Seed: " << seed << std::endl;
    srand(seed);
  

    int numero_bambini = rand() % MAX_BAMBINI + 2;
    for (int i = 0; i < numero_bambini; i++) {
        char* nome = (char*)nomi[rand() % 18];
        if (cerca(cerchio, nome) == NULL) {
            insert_in(cerchio, nome, 0);
        } else {
            i--;
        }
    }

    cout << "Ci sono " << size(cerchio) << " bambini nella lista." << endl;
    print(cerchio);

    int i = 0;
    int durata;
    bool finished = false;

    while (!empty(cerchio) && !finished) {
        cout << "-------------------------------------------------------------" << endl;
        cout << "Giro numero " << ++i << endl;
        
        cout << "La canzone durerà per " << (durata = rand() % 60 + 10) << " secondi." << endl;

        int sedia_rimossa = rand() % size(cerchio);
        cout << "Fermo il bambino alla sedia numero " << sedia_rimossa << "." << endl;

        lista eliminato = coloraPartecipante(cerchio, durata, sedia_rimossa);

        if (eliminato != NULL) {
            cout << eliminato->nome << " ha ricevuto il colore " << eliminato->colore << endl;
        } else {
            cout << "Tutti i bambini hanno un colore. Ho finito." << endl;
            finished = true;
        }
        print(cerchio);
    }

    cout << "-------------------------------------------------------------" << endl;
    cout << "Tutti i bambini hanno un colore. Ho finito." << endl;

    return 0;
}

// Inserire QUI la definizione delle funzioni coloraPartecipante e cerca.
bool strcmp(char* f, char* s){
    bool check = true;
    int i=0;
    for(; check && f[i] != '\0' && s[i] != '\0'; i++){
        if(f[i] != s[i]){
            check = false;
        }
    }
    if(check && f[i] == s[i]){
        return true;
    }else{
        return false;
    }
}

lista cerca(lista L, char* v){
    if(empty(L)){
        return NULL;
    }else{
        lista p = L;
        bool found = false;
        do{
            if(strcmp(L->nome, v)){
                p = L;
                found = true;
            }else{
                L = L->next;
            }
        }while(p != L);
        if(found){
            return L;
        }else{
            return NULL;
        }
    }
}

lista coloraPartecipante(lista L, int k, int i){
    if(L == NULL){
        return NULL;
    }
    lista bp = NULL;
    for(int j=0; j<k*POS_AL_SECONDO; j++){
        bp = L;
        L = L->next;
    }
    for(int j=0; j<i; j++){
        bp = L;
        L = L->next;
    }
    lista p = L;
    do{
        bp = L;
        L = L->next;
    }while(L->colore != -1 && p != L);
    if(L->colore != -1){
        return NULL;
    }else{
        L->colore = rosso;
        if(L->colore == bp->colore || L->colore == L->next->colore){
            L->colore = verde;
        }
        if(L->colore == bp->colore || L->colore == L->next->colore){
            L->colore = blu;
        }
        return L;
    }
}