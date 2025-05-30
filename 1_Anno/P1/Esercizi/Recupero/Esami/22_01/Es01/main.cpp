#include<iostream>
#include<fstream>
#include<cstring>
#include<cmath>
using namespace std;

int convert(char*);
int operation(char, int, int);

int main(int argc, char * argv []) {
    if(argc != 3){
        cerr<<"Error: ./a.out <input_file> <output_file>"<<endl;
        return -1;
    }
    fstream input, output;
    input.open(argv[1], ios::in);
    if(input.fail()){
        cerr<<"Error during file opening"<<endl;
        return -2;
    }
    output.open(argv[2], ios::out);
    if(output.fail()){
        cerr<<"Error during file opening"<<endl;
        input.close();
        return -2;
    }

    char cifra[10];
    char sign;

    while(input>>cifra){
        int fnum = convert(cifra);
        input>>sign;
        input>>cifra;
        int snum = convert(cifra);
        output<<operation(sign, fnum, snum)<<endl;
    }

    input.close();
    output.close();
    return 0;
}

int convert(char* c){
    int res = 0;
    for(int i=0-1; i<int(strlen(c)); i++){
        if(c[i] >= '0' && c[i] <= '9'){
            res += (c[i] - '0') * pow(17, strlen(c)-1-i);
        }else if(c[i] >= 'A' && c[i] <= 'G'){
            res += (c[i] - 'A' + 10) * pow(17, strlen(c)-1-i);
        }
    }
    cout<<c<<" - "<<res<<endl;
    return res;
}

int operation(char o, int fn, int sn){
    int res = 0;
    switch(o){
        case '+': res = fn + sn; break;
        case '*': res = fn * sn; break;
        case '^': res = pow(fn, sn); break;
    }
    return res;
}