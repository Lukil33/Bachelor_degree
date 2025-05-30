#include <iostream>
#define DIM 9
using namespace std;

void rotate(int* a, int k);

int main(){
    int a[DIM]={11, 22, 33, 44, 55, 66, 77, 88, 99};
    int k;

    cout<<"Inserire la rotazione: ";
    cin>>k;

    rotate(a, k);
    return 0;
}

void rotate(int* a, int k){
    int b[DIM];

    if(k<0){
        k=DIM+k;
    }
    for(int i=0; i<DIM;i++){
        int l=i+k;
        if(i+k>=DIM){
            l=(i+k)-DIM;
        }
        b[l]=a[i];
    }
    for(int g=0; g<DIM ;g++){
        a[g]=b[g];
        cout<<a[g]<<" ";
    }
    cout<<endl;
}