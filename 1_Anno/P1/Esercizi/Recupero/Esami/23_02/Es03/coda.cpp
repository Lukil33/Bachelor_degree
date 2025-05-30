#include <iostream>
#include "coda.h"

using namespace std;

static coda Q;

static bool vuota() {
  return (Q.head == NULL);
}


void init() {
  Q.head = NULL;
}


bool enqueue(int n) {
  
    bool risultatoOperazione;
    listaCoda nuovoNodo = new (nothrow) nodoCoda;
    if (nuovoNodo==NULL) {
        risultatoOperazione = false;
    }
    else {
        nuovoNodo->value=n;
        nuovoNodo->next=NULL;
        if (vuota()) {
            Q.head=nuovoNodo;
        }
        else { 
            Q.tail->next=nuovoNodo;
        }
        Q.tail=nuovoNodo;
        risultatoOperazione = true;
    }
    return risultatoOperazione;
}


bool first(int &n) { 
    bool risultatoOperazione;
    if (vuota()) {
        risultatoOperazione = false;
    }
    else {
        n = Q.head->value;
        risultatoOperazione = true;
    }
    return risultatoOperazione;
}


bool dequeue() { 
    bool risultatoOperazione;
    if (vuota()) {
        risultatoOperazione = false;
    }
    else {
        listaCoda primoNodo;
        primoNodo = Q.head;
        Q.head = Q.head->next;
        delete primoNodo; 
        risultatoOperazione = true;
    }
    return risultatoOperazione;
}

void deinit() {
    int tmp;
	while(first(tmp)) {
		dequeue();
	}
}

void print() {

  if (!vuota()) {
    listaCoda nodoCorrente=Q.head;
    do {
      cout << nodoCorrente->value << endl;
      nodoCorrente = nodoCorrente->next;
    } while (nodoCorrente != NULL);
  }
}