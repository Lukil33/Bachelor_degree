#include <iostream>
#include <cstring>
#include "pila.h"

using namespace std;


int main() {

    init(15);

    cout << "inserisci: " << endl;
    cout << "- 'push1' per aggiungere un valore a P1" << endl;
    cout << "- 'push2' per aggiungere un valore a P2" << endl;
    cout << "- 'top1' per stampare a video il primo elemento di P1" << endl;
    cout << "- 'top2' per stampare a video il primo elemento di P2" << endl;
    cout << "- 'pop1' per rimuovere il primo elemento di P1" << endl;
    cout << "- 'pop2' per rimuovere il primo elemento di P2" << endl;
    cout << "- 'p' per stampare a video P1 e P2" << endl;
    cout << "- 'e' per terminare il programma" << endl;

    bool esci = false;
    char input[6];

    while (!esci) {
        
        cout << "Il tuo comando: ";
        cin >> input;

        if (strcmp(input, "push1") == 0) {
            int valore;
            cout << "Inserisci il valore da inserire in P1: ";
            cin >> valore;
            bool result = pushP1(valore);
            if (!result) {
                cout << "Errore, dimensione massima raggiunta!" << endl;
            }
        }

        else if (strcmp(input, "push2") == 0) {
            int valore;
            cout << "Inserisci il valore da inserire in P2: ";
            cin >> valore;
            bool result = pushP2(valore);
            if (!result) {
                cout << "Errore, dimensione massima raggiunta!" << endl;
            }
        }

        else if (strcmp(input, "top1") == 0) {
            int primoP1;
            if (topP1(primoP1)) {
                cout << "Il primo elemento in P1 è " << primoP1 << endl;
            } else {
                cout << "P1 è vuota" <<  endl;
            }
        }

        else if (strcmp(input, "top2") == 0) {
            int primoP2;
            if (topP2(primoP2)) {
                cout << "Il primo elemento in P2 è " << primoP2 << endl;
            } else {
                cout << "P2 è vuota" <<  endl;
            }
        }

        else if (strcmp(input, "pop1") == 0) {
            int primoP1;
            if (topP1(primoP1)) {
                popP1();
                cout << "abbiamo rimosso da P1 l'elemento " << primoP1 << endl;
            } else {
                cout << "P1 è vuota" <<  endl;
            }
        }

        else if (strcmp(input, "pop2") == 0) {
            int primoP2;
            if (topP2(primoP2)) {
                popP2();
                cout << "abbiamo rimosso da P2 l'elemento " << primoP2 << endl;
            } else {
                cout << "P2 è vuota" <<  endl;
            }
        }

        /** Stampa a video */
        else if (strcmp(input, "p") == 0) {
            print();
        }

        /** Uscita del programma */
        else if (strcmp(input, "e") == 0) {
            cout << "Uscita del programma" << endl;
            esci = true;
        }

        /** Opzione non valida */
        else {
            cout << "Opzione non valida" << endl;
        }
    }

    deinit();

    return 0;
}
