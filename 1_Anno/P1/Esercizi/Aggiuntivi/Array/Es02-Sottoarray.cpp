#include <iostream>
#include <cstdlib>
using namespace std;
#define DIM_primo_array 2
#define DIM_secondo_array 10

void random_number(int* a, int i);

void controllo_array(int* a, int* b);
bool ausiliaria(int* a, int* b, bool sottospazio, int contatore_a, int contatore_b);

int main(){
    srand(time(NULL));
    int a[DIM_primo_array], b[DIM_secondo_array];

    for(int i=0;i<DIM_secondo_array;i++){
        random_number(b, i);
    }
    cout<<endl;
    for(int i=0;i<DIM_primo_array;i++){
        random_number(a, i);
    }
    cout<<endl;

    controllo_array(a, b);
    return 0;
}

void random_number(int* a, int i){
    a[i]=rand()%10;
    cout<<a[i]<<" ";
}

void controllo_array(int* a, int* b){
    bool sottospazio=true;
    int contatore_a=DIM_primo_array, contatore_b=DIM_secondo_array;
    sottospazio=ausiliaria(a, b, sottospazio, contatore_a, contatore_b);
    if(sottospazio==true){
        cout<<"A e' un sottospazio di B"<<endl;
    }else{
        cout<<"A non e' un sottospazio di B"<<endl;
    }
}

bool ausiliaria(int* a, int* b, bool sottospazio, int contatore_a, int contatore_b){
    if((sottospazio==false)||(contatore_a<0)){
        return sottospazio;
    }else{
        if(a[contatore_a]==b[contatore_b]){
            contatore_a--;
            contatore_b=DIM_secondo_array;
        }else{
            contatore_b--;
        }
        if(contatore_b<0){
            sottospazio=false;
        }
        ausiliaria(a, b, sottospazio, contatore_a, contatore_b);
    }
}