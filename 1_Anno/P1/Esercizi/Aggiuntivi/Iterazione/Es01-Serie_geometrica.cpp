#include <iostream>
using namespace std;

int main(){
    double numero, somma=0;

    cout<<"Inserire un numero intero: ";
    cin>>numero;

    for(int i=1;i<=numero;i++){
        double num_elevato=1;
        for(int g=1;g<i;g++){
            num_elevato*=2;
        }
        somma+=1/num_elevato;
        cout<<somma<<endl;
    }
    return 0;
}