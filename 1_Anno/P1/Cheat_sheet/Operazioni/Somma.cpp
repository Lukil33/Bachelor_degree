#include <iostream>
using namespace std;

//Ipotesi: il secondo numero deve essere positivo

void somma_iterativa(int Snumero, long somma);
void somma_ricorsiva(int Snumero, long somma);

int main(){
    int Pnumero, Snumero;

    cout<<"Inserire il primo numero intero: ";
    cin>>Pnumero;
    cout<<"Inserire il secondo numero intero: ";
    cin>>Snumero;

    long somma=Pnumero;
    somma_iterativa(Snumero, somma);
    somma_ricorsiva(Snumero, somma);

    return 0;
}

void somma_iterativa(int Snumero, long somma){
    while(Snumero!=0){
        somma++;
        Snumero--;
    }
    cout<<"Somma iterativa: "<<somma<<endl;
}

void somma_ricorsiva(int Snumero, long somma){
    if(Snumero==0){
        cout<<"Somma ricorsiva: "<<somma<<endl;
    }else{
        somma+=1;
        Snumero-=1;
        somma_ricorsiva(Snumero, somma);
    }
}