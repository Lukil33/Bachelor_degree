#include <iostream>
using namespace std;
#define DIM 6

void remove_rec(float a[], int* n, int i);

int main(){
    float a[DIM]={0, 1, 2, 3, 4, 5};
    int n, i=DIM-1;

    cout<<"Inserire la posizione dell'elemento che si vuole rimuovere: ";
    cin>>n;
    while(n<0||n>5){
        cout<<"Hai sbagliato, reinserire la posizione dell'elemento: ";
        cin>>n;
    }

    for(int f=0; f<DIM;f++){
        cout<<a[f]<<" ";
    }
    cout<<endl;
    remove_rec(a, &n, i);
    for(int g=0; g<DIM;g++){
        cout<<a[g]<<" ";
    }
    cout<<endl;
    return 0;
}

void remove_rec(float a[], int* n, int i){
    if((*n)==i||i<0){
    }else{
        remove_rec(a, n, i-1);
        a[i-1]=a[i];
    }
}