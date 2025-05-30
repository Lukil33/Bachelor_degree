#include <iostream>
#include <cstdlib>
using namespace std;
#define DIM 8

int random_value();
void rotate(int* a, int k);
void print(int*);

int main(){
    srand(time(NULL));
    int a[DIM];
    int k;

    for(int i=0; i<DIM; i++){
        a[i]=random_value();
    }

    print(a);

    cout<<"Inserire la rotazione: ";
    cin>>k;
    
    rotate(a, k);
    return 0;
}

int random_value(){
    int number=rand()%100;
    return number;
}

void rotate(int* a, int k){
    int b[DIM];
    if(k<0){
        k=8+k;
    }
    cout<<"k: "<<k<<endl;

    for(int i=DIM; i>=0;i--){
        int l=i+k;
        if(l>=DIM){
            l-=DIM;
        }
        b[i]=a[l];
    }

    print(b);
}

void print(int* a){
    for(int i=0; i<DIM; i++){
        cout<<a[i]<<" ";
    }
    cout<<endl;
}