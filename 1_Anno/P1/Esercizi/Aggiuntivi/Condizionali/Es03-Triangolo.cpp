#include <iostream>
using namespace std;

int main(){
    float lato_1, lato_2, lato_3;

    cout<<"Inserire il valore del primo lato: ";
    cin>>lato_1;
    cout<<"Inserire il valore del secondo lato: ";
    cin>>lato_2;
    cout<<"Inserire il valore del terzo lato: ";
    cin>>lato_3;
    
    if(lato_1==lato_2||lato_1==lato_3){
        if(lato_2==lato_3){
            cout<<"Il triangolo e' equilatero"<<endl;
        }else{
            cout<<"Il triangolo e' isoscele"<<endl;
        }
    }else if(lato_2==lato_3){
        cout<<"Il triangolo e' isoscele"<<endl;
    }else {
        cout<<"Il triangolo e' scaleno"<<endl;
    }
    return 0;
}