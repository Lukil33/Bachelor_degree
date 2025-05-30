#include <iostream>
using namespace std;

int main(){
    float primo_numero, secondo_numero, terzo_numero;

    cout<<"Inserire il valore del primo numero: ";
    cin>>primo_numero;
    cout<<"Inserire il valore del secondo numero: ";
    cin>>secondo_numero;
    cout<<"Inserire il valore del terzo numero: ";
    cin>>terzo_numero;

    if(primo_numero>=secondo_numero&&primo_numero>=terzo_numero){
        cout<<"Il valore maggiore e': "<<primo_numero<<endl;
    }else if(secondo_numero>=terzo_numero){
        cout<<"Il valore maggiore e': "<<secondo_numero<<endl;
    }else{
        cout<<"Il valore maggiore e': "<<terzo_numero<<endl;
    }
    return 0;
}