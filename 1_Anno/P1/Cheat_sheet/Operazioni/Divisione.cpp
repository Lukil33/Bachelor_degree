#include <iostream>
using namespace std;

//Ipotesi: entrambi i numeri devono essere positivi

void divisione_iterativa(int Pnumero, int Snumero, long risultato);
void divisione_ricorsiva(int Pnumero, int Snumero, long risultato);

int main(){
    int Pnumero, Snumero;

    cout<<"Inserire il dividendo: ";
    cin>>Pnumero;
    cout<<"Inserire il divisore: ";
    cin>>Snumero;

    long risultato=0;
    divisione_iterativa(Pnumero, Snumero, risultato);
    divisione_ricorsiva(Pnumero, Snumero, risultato);

    return 0;
}

void divisione_iterativa(int Pnumero, int Snumero, long risultato){
    while(Snumero<=Pnumero){
        Pnumero-=Snumero;
        risultato++;
    }
    cout<<"Divisione iterativa: "<<risultato<<", Resto: "<<Pnumero<<endl;
}

void divisione_ricorsiva(int Pnumero, int Snumero, long risultato){
    if(Snumero>Pnumero){
        cout<<"Divisione ricorsiva: "<<risultato<<", Resto: "<<Pnumero<<endl;
    }else{
        Pnumero-=Snumero;
        risultato++;
        divisione_ricorsiva(Pnumero, Snumero, risultato);
    }
}