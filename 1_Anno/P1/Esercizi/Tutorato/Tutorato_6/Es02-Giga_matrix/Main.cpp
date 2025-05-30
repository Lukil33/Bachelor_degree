#include <iostream>
#include <fstream>
using namespace std;
#define DIM_COLONNE 141
#define DIM_RIGHE 140

void create_matrix(char matrix[DIM_COLONNE][DIM_RIGHE], char**);
int controlla_hastag(char matrix[DIM_COLONNE][DIM_RIGHE]);
bool controllo(char matrix[DIM_COLONNE][DIM_RIGHE], int, int, int&);
int somma_numero(char matrix[DIM_COLONNE][DIM_RIGHE], int, int);
void stampa(char matrix[DIM_COLONNE][DIM_RIGHE]);

int main(int argc, char **argv){
    if(argc != 2){
        cerr<<"Error: ./a.out <input_fle>"<<endl;
        exit(1);
    }

    char matrix[DIM_COLONNE][DIM_RIGHE];
    
    create_matrix(matrix, argv);
    cout<<"Il risultato totale e': "<<controlla_hastag(matrix)<<endl;
    //stampa(matrix);

    return 0;
}

void create_matrix(char matrix[DIM_COLONNE][DIM_RIGHE], char** argv){
    fstream input;
    input.open(argv[1], ios::in);
    if(input.fail()){
        cerr<<"Error during file opening"<<endl;
        exit(2);
    }

    char letter;
    int colonna=0, riga=0;
    while(input>>letter){
        if(riga>=DIM_RIGHE){
            colonna++;
            riga=0;
        }
        matrix[colonna][riga]=letter;
        riga++;
    }
    
    input.close();
}

int controlla_hastag(char matrix[DIM_COLONNE][DIM_RIGHE]){
    int colonna=0, riga=0, somma_tot=0;
    while(colonna<DIM_COLONNE){
        if(riga>=DIM_RIGHE){
            colonna++;
            riga=0;
        }
        if(matrix[colonna][riga]=='#'){
            if(controllo(matrix, colonna, riga, somma_tot)){
            }else{
                riga++;
            }
        }else{
            riga++;
        }
    }
    return somma_tot;
}

bool controllo(char matrix[DIM_COLONNE][DIM_RIGHE], int colonna, int riga, int & somma_tot){
    for(int i=-1; i<2; i++){
        for(int g=-1; g<2; g++){
            if((colonna+i>=0)&&(colonna+i<DIM_COLONNE-1)&&(riga+g>=0)&&(riga+g<DIM_RIGHE)){
                if(matrix[colonna+i][riga+g]>='0'&&matrix[colonna+i][riga+g]<='9'){
                    somma_tot += somma_numero(matrix, colonna+i, riga+g);
                    return 1;
                }
            }
        }
    }
    return 0;
}

int somma_numero(char matrix[DIM_COLONNE][DIM_RIGHE], int colonna, int riga){
    while(matrix[colonna][riga]>='0'&&matrix[colonna][riga]<='9'){
        riga--;
        if(riga<0){
            break;
        }
    }
    riga++;
    int number=0;
    while(matrix[colonna][riga]>='0'&&matrix[colonna][riga]<='9'){
        number*=10;
        number+=matrix[colonna][riga]-'0';
        matrix[colonna][riga]='.';
        riga++;
        if(riga>=DIM_RIGHE){
            break;
        }
    }
    cout<<"N: "<<number<<" - "<<colonna<<endl;
    return number;
}

void stampa(char matrix[DIM_COLONNE][DIM_RIGHE]){
    int colonna=0, riga=0;
    while(colonna<DIM_COLONNE-1){
        if(riga>=DIM_RIGHE){
            colonna++;
            riga=0;
            cout<<endl;
        }
        cout<<matrix[colonna][riga];
        riga++;
    }
}