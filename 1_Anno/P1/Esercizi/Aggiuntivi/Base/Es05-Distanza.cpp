#include <iostream>
using namespace std;

int main(){
    float distanza_miglia;

    cout<<"Inserire il valore della distanza: ";
    cin>>distanza_miglia;

    float distanza_chilometri=distanza_miglia/0.62137;
    cout<<"La distanza in miglia vale: "<<distanza_miglia<<endl;
    cout<<"La distanza in chilometri vale: "<<distanza_chilometri<<endl;
    return 0;
}