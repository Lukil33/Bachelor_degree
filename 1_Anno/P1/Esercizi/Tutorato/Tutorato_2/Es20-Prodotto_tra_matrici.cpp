#include <iostream>
#include <cstdlib>
using namespace std;

void assegna_valore(int matrice[][4]);
int valori();
void prodotto_tra_matrici(int prima_matrice[][4], int seconda_matrice[][4]);
int somma_numeri(int prima_matrice[][4], int seconda_matrice[][4], int riga, int colonna);

int main(){
    srand(time(NULL));
    int prima_matrice[4][4], seconda_matrice[4][4];

    assegna_valore(prima_matrice);
    assegna_valore(seconda_matrice);

    prodotto_tra_matrici(prima_matrice, seconda_matrice);
    return 0;
}

void assegna_valore(int matrice[][4]){
    for(int i=0; i<4; i++){
        for(int g=0; g<4; g++){
            matrice[g][i]=valori();
            cout<<"["<<matrice[g][i]<<"] ";
        }
        cout<<endl;
    }
    cout<<endl;
}

int valori(){
    int numero= rand()%11;
    return numero;
}

void prodotto_tra_matrici(int prima_matrice[][4], int seconda_matrice[][4]){
    for(int t=0;t<4;t++){
        for(int h=0;h<4;h++){
            cout<<"["<<somma_numeri(prima_matrice, seconda_matrice, t, h)<<"] ";
        }
        cout<<endl;
    }
    cout<<endl;
}

int somma_numeri(int prima_matrice[][4], int seconda_matrice[][4], int riga, int colonna){
    int somma=0;
    for(int y=0;y<4;y++){
        somma+=prima_matrice[y][riga]*seconda_matrice[colonna][y];
    }
    return somma;
}