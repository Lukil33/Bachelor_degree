#include <iostream>
#include <cstdlib>
using namespace std;
#define DIM 10

void random_number(int array[], int cont);
void recursive_array_invertion(int array[], int cont);
void array_invertion(int array[], int cont);

int main(){
    srand(time(NULL));
    int array[DIM], cont=0;

    random_number(array, cont);
    cout<<endl;
    recursive_array_invertion(array, cont);
    cout<<endl;
    array_invertion(array, cont);
    cout<<endl;
    return 0;
}

void random_number(int array[DIM], int cont){
    if(cont>=DIM){
    }else{
        array[cont]=rand()%11;
        cout<<array[cont]<<" ";
        random_number(array, cont+1);
    }
}

void recursive_array_invertion(int array[], int cont){
    int supporto=0;
    if(cont>=DIM){
    }else{
        if(((cont+1)*2)<=DIM){
            supporto=array[cont];
            array[cont]=array[DIM-1-cont];
            array[DIM-1-cont]=supporto;
        }
        cout<<array[cont]<<" ";
        recursive_array_invertion(array, cont+1);
    }
}

void array_invertion(int array[], int cont){
    int supporto=0;
    while(cont<DIM){
        if(((cont+1)*2)<=DIM){
            supporto=array[cont];
            array[cont]=array[DIM-1-cont];
            array[DIM-1-cont]=supporto;
        }
        cout<<array[cont]<<" ";
        cont++;
    }
}