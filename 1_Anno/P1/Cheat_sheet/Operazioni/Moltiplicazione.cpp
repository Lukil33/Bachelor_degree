#include <iostream>
using namespace std;

//Ipotesi: il secondo numero deve essere positivo

void moltiplicazione_iterativa(int Pnumero, int Snumero, long risultato);
void moltiplicazione_ricorsiva(int Pnumero, int Snumero, long risultato);

int main(){
    int Pnumero, Snumero;

    cout<<"Inserire il primo numero intero: ";
    cin>>Pnumero;
    cout<<"Inserire il secondo numero intero: ";
    cin>>Snumero;

    long risultato=0;
    moltiplicazione_iterativa(Pnumero, Snumero, risultato);
    moltiplicazione_ricorsiva(Pnumero, Snumero, risultato);

    return 0;
}

void moltiplicazione_iterativa(int Pnumero, int Snumero, long risultato){
    while(Snumero!=0){
        risultato+= Pnumero;
        Snumero--;
    }
    cout<<"Moltiplicazione iterativa: "<<risultato<<endl;
}

void moltiplicazione_ricorsiva(int Pnumero, int Snumero, long risultato){
    if(Snumero==0){
        cout<<"Moltiplicazione ricorsiva: "<<risultato<<endl;
    }else{
        risultato+=Pnumero;
        Snumero--;
        moltiplicazione_ricorsiva(Pnumero, Snumero, risultato);
    }
}