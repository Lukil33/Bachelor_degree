#include <iostream>
using namespace std;

int* add_element(int* pile, int&);
int* remove_element(int* pile, int&);
void print_pile(int* pile, int);
int* dim_g(int* pile, int&);
int* dim_r(int* pile, int&);

int main(){
    char letter;
    int* pile={};
    int dim_buffer=0;
    do{
        cout<<"<a> Add an element"<<endl
            <<"<r> Remove an element"<<endl
            <<"<p> Print the pile"<<endl
            <<"<q> Quit"<<endl;
        cin>>letter;

        if(letter == 'a'){
            pile = add_element(pile, dim_buffer);
        }
        if(letter == 'r'){
            pile = remove_element(pile, dim_buffer);
        }
        if(letter == 'p'){
            print_pile(pile, dim_buffer);
        }
    }while(letter != 'q');
    delete[] pile;
    return 0;
}

int* add_element(int* pile, int& dim_buffer){
    int number;
    cout<<"Inserire un numero: ";
    cin>>number;
    pile=dim_g(pile, dim_buffer);
    pile[dim_buffer-1]=number;
    return pile;
}

int* remove_element(int* pile, int& dim_buffer){
    if(dim_buffer<=0){
        cout<<"Pila vuota"<<endl;
    }else{
        pile=dim_r(pile, dim_buffer);
    }
    return pile;
}

void print_pile(int* pile, int dim_buffer){
    cout<<"Pile-> ";
    for(int i=0; i<dim_buffer; i++){
        cout<<pile[i]<<" ";
    }
    cout<<endl;
}

int* dim_g(int* pile, int& dim_buffer){
    dim_buffer++;
    int* new_pila=new int[dim_buffer];
    for(int i=0; i<(dim_buffer-1); i++){
        new_pila[i]=pile[i];
    }
    delete[] pile;
    return new_pila;
}

int* dim_r(int* pile, int& dim_buffer){
    dim_buffer--;
    int* new_pila=new int[dim_buffer];
    for(int i=0; i<(dim_buffer); i++){
        new_pila[i]=pile[i];
    }
    delete[] pile;
    return new_pila;
}
