#include <iostream>
#include <cstdlib>
using namespace std;
#define DIM 10

void random_number(int* array);

void bubble_sort(int * array);
void bubble_sort_ausiliaria(int * array);

int main(){
    srand(time(NULL));
    int array[DIM];

    random_number(array);
    cout<<endl;
    bubble_sort(array);
    return 0;
}

void random_number(int* array){
    for(int i=0; i<DIM; i++){
        array[i]=rand()%10;
        cout<<array[i]<<" ";
    }
}

void bubble_sort(int * array){
    for(int d=0; d<DIM; d++){
        bubble_sort_ausiliaria(array);
    }
    for(int j=0; j<DIM; j++){
        cout<<array[j]<<" ";
    }
    cout<<endl;
}

void bubble_sort_ausiliaria(int * array){
    for(int l=0; l<DIM-1; l++){
        if(array[l]==0){
            array[l]+=array[l+1];
            array[l+1]=array[l]-array[l+1];
            array[l]-=array[l+1];
        }
    }
}