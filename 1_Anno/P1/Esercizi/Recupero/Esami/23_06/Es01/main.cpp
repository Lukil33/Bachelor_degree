#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

void lower(char*);
void shift(char*, int);
void movetoright(char*);
int countrepetition(char*, char*);

int main(int argc, char* argv[]){
    if(argc != 2){
        cerr<<"Error: ./a.out <input_file>"<<endl;
        return -1;
    }
    fstream input;
    input.open(argv[1], ios::in);
    if(input.fail()){
        cerr<<"Error during file opening"<<endl;
        return -2;
    }

    char stringa[255];
    int key;
    cout<<"Inserire una serie di caratteri: ";
    cin>>stringa;
    lower(stringa);

    cout<<"Inserire un numero per lo shifting: ";
    cin>>key;
    shift(stringa, key);

    cout<<stringa<<endl;

    char word[255];
    int occorrenze = 0;
    while(input>>word){
        occorrenze += countrepetition(word, stringa);
    }

    cout<<occorrenze<<endl;

    input.close();
    return 0;
}

void lower(char* str){
    for(int i=0; i<int(strlen(str)); i++){
        if(str[i] >= 'A' && str[i] <= 'Z'){
            str[i] += 'a' - 'A';
        }
    }
}

void shift(char* str, int key){
    for(int i=0; i<key; i++){
        movetoright(str);
    }
}

void movetoright(char* str){
    int len = strlen(str)-1;
    char last = str[len];

    for(int i=len-1; i>=0; i--){
        str[i+1] = str[i];
    }
    str[0] = last;
}

int countrepetition(char* bigger, char* smaller){
    int res = 0;

    for(int i=0; i<int(strlen(bigger)); i++){
        if(bigger[i] == smaller[0]){
            bool check = true;
            for(int j=0; check && j<int(strlen(smaller)); j++){
                if(bigger[i+j] != smaller[j]){
                    check = false;
                }
            }
            if(check){
                res+=1;
            }
        }
    }

    return res;
}