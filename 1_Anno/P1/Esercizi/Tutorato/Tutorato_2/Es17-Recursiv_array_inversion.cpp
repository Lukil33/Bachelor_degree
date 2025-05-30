#include <iostream>
using namespace std;

void procedura(char* matrice, int i);

int main(){
    
    char matrice[4] [4];

    cin>>matrice;

    int i=0;
    procedura(matrice, i);
    cout<<endl;
    return 0;
}

void procedura(char* matrice, int i){
    if(matrice[i]=='\0'){
    }else{
        procedura(matrice, i+1);
        cout<<matrice[i]<<" ";
    }
}