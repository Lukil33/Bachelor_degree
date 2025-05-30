#include<iostream>
#include<fstream>
#include<cstring>
#include<cmath>
using namespace std;
#define DIM 255

// è possibile definire proprie funzioni
void testa(char *, char *);
void coda(char *, char *);
bool lettera(char);
void ruota_body(char *, int);

int main(int argc, char * argv []) {
    if (argc != 3){
        cerr<<"Error: ./a.out <input_file> <output_file>"<<endl;
        exit(1);
    }

    fstream input, output;
    input.open(argv[1], ios::in);
    output.open(argv[2], ios::out);

    int number;
    char word[DIM];

    cout<<"Di quanto bisogna shiftare a sinistra: ";
    cin>>number;

    while(input>>word){
        char testa_word[DIM]={'\0'};
        testa(word, testa_word);
        char coda_word[DIM]={'\0'};
        coda(word, coda_word);
        ruota_body(word, number);
        output<<testa_word<<word<<coda_word<<" ";
    }

    input.close();
    output.close();
    return 0;
}

void testa(char * word, char * testa){
    int dim=0;
    while(!(lettera(word[dim]))){
        testa[dim]=word[dim];
        dim++;
    }
    int i=0;
    while(word[i] != '\0'){
        word[i]=word[i+dim];
        i++;
    }
}

void coda(char * word, char * coda){
    int dim=0;
    while(word[dim]!='\0'){
        dim++;
    }
    int i=0, cont=1;
    while(!(lettera(word[dim-cont]))){
        coda[i]=word[dim-cont];
        i++;
        cont++;
    }
    word[dim-i]='\0';
}

bool lettera(char letter){
    return ((letter>='a'&&letter<='z')||(letter>='A'&&letter<='Z'));
}

void ruota_body(char * word, int number){
    int cont=1;
    while(word[cont-1] != '\0'){
        cont++;
    }
    number=number%cont;
    char b[cont];
    for(int i=0; i<cont-1; i++){
        int l=i-number;
        if(l<0){
            l+=cont-1;
        }
        b[i]=word[l];
    }
    int i=0;
    while(word[i] != '\0'){
        word[i]=b[i];
        i++;
    }
}