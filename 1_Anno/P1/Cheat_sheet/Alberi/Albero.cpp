#include <iostream>
#include <fstream>
#include "Albero.h"
using namespace std;

albero creaAlberoDiRicercaBinaria(char* inputFile) {

    albero radice = NULL;
    fstream input;

    input.open(inputFile, ios::in);
    if (input.fail()) {
        cout << "Errore in lettura" << endl;
    }
    else {
        int numero;
        input >> numero;
        radice = new nodo{numero, NULL, NULL};

        while(input >> numero) {
            nodo* nuovoNodo = new nodo{numero, NULL, NULL};
            inserisciNodoInAlberoDiRicercaBinaria(radice, nuovoNodo);
        }
    }

    input.close();

    return radice;
}

void inserisciNodoInAlberoDiRicercaBinaria(albero radice, nodo* nuovoNodo) {
    if (nuovoNodo->value > radice->value) {
        if (radice->right == NULL) {
            radice->right = nuovoNodo;
        }
        else {
            inserisciNodoInAlberoDiRicercaBinaria(radice->right, nuovoNodo);
        }
    }
    else {
        if (radice->left == NULL) {
            radice->left = nuovoNodo;
        }
        else {
            inserisciNodoInAlberoDiRicercaBinaria(radice->left, nuovoNodo);
        }
    }
}

void stampaAlberoDiRicercaBinaria(albero radice) {
    if (radice != NULL) {
        stampaAlberoDiRicercaBinaria(radice->left);
        cout << radice->value << " ";
        stampaAlberoDiRicercaBinaria(radice->right);
    }
}

void stampaAlbero(albero radice, int spazio){
   if (radice != NULL) {
    spazio ++;
    
    stampaAlbero(radice->right, spazio);
 
    for (int i = 1; i < spazio; i++) {
        cout<<"\t";
    }
    cout<<radice->value<<"\n";
    
    stampaAlbero(radice->left, spazio);
   }
}

void trovaPercorso(albero radice, int elemento) {
    if (radice == NULL) {
        cout << "Elemento non trovato!" << endl;
    }
    else if (radice->value == elemento) {
        cout << "Trovato!" << endl;
    }
    else if (radice->value < elemento) {
        cout << radice->value << ", destra" << endl;
        trovaPercorso(radice->right, elemento);
    }
    else {
        cout << radice->value << ", sinistra" << endl;
        trovaPercorso(radice->left, elemento);
    }
}

void deallocaAlbero(albero radice) {
    if (radice != NULL) {
        deallocaAlbero(radice->left);
        deallocaAlbero(radice->right);
        delete radice;
    }
}