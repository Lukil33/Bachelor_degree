#include <iostream>
#include <fstream>
using namespace std;

void elaborariga(char*, int*, int&);
int converti(int*, int);
int pow_2(int);
int somma(int*, int);

int main(){
    fstream input, output;
    input.open("inputdati.txt", ios::in);
    if(input.fail()){
        cerr<<"Error during file opening"<<endl;
        return -2;
    }
    output.open("outputcheck.txt", ios::out);
    if(output.fail()){
        cerr<<"Error during file opening"<<endl;
        input.close();
        return -2;
    }

    char line[128];

    while(input>>line){
        int array[13]={};
        int ris = 0;
        elaborariga(line, array, ris);
        cout<<"Gialle"<<endl;
        if(somma(array, 13) == ris){
            output<<ris<<endl;
        }else{
            output<<"Errore"<<endl;
        }
    }

    input.close();
    output.close();
    return 0;
}

void elaborariga(char* str, int* num, int& ris){
    int b[128] = {};
    int dim_num = 0;
    int dim_str = 0;
    int dim_b = 0;
    while(str[dim_str] != '='){
        if(str[dim_str] == '+'){
            num[dim_num] = converti(b, dim_b);
            dim_num += 1;
            dim_b = 0;
        }else{
            b[dim_b] = str[dim_str] - '0';
            dim_b += 1;
        }
        dim_str += 1;
    }
    num[dim_num] = converti(b, dim_b);

    dim_str += 1;
    dim_b = 0;
    while(str[dim_str] != ';' && str[dim_str] != '\0'){
        b[dim_b] = str[dim_str] - '0';
        dim_b += 1;
        dim_str+=1;
    }
    ris = converti(b, dim_b);
}

int converti(int* b, int dim){
    int res = 0;
    for(int i=0; i<dim; i++){
        res += b[i] * pow_2(dim-1-i);
    }
    cout<<res<<" Rotondo"<<endl;
    return res;
}

int pow_2(int n){
    if(n > 0){
        return 2*pow_2(n-1);
    }else{
        return 1;
    }
}

int somma(int*a, int n){
    int res = 0;
    for(int i=0; i<n; i++){
        res += a[i];
    }
    return res;
}