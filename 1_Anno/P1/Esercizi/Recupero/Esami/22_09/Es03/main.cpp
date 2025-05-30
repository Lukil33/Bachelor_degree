#include <iostream>
#include <string.h> // definisce la funzione "int strlen (const char * array);"
#include <math.h>   // definisce la funzione "int pow (base, esponente);"
#include "pila.h"   // fare riferimento al file "pila.h" per le funzioni esposte

using namespace std;

int decodificaNumero(char numeroCodificato []);
int countD(char codifica[], int n);
int smallestnum(int n);

int main() { 
    int dimensioneMassima = 9;
    char numeroCodificato [dimensioneMassima];
    cout << "Inserisci l'array: ";
    cin >> numeroCodificato;
    int decodifica = decodificaNumero(numeroCodificato);
    cout << "Decodifica: " << decodifica << endl;
}

int decodificaNumero(char numeroCodificato []) {
    // Scrivere il codice qui
    init();
    int res = 0;
    int lunghezza = int(strlen(numeroCodificato));

    for(int i=9; i>=1; i--){
        push(i);
    }

    for(int j=0; j<=lunghezza; j++){
        if(numeroCodificato[j] == 'I'){
            int n;
            top(n);
            res += n * pow(10, lunghezza - j);
            pop();
        }else{
            res += countD(numeroCodificato, j) * pow(10, lunghezza - j);
        }
    }

    deinit();
    // Potete assumere che l'array rispetti le assunzioni
    // dell'esercizio (non serve fare controlli sull'input)
    return res;
}

int countD(char codifica[], int n){
    int i = n;
    while(codifica[i] == 'D'){
        i = i+1;
    }
    n = i-n;
    return smallestnum(n);
}

int smallestnum(int n){
    int t;
    if(n > 0){
        top(t);
        pop();
        int res = smallestnum(n-1);
        push(t);
        return res;
    }else{
        top(t);
        pop();
        return t;
    }
}