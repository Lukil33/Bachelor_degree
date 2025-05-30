#include <iostream>
#include <cstdlib>
#define DIM_X 5
#define DIM_Y 5
using namespace std;

void random_value(int a[][DIM_Y]);

void passaggio(int a[][DIM_Y]);
void controlli_avanti(int a[][DIM_Y], int x, int y);

void passaggi_totali(int a[][DIM_Y]);

void matrice_essenziale(int a[][DIM_Y]);
void controlli_indietro(int a[][DIM_Y], int x, int y);

void percorsi_possibili(int a[][DIM_Y], char b[][DIM_Y]);

int main(){
    srand(time(NULL));
    int a[DIM_X][DIM_Y];
    char b[DIM_X][DIM_Y];

    random_value(a);

    passaggio(a);

    passaggi_totali(a);

    matrice_essenziale(a);

    percorsi_possibili(a, b);
    return 0;
}

void random_value(int a[][DIM_Y]){
    for(int y=0; y<DIM_Y; y++){
        cout<<"[ ";
        for(int x=0; x<DIM_X; x++){
            a[x][y]=rand()%2;
            cout<<a[x][y]<<" ";
        }
        cout<<"]"<<endl;
    }
}

void passaggio(int a[][DIM_Y]){
    for(int x=0; x<DIM_X; x++){
        for(int y=0; y<DIM_Y; y++){
            controlli_avanti(a, x, y);
        }
    }
}

void controlli_avanti(int a[][DIM_Y], int x, int y){
    if(a[x][y]>=1){
        if((x-1)>=0){
            if((y-1)<0){
                a[x][y]=a[x-1][y]+a[x-1][y+1];
            }else{
                if((y+1)>=DIM_Y){
                    a[x][y]=a[x-1][y-1]+a[x-1][y];
                }else{
                    a[x][y]=a[x-1][y-1]+a[x-1][y]+a[x-1][y+1];
                }
            }
        }
    }
}

void passaggi_totali(int a[][DIM_Y]){
    int passaggi=0;
    for(int y=0; y<DIM_Y; y++){
        passaggi+=a[DIM_X-1][y];
    }
    cout<<"Numero totale di cammini disponibili: "<<passaggi<<endl;
}

void matrice_essenziale(int a[][DIM_Y]){
    for(int x=DIM_X-1; x>=0; x--){
        for(int y=0; y<DIM_Y; y++){
            controlli_indietro(a, x, y);
        }
    }
}

void controlli_indietro(int a[][DIM_Y], int x, int y){
    if(a[x][y]==0){
        if((x-1)>=0){
            if((y-1)<0){
                if((a[x][y+1]==0)){
                    a[x-1][y]=0;
                }
            }else{
                if((y+1)>=DIM_Y){
                    if((a[x][y-1]==0)){
                        a[x-1][y]=0;
                    }
                }else{
                    if((a[x][y-1]==0)&&(a[x][y+1]==0)){
                        a[x-1][y]=0;
                    }
                }
            }
        }
    }
}

void percorsi_possibili(int a[][DIM_Y], char b[][DIM_Y]){
    for(int y=0; y<DIM_Y; y++){
        cout<<"[ ";
        for(int x=0; x<DIM_X; x++){
            if(a[x][y]==0){
                b[x][y]='-';
            }else{
                b[x][y]='*';
            }
            cout<<b[x][y]<<" ";
        }
        cout<<"]"<<endl;
    }
}