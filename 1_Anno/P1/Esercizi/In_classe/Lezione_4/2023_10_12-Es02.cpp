#include <iostream>
using namespace std;

void riordina(int & n1, int & n2, int & n3);

int main(){
    int n1, n2, n3;

    cout<<"Inserisci il primo dei 3 numeri: ";
    cin>>n1;
    cout<<"Inserisci il secondo dei 3 numeri: ";
    cin>>n2;
    cout<<"Inserisci il terzo dei 3 numeri: ";
    cin>>n3;
    
    cout<<"n1: "<<n1<<" n2: "<<n2<<" n3: "<<n3<<endl;

    riordina(n1, n2, n3);

    cout<<"n1: "<<n1<<" n2: "<<n2<<" n3: "<<n3<<endl;
    return 0;
}

void riordina(int & n1, int & n2, int & n3){
    if(n1>n2){
        n1+=n2;
        n2=n1-n2;
        n1-=n2;
    }
    if(n2>n3){
        n2+=n3;
        n3=n2-n3;
        n2-=n3;
    }
    if(n1>n2){
        n1+=n2;
        n2=n1-n2;
        n1-=n2;
    }
}