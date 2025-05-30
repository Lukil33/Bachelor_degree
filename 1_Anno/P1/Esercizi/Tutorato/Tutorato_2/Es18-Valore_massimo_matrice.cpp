#include <iostream>
#include <cstdlib>
using namespace std;

int valori_matrice();
void valore_massimo(int matrice[][5]);

int main(){
    srand(time(NULL));
    int matrice [5] [5];

    for(int i=0; i<5; i++){
        for(int g=0; g<5; g++){
            matrice[g][i]=valori_matrice();
            cout<<"["<<matrice[g][i]<<"] ";
        }
        cout<<endl;
    }
    
    valore_massimo(matrice);

    return 0;
}

int valori_matrice(){
    int numero= rand()%101;
    return numero;
}

void valore_massimo(int matrice[][5]){
    int max=matrice[0][0], x=0, y=0;
    for(int l=0;l<5;l++){
        for(int d=0;d<5;d++){
            if(matrice[d][l]>max){
                max=matrice[d][l];
                x=d;
                y=l;
            }
        }
    }
    cout<<"Valore massimo in ["<<x<<", "<<y<<"]"<<endl;
}