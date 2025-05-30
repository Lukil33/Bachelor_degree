#include <iostream>
#include "Pila.h"
 
using namespace std;
 
static listaPila pila;
 
static bool pila_vuota () {
    return (pila == NULL);    
}
 
 
void pila_init() {
    pila = NULL;
}
 
 
bool pila_top (char &character) {
    
    bool risultatoOperazione;
    if (pila_vuota()) {
        risultatoOperazione = false;
    }
    else {
        character=pila->value;
        risultatoOperazione = true;
    }
    return risultatoOperazione;
}
 
 
bool pila_push (char character) {
 
    bool risultatoOperazione;
    listaPila nuovoNodo = new (nothrow) nodoPila;
    if (nuovoNodo==NULL) {
        risultatoOperazione = false;
    }
    else {
        nuovoNodo->value = character;
        nuovoNodo->next = pila;
        pila = nuovoNodo;
        risultatoOperazione = true;
    }
    return risultatoOperazione;
}
 
 
bool pila_pop () {
    
    bool risultatoOperazione;
    if (pila_vuota()) {
        risultatoOperazione = false;
    }
    else {
        listaPila primoNodo = pila;
        pila = pila->next;
        delete primoNodo;
        risultatoOperazione = true;
    }
    return risultatoOperazione;
}
 
void pila_deinit() {
    char tmp;
    while(pila_top(tmp)) {
        pila_pop();
    }
}
 
void pila_print() {
 
  if (!pila_vuota()) {
    listaPila nodoCorrente = pila;
    do {
      cout << nodoCorrente->value << endl;
      nodoCorrente = nodoCorrente->next;
    } while (nodoCorrente != NULL);
  }
}