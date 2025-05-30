#include <iostream>
using namespace std;

int main(){
    int a, b;

    cout<<"Inserisci il numero A: ";
    cin>>a;
    cout<<"Inserisci il numero B: ";
    cin>>b;

    int risultato = a - b;
    bool P, Q=false;
    P=((risultato<0)||(risultato>0));

    cout<<"1=VERO 0=FALSO : "<<(! P||Q)<<endl;
    return 0;
}