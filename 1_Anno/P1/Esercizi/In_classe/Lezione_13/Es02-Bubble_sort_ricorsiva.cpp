#include <iostream>
#include <cstdlib>
using namespace std;
#define DIM 10

void random_number(int * a);

void bubble_sort_ricorsivo(int * a);
void bubble_sort_ausiliaria(int * a, int & contatore, int& l);

bool controllo_ordine(int * a, int v);

int main(){
    srand(time(NULL));
    int a[DIM];

    random_number(a);
    bubble_sort_ricorsivo(a);

    return 0;
}

void random_number(int * a){
    cout<<"[ ";
    for(int i=0;i<DIM;i++){
        a[i]=rand()%100;
        cout<<a[i]<<" ";
    }
    cout<<"]"<<endl;
}

void bubble_sort_ricorsivo(int * a){
    int contatore=0;
    int l=0;

    bubble_sort_ausiliaria(a, contatore, l);

    cout<<"contatore: "<<contatore<<endl<<"[ ";
    for(int j=0; j<DIM; j++){
        cout<<a[j]<<" ";
    }
    cout<<"]"<<endl;
}

void bubble_sort_ausiliaria(int * a, int & contatore, int& l){
    int v=0;
    if(controllo_ordine(a, v)){
    }else{
        cout<<"Pipo"<<endl;
        if(l<=0){
            l=DIM-1;
        }
        if(a[l]<a[l-1]){
            contatore++;
            a[l]+=a[l-1];
            a[l-1]=a[l]-a[l-1];
            a[l]-=a[l-1];
        }
        l--;
        bubble_sort_ausiliaria(a, contatore, l);
    }
}

bool controllo_ordine(int * a, int v){
    if(a[v]>a[v+1]){
        cout<<a[v]<<" - "<<a[v+1]<<endl;
        return 0;
    }else if((v+2)>=DIM){
        cout<<"Evviva"<<endl;
        return 1;
    }else{
        controllo_ordine(a, v+1);
    }
}