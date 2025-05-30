#include <iostream>
#include "pila.h"

using namespace std;

int* collidiAsteroidi(int*, int, int&);

int main() {
    
    // Potete modificare l'array di asteroidi (e la sua
    // dimensione) per testare la vostra soluzione
    int asteroidi [] = {};
    int numeroAsteroidi = 0;


    int numeroAsteroidiRimasti;
    int * asteroidiRimasti = collidiAsteroidi(asteroidi, numeroAsteroidi, numeroAsteroidiRimasti);

    // La stampa dell'array dinamico degli
    // asteroidi rimasti avviene nel main
    for (int i = 0; i < numeroAsteroidiRimasti ; i++) {
        cout << asteroidiRimasti[i] << " ";
    }
    cout << endl;

    // La deallocazione dell'array dinamico 
    // degli asteroidi rimasti avviene nel main
    delete[] asteroidiRimasti;
}


// Implementare la funzione sottostante come da consegna:
// - ritornare un'array di interi allocato dinamicamente che 
//   contenga lo stato degli asteroidi dopo tutte le collisioni
// - assegnare a 'numeroAsteroidiRimasti' il numero di elementi 
//   nell'array ritornato
int* collidiAsteroidi(int* asteroidi, int numasteroidi, int& numres){
    init();
    numres = 0;

    for(int i = 0; i<numasteroidi; i++){
        int j = 0;
        if(vuota() || top(j)){
            if(asteroidi[i] >= 0){
                push(asteroidi[i]);
                numres++;
            }else{
                if(j <= 0){
                    push(asteroidi[i]);
                    numres++;
                }else{
                    if(j < -asteroidi[i]){
                        pop();
                        numres--;
                        i-=1;
                    }else if(j == -asteroidi[i]){
                        pop();
                        numres--;
                    }
                }
            }
        }
    }
    
    int* res = new int[numres];
    for(int i = 0; i<numres; i++){
        int k;
        top(k);
        pop();
        res[numres-1-i] = k;
    }

    return res;
}