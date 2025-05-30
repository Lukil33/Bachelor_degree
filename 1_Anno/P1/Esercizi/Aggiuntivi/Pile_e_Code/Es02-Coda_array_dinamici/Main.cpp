#include <iostream>
using namespace std;

int* add_element(int* code, int&);
int* remove_element(int* code, int&);
void print_code(int* code, int);
int* dim_g(int* code, int&);
int* dim_r(int* code, int&);

int main(){
    char letter;
    int* code={};
    int dim_buffer=0;
    do{
        cout<<"<a> Add an element"<<endl
            <<"<r> Remove an element"<<endl
            <<"<p> Print the code"<<endl
            <<"<q> Quit"<<endl;
        cin>>letter;

        if(letter == 'a'){
            code = add_element(code, dim_buffer);
        }
        if(letter == 'r'){
            code = remove_element(code, dim_buffer);
        }
        if(letter == 'p'){
            print_code(code, dim_buffer);
        }
    }while(letter != 'q');
    delete[] code;
    return 0;
}


int* add_element(int* code, int& dim_buffer){
    int number;
    cout<<"Inserire un numero: ";
    cin>>number;
    code=dim_g(code, dim_buffer);
    code[dim_buffer-1]=number;
    return code;
}

int* remove_element(int* code, int& dim_buffer){
    if(dim_buffer<=0){
        cout<<"Pila vuota"<<endl;
    }else{
        code=dim_r(code, dim_buffer);
    }
    return code;
}

void print_code(int* code, int dim_buffer){
    cout<<"code-> ";
    for(int i=0; i<dim_buffer; i++){
        cout<<code[i]<<" ";
    }
    cout<<endl;
}

int* dim_g(int* code, int& dim_buffer){
    dim_buffer++;
    int* new_code=new int[dim_buffer];
    for(int i=0; i<(dim_buffer-1); i++){
        new_code[i]=code[i];
    }
    delete[] code;
    return new_code;
}

int* dim_r(int* code, int& dim_buffer){
    dim_buffer--;
    int* new_code=new int[dim_buffer];
    for(int i=0; i<(dim_buffer); i++){
        new_code[i]=code[i+1];
    }
    delete[] code;
    return new_code;
}