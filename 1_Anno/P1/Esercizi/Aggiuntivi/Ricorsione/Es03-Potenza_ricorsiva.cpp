#include <iostream>
using namespace std;

void potenzaricorsiva(int Pnumero, int Snumero, long somma);

int main(){
    int Pnumero, Snumero;

    cout<<"Inserire la base: ";
    cin>>Pnumero;
    cout<<"Inserire l'esponente: ";
    cin>>Snumero;

    long somma=Pnumero;
    potenzaricorsiva(Pnumero, Snumero, somma);

    return 0;
}

void potenzaricorsiva(int Pnumero,int Snumero,long somma){
    if(Snumero==1){
        cout<<"Potenza ricorsiva: "<<somma<<endl;
    }else{
        somma*=Pnumero;
        Snumero-=1;
        potenzaricorsiva(Pnumero, Snumero, somma);
    }
}