#include <iostream>
using namespace std;

//Ipotesi: il secondo numero deve essere positivo

void sottrazione_iterativa(int Snumero, long risultato);
void sottrazione_ricorsiva(int Snumero, long risultato);

int main(){
    int Pnumero, Snumero;

    cout<<"Inserire il primo numero intero: ";
    cin>>Pnumero;
    cout<<"Inserire il secondo numero intero: ";
    cin>>Snumero;

    long risultato=Pnumero;
    sottrazione_iterativa(Snumero, risultato);
    sottrazione_ricorsiva(Snumero, risultato);

    return 0;
}

void sottrazione_iterativa(int Snumero, long risultato){
    while(Snumero!=0){
        risultato--;
        Snumero--;
    }
    cout<<"Sottrazione iterativa: "<<risultato<<endl;
}

void sottrazione_ricorsiva(int Snumero, long risultato){
    if(Snumero==0){
        cout<<"Sottrazione ricorsiva: "<<risultato<<endl;
    }else{
        risultato--;
        Snumero--;
        sottrazione_ricorsiva(Snumero, risultato);
    }
}