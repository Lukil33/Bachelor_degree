#include <iostream>
using namespace std;

const int DIM=10;

// Inserire qui le DICHIARAZIONI delle funzioni
int somma_prodotto_incrociato(int* primo,int* secondo, int DIM);
int somma_prodotto_incrociato_ausiliario(int* primo,int* secondo, int contatore, int somma);

int main() {
    int primo[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int secondo[10] = {1, 1, 2, 3, 5, 8, 13, 21, 34, 55};
    cout << "La somma dei prodotti incrociati dei due array e’ " << somma_prodotto_incrociato(primo, secondo, DIM) << endl;
    return 0;
}

// Inserire qui le DEFINIZIONI delle funzioni
int somma_prodotto_incrociato(int* primo,int* secondo, int DIM){
    int somma=0,contatore=DIM-1;
    somma=somma_prodotto_incrociato_ausiliario( primo, secondo, contatore, somma);
    return somma;
}

int somma_prodotto_incrociato_ausiliario(int* primo,int* secondo, int contatore, int somma){
    if(contatore<0){
        
    }else{
        somma+=primo[contatore]*secondo[DIM-(contatore+1)];
        contatore--;
        somma=somma_prodotto_incrociato_ausiliario( primo, secondo, contatore, somma);
    }
    return somma;
}