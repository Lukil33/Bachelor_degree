#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

bool isValid(char*);
bool check(char*, char archivio[][100], int*, int);

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

    char archivio[100][100];
    int ripetizioni[100];
    char word[100];
    int counter = 0;

    while(input>>word){
        if(isValid(word)){
            if(!check(word, archivio, ripetizioni, counter)){
                strcpy(archivio[counter], word);
                ripetizioni[counter] = 1;
                counter+=1;
            }
        }
    }

    for(int i=0; i<counter; i++){
        output<<archivio[i]<<": "<<ripetizioni[i]<<endl;
    }

    input.close();
    output.close();
    return 0;
}

bool isValid(char* word){
    int res = true;
    for(int i=0; i<strlen(word); i++){
        if(word[i]<'a' || word[i]>'z'){
            res = false;
        }
    }
    return res;
}

bool check(char* word, char archivio[][100], int* ripetizioni, int counter){
    bool res = false;
    for(int i=0; i<counter; i++){
        if(strcmp(word, archivio[i]) == 0){
            ripetizioni[i]+=1;
            res = true;
        }
    }
    return res;
}