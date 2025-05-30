#include <iostream>
using namespace std;

int main(){
    int numero, somma=0;

    cout<<"Inserire un numero intero: ";
    cin>>numero;

    while((numero/10)>=1){
        somma+=(numero%10);
        numero-=(numero%10);
        numero/=10;
        cout<<somma<<endl;
    }
    somma+=numero;
    cout<<somma<<endl;
    return 0;
}