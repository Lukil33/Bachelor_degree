#include <iostream>
#include <cstdlib>
using namespace std;
#define DIM 10

void random_number(int * a);

void bubble_sort_ricorsivo(int * a);
void controllo_ordine(int * a, bool & ordinato);
void bubble_sort_ausiliaria(int * a, int & contatore, int& l);

void binary_search(int * a, int lunghezza, int contatore, int numero);

int main(){
    srand(time(NULL));
    int a[DIM], lunghezza=DIM/2, contatore=1, numero;

    random_number(a);
    bubble_sort_ricorsivo(a);

    cout<<"Inserire un numero da 0 a 9: ";
    cin>>numero;
    while(numero<0||numero>9){
        cout<<"Leggi cio' che scrivo?"<<endl;
        cout<<"Inserire un numero da 0 a 9: ";
        cin>>numero;
    }

    binary_search(a, lunghezza, contatore, numero);

    return 0;
}

void random_number(int * a){
    cout<<"[ ";
    for(int i=0;i<DIM;i++){
        a[i]=rand()%10;
        cout<<a[i]<<" ";
    }
    cout<<"]"<<endl;
}

void bubble_sort_ricorsivo(int * a){
    int contatore=0;
    int l=0;

    bubble_sort_ausiliaria(a, contatore, l);

    cout<<"[ ";
    for(int j=0; j<DIM; j++){
        cout<<a[j]<<" ";
    }
    cout<<"]"<<endl;
}

void bubble_sort_ausiliaria(int * a, int & contatore, int& l){
    bool ordinato=true;
    controllo_ordine(a, ordinato);
    if((ordinato==true)){
    }else{
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

void controllo_ordine(int * a, bool & ordinato){
    int v=0;
    while((ordinato==true)&&(v+1<DIM)){
        if(a[v]>a[v+1]){
            ordinato=false;
        }
        v++;
    }
}

void binary_search(int * a, int lunghezza, int contatore, int numero){
    if(6==contatore){
        cerr<<"Numero inserito non presente all'interno dell'array"<<endl;
    }else if(a[lunghezza]==numero){
        if((lunghezza==0)){
            cout<<"L'indice e': "<<lunghezza<<endl;
        }else if(a[lunghezza-1]==a[lunghezza]){
            lunghezza--;
            binary_search(a, lunghezza, contatore, numero);
        }else{
            cout<<"L'indice e': "<<lunghezza<<endl;
        }
    }else{
        if(a[lunghezza]>numero){
            if((lunghezza/(2*contatore))<1){
                lunghezza--;
            }else{
                lunghezza-=lunghezza/(2*contatore);
            }
        }else{
            if((lunghezza/(2*contatore))<1){
                lunghezza++;
            }else{
                lunghezza+=lunghezza/(2*contatore);
            }
        }
        contatore++;
        binary_search(a, lunghezza, contatore, numero);
    }
}