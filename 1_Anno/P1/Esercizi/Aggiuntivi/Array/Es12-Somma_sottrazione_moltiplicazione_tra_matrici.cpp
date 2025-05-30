#include <iostream>
#include <cstdlib>
#define DIM 5
using namespace std;

void assegna_valori(int matrice[][DIM]);
void somma(int p_matrice[][DIM], int s_matrice[][DIM]);
void sottrazione(int p_matrice[][DIM], int s_matrice[][DIM]);
void prodotto(int p_matrice[][DIM], int s_matrice[][DIM]);
int somma_numeri(int p_matrice[][DIM], int s_matrice[][DIM], int riga, int colonna);

int main(){
    srand(time(NULL));
    int p_matrice[DIM][DIM], s_matrice[DIM][DIM];

    assegna_valori(p_matrice);
    assegna_valori(s_matrice);

    somma(p_matrice, s_matrice);
    sottrazione(p_matrice, s_matrice);
    prodotto(p_matrice, s_matrice);
    return 0;
}

void assegna_valori(int matrice[][DIM]){
    for(int colonna=0; colonna<DIM; colonna++){
        for(int riga=0; riga<DIM; riga++){
            matrice[colonna][riga]=rand()%5;
            cout<<"["<<matrice[colonna][riga]<<"] ";
        }
        cout<<endl;
    }
    cout<<endl;
}

void somma(int p_matrice[][DIM], int s_matrice[][DIM]){
    cout<<"Somma:"<<endl;
    for(int colonna=0; colonna<DIM; colonna++){
        for(int riga=0; riga<DIM; riga++){
            cout<<"["<<p_matrice[colonna][riga]+s_matrice[colonna][riga]<<"] ";
        }
        cout<<endl;
    }
    cout<<endl;
}

void sottrazione(int p_matrice[][DIM], int s_matrice[][DIM]){
    cout<<"Sottrazione:"<<endl;
    for(int colonna=0; colonna<DIM; colonna++){
        for(int riga=0; riga<DIM; riga++){
            cout<<"["<<p_matrice[colonna][riga]-s_matrice[colonna][riga]<<"] ";
        }
        cout<<endl;
    }
    cout<<endl;
}

void prodotto(int p_matrice[][DIM], int s_matrice[][DIM]){
    cout<<"Moltiplicazione:"<<endl;
    for(int colonna=0; colonna<DIM; colonna++){
        for(int riga=0; riga<DIM; riga++){
            cout<<"["<<somma_numeri(p_matrice, s_matrice, riga, colonna)<<"] ";
        }
        cout<<endl;
    }
    cout<<endl;
}

int somma_numeri(int p_matrice[][DIM], int s_matrice[][DIM], int riga, int colonna){
    int somma=0;
    for(int y=0;y<DIM;y++){
        somma+=p_matrice[colonna][y]*s_matrice[y][riga];
    }
    return somma;
}