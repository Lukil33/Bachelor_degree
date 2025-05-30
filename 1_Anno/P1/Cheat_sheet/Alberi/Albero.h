#ifndef ALBERO_H
#define ALBERO_H

struct nodo {
    int value;
    nodo* left;
    nodo* right;
};
typedef nodo* albero;

albero creaAlberoDiRicercaBinaria(char* inputFile);
void inserisciNodoInAlberoDiRicercaBinaria(albero radice, nodo* nuovoNodo);
void stampaAlberoDiRicercaBinaria(albero radice);
void stampaAlbero(albero radice, int spazio=0);
void trovaPercorso(albero alberoBinario, int elementoDaCercare);
void deallocaAlbero(albero alberoBinario);

#endif