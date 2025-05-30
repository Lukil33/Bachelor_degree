#include <iostream>
#include <cstdlib>
using namespace std;
#define DIM 10
#define Val_max 10

void random_number(int* array);

void frequenza(int* array, int* freq);
void azzera_array(int* freq);
void ausiliaria(int* array, int* freq, int i);
void stampa_array(int* freq);

int main(){
    srand(time(NULL));
    int array[DIM], freq[Val_max];

    random_number(array);
    cout<<endl;
    frequenza(array, freq);
    return 0;
}

void random_number(int* array){
    for(int i=0; i<DIM; i++){
        array[i]=rand()%Val_max;
        cout<<array[i]<<" ";
    }
}

void frequenza(int* array, int* freq){
    azzera_array(freq);
    for(int i=0; i<DIM; i++){
        ausiliaria(array, freq, i);
    }
    stampa_array(freq);
}

void azzera_array(int* freq){
    for(int i=0; i<Val_max; i++){
        freq[i]=0;
    }
}

void ausiliaria(int* array, int* freq, int i){
    for(int g=0; g<Val_max; g++){
        if(g==array[i]){
            freq[g]++;
        }
    }
}

void stampa_array(int* freq){
    for(int i=0; i<Val_max; i++){
        if(freq[i]!=0){
            cout<<"Frequenza "<<i<<": "<<freq[i]<<endl;
        }
    }
}