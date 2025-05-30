#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
using namespace std;

int decode(char*, int);
int convert(char);
char reconvert(int n);

int main(int argc, char* argv[]){
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

    int key;

    do{
        cout<<"Inserire una chiave di criptazione: ";
        cin>>key;
    }while(key >= 10000000);
    
    char word[100];
    while(input>>word){
        word[4] = '\0';
        int n = decode(word, key);
        int i = 0;
        while(n > 0){
            word[i] = reconvert(n%36);
            n/=36;
            i++;
        }
        
        word[i] = '\0';
        while(i > 0){
            i--;
            output<<word[i];
        }
        output<<endl;
    }

    input.close();
    output.close();
    return 0;
}

int decode(char* w, int n){
    for(int i=0; i<strlen(w); i++){
        n+=convert(w[i])*pow(36, strlen(w)-1-i);
    }
    return n;
}

int convert(char c){
    if(c >= '0' && c <= '9'){
        return c - '0';
    }else{
        return c - 'a' + 10;
    }
}

char reconvert(int n){
    if(n < 10){
        return '0' + n;
    }else{
        return 'a'+ n - 10;
    }
}