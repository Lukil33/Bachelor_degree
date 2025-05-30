#include <iostream>
using namespace std;

void stampa_triangolo(int riga, int c_riga, int c_colonna);
int numero_preciso(int c_riga, int c_colonna, int numero);

int main(){
    int riga, c_riga=1, c_colonna=1;

    cout<<"Inserire la riga del Triangolo di Pascal: ";
    cin>>riga;

    stampa_triangolo(riga, c_riga, c_colonna);
    return 0;
}

void stampa_triangolo(int riga, int c_riga, int c_colonna){
    int numero=0;
    if((c_riga>=riga)&&(c_colonna>riga)){
        cout<<endl;
    }else{
        if(c_colonna>c_riga){
            c_colonna=1;
            c_riga+=1;
            cout<<endl;
        }
        numero = numero_preciso(c_riga, c_colonna, numero);
        cout<<numero<<" ";
        stampa_triangolo(riga, c_riga, c_colonna+1);
    }
    
}

int numero_preciso(int c_riga, int c_colonna, int numero){
    if(c_colonna>=c_riga){
        numero=1;
        return numero;
    }
    if(c_colonna<=1){
        numero=1;
        return numero;
    }
    numero=numero_preciso(c_riga-1,c_colonna-1,numero)+numero_preciso(c_riga-1,c_colonna, numero);
    return numero;
}