#include <iostream>
#include <cstdlib>
using namespace std;

int valori();
void somma(int matrice[][3], int vettore[]);

int main(){
    srand(time(NULL));
    int matrice[4][3], vettore[4];

    for(int i=0; i<3; i++){
        for(int g=0; g<4; g++){
            matrice[g][i]=valori();
            cout<<"["<<matrice[g][i]<<"] ";
        }
        cout<<endl;
    }
    cout<<endl;

    for(int l=0; l<4; l++){
        vettore[l]=valori();
        cout<<"["<<vettore[l]<<"] ";
    }
    cout<<endl<<endl;

    somma(matrice, vettore);
    return 0;
}

int valori(){
    int numero= rand()%11;
    return numero;
}

void somma(int matrice[][3], int vettore[]){
    for(int h=0; h<3; h++){
        for(int t=0; t<4; t++){
            matrice[t][h]+=vettore[t];
            cout<<"["<<matrice[t][h]<<"] ";
        }
        cout<<endl;
    }
    cout<<endl;
}