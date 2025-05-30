#include <iostream>
#include "pila.h"
using namespace std;


/**
 * Ricordare che il file "pila.h" contiene la definizione della struct "cella" (qui sotto riportata)
 * 
 * struct cella {
 *   int indiceRiga;
 *   int indiceColonna;
 * };
*/

void risolviLabirinto(int labirinto[][5], int, int);
bool trova_percorso(int labirinto[][5], int matrix[][5], int position[2], int, int);
bool controlla_labirinto(int labirinto[][5], int matrix[][5], int position[2]);
void casella_precedente(int matrix[][5], int position[2]);
bool controlla_casella(int position[2], int, int);

int main(int argc, char* argv[]) {
    if(argc != 3){
        cerr<<"Errore: ./a.out <y> <x>"<<endl;
        exit(1);
    }

    int colonna=atoi(argv[1]);
    int riga=atoi(argv[2]);
    // Se modificate la funzione "main", ricordarsi poi di ripristinare il codice originale  

    // E' possibile modificare la matrice per effettuare dei test   
    int labirinto[5][5] = {
        { 1, 1, 0, 1, 1 },
        { 0, 0, 0, 0, 1 },
        { 1, 1, 1, 1, 1 },
        { 1, 0, 0, 0, 0 },
        { 1, 1, 1, 1, 1 }
    };
    
    // E' possibile modificare la cella di arrivo per effettuare dei test (la cella di partenza invece è sempre [0,0])
    cout<<"Percorso: ";
    risolviLabirinto(labirinto, colonna, riga);
   
    return 0;
}

void risolviLabirinto(int labirinto[][5], int colonna, int riga){
    int matrix[5][5];
    int position[2]={0, 0};
    for(int i=0; i<5; i++){
        for(int g=0; g<5; g++){
            matrix[g][i]=0;
        }
    }
    matrix[0][0]= 2-labirinto[0][0];
    init();
    if(trova_percorso(labirinto, matrix, position, colonna, riga)){
        cella casella;
        while(top(casella)){
            cout<<"["<<casella.indiceColonna<<", "<<casella.indiceRiga <<"] ";
            pop();
        }
    }else{
        cout<<"percorso non trovato";
    }
    cout<<endl;
    deinit();
}

bool trova_percorso(int labirinto[][5], int matrix[][5], int position[2], int colonna, int riga){
    cella casella;
    casella.indiceRiga=position[1];
    casella.indiceColonna=position[0];
    push(casella);
    while(matrix[0][0]!=2){
        if(controlla_labirinto(labirinto, matrix, position)){
            casella.indiceRiga=position[1];
            casella.indiceColonna=position[0];
            push(casella);
            if(controlla_casella(position, colonna, riga)){
                return 1;
            }
        }else{
            casella_precedente(matrix, position);
        }
    }
    return 0;
}

bool controlla_labirinto(int labirinto[][5], int matrix[][5], int position[2]){
    for(int i=-1; i<2; i++){
        if((position[0]+i)<0||(position[0]+i)>=5){
        }else{
            if((labirinto[position[0]+i][position[1]]==1)&&(matrix[position[0]+i][position[1]]==0)){
                position[0]+=i;
                matrix[position[0]][position[1]]=1;
                return 1;
            }
        }
    }
    for(int g=-1; g<2; g++){
        if((position[1]+g)<0||(position[1]+g)>=5){
        }else{
            if((labirinto[position[0]][position[1]+g]==1)&&(matrix[position[0]][position[1]+g]==0)){
                position[1]+=g;
                matrix[position[0]][position[1]]=1;
                return 1;
            }
        }
    }
    return 0;
}

void casella_precedente(int matrix[][5], int position[2]){
    matrix[position[0]][position[1]]=2;
    pop();
    if((position[0]==0)&&(position[1]==0)){
        return;
    }else{
        for(int i=-1; i<2; i++){
            if((position[0]+i)<0||(position[0]+i)>=5){
            }else{
                if((matrix[position[0]+i][position[1]]==1)){
                    position[0]+=i;
                    return;
                }
            }
        }
        for(int g=-1; g<2; g++){
            if((position[1]+g)<0||(position[1]+g)>=5){
            }else{
                if(matrix[position[0]][position[1]+g]==1){
                    position[1]+=g;
                    return;
                }
            }
        }
    }
}

bool controlla_casella(int position[2], int colonna, int riga){
    if((position[0]==colonna)&&(position[1]==riga)){
        return 1;
    }
    else{
        return 0;
    }
}