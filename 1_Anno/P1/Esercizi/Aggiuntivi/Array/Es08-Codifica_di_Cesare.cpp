#include <iostream>
#include <cstdlib>
using namespace std;
#define DIM 5

void random_number(char* array);

void codifica_di_cesare(char* array);

int main(){
    srand(time(NULL));
    char array[DIM];

    random_number(array);
    cout<<endl;
    codifica_di_cesare(array);
    return 0;
}

void random_number(char* array){
    for(int i=0; i<DIM; i++){
        do{
            array[i]=rand()%(('z'+1)-'A')+('A');
        }while((array[i]>'Z')&&(array[i]<'a'));
        cout<<array[i]<<" ";
    }
}

void codifica_di_cesare(char* array){
    for(int i=0; i<DIM; i++){
        if((array[i]+3)<='z'){
            if(((array[i]+3)>'Z')&&((array[i]+3)<'a')){
                array[i]=array[i]+3+('a'-'Z'-1);
            }else{
                array[i]+=3;
            }
        }else{
            array[i]=array[i]+3-('z'-'A'+1);
        }
        cout<<array[i]<<" ";
    }
    cout<<endl;
}