#include <iostream>
#include <cstdlib>
using namespace std;
#define DIM 10

void random_number(int* array);

void conta_doppioni(int* array);

int main(){
    srand(time(NULL));
    int array[DIM];

    random_number(array);
    cout<<endl;
    conta_doppioni(array);
    return 0;
}

void random_number(int* array){
    for(int i=0; i<DIM; i++){
        array[i]=rand()%10;
        cout<<array[i]<<" ";
    }
}

void conta_doppioni(int* array){
    int doppioni=0;
    for(int i=0; i<DIM; i++){
        bool doppio=false;
        for(int g=0; g<DIM; g++){
            if(g==i){
            }else{
                if(array[i]==array[g]){
                    doppio=true;
                }
            }
        }
        if(doppio==true){
            doppioni++;
        }
    }
    cout<<"Ci sono "<<doppioni<<" doppioni"<<endl;
}