#include <iostream>
#include <fstream>
#include "Albero.h"
using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Usage: ./a.out <nome_file>" << endl;
        exit(1);
    }

    albero radice = creaAlberoDiRicercaBinaria(argv[1]);

    if (radice == NULL) {
        exit(2);
    } else {

        stampaAlbero(radice);

        int elementoDaCercare;
        cout << "Inserisci l'elemento da cercare: ";
        cin >> elementoDaCercare;

        trovaPercorso(radice, elementoDaCercare);
        deallocaAlbero(radice); 
    }

    return 0;
}