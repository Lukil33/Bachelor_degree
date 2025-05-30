#include <iostream>
#include <cstdlib>
#define DIM 5
using namespace std;

void assegna_valori(int matrice[][DIM]);

void controllo_attorno(int matrice[][DIM]);
bool caso_base(int matrice[][DIM], int colonna, int riga, int y, int y_max, int x, int x_max);

int main(){
    srand(time(NULL));
    int matrice[DIM][DIM];

    assegna_valori(matrice);

    controllo_attorno(matrice);
    return 0;
}

void assegna_valori(int matrice[][DIM]){
    for(int colonna=0; colonna<DIM; colonna++){
        for(int riga=0; riga<DIM; riga++){
            matrice[colonna][riga]=rand()%2;
            cout<<"["<<matrice[colonna][riga]<<"] ";
        }
        cout<<endl;
    }
    cout<<endl;
}

void controllo_attorno(int matrice[][DIM]){
    int numero_isole=0;
    for(int colonna=0; colonna<DIM; colonna++){
        for(int riga=0; riga<DIM; riga++){
            bool isola=true;
            if(matrice[colonna][riga]==1){
                if(colonna<=0){
                    if(riga<=0){
                        int y=0, y_max=2, x=0, x_max=2;
                        isola=caso_base(matrice, colonna, riga, y, y_max, x, x_max);
                    }else if(riga>=(DIM-1)){
                        int y=0, y_max=2, x=-1, x_max=1;
                        isola=caso_base(matrice, colonna, riga, y, y_max, x, x_max);
                    }else{
                        int y=0, y_max=2, x=-1, x_max=2;
                        isola=caso_base(matrice, colonna, riga, y, y_max, x, x_max);
                    }
                }else if(colonna>=(DIM-1)){
                    if(riga<=0){
                        int y=-1, y_max=1, x=0, x_max=2;
                        isola=caso_base(matrice, colonna, riga, y, y_max, x, x_max);
                    }else if(riga>=(DIM-1)){
                        int y=-1, y_max=1, x=-1, x_max=1;
                        isola=caso_base(matrice, colonna, riga, y, y_max, x, x_max);
                    }else{
                        int y=-1, y_max=1, x=-1, x_max=2;
                        isola=caso_base(matrice, colonna, riga, y, y_max, x, x_max);
                    }
                }else{
                    if(riga<=0){
                        int y=-1, y_max=2, x=0, x_max=2;
                        isola=caso_base(matrice, colonna, riga, y, y_max, x, x_max);
                    }else if(riga>=(DIM-1)){
                        int y=-1, y_max=2, x=-1, x_max=1;
                        isola=caso_base(matrice, colonna, riga, y, y_max, x, x_max);
                    }else{
                        int y=-1, y_max=2, x=-1, x_max=2;
                        isola=caso_base(matrice, colonna, riga, y, y_max, x, x_max);
                    }
                }
                if(isola==true){
                    numero_isole++;
                }
            }
        }
    }
    cout<<"Ci sono "<<numero_isole<<" isole"<<endl;
}

bool caso_base(int matrice[][DIM], int colonna, int riga, int y, int y_max, int x, int x_max){
    bool isola=true;
    for(int i=y; i<y_max; i++){
        for(int h=x; h<x_max; h++){
            if((matrice[colonna+i][riga+h]==1)&&((i!=0)||(h!=0))){
                isola=false;
            }
        }
    }
    return isola;
}