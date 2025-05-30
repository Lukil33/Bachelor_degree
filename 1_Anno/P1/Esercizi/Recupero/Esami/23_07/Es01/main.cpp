#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

void compare(char*, char*);

int main(int argc, char* argv[]){
    if(argc != 2){
        cerr<<"Error: ./a.out <input_fle>"<<endl;
        return -1;
    }

    fstream input;
    input.open(argv[1], ios::in);
    if(input.fail()){
        cerr<<"Error during file opening"<<endl;
        return -2;
    }

    char stringa[256];
    cout<<"Inserire una stringa da cercare: ";
    cin>>stringa;

    char word[256];
    while(input>>word){
        compare(word, stringa);
    }

    input.close();
    return 0;
}

void compare(char* w, char* s){
    int lenW = strlen(w);
    int lenS = strlen(s);

    if(lenS <= lenW){
        for(int i = 0; i<lenW; i++){
            if(w[i] == s[0] || s[0] == '*'){
                bool check = true;

                for(int j = 0; check && j<lenS; j++){
                    if(w[i+j] != s[j] && s[j] != '*'){
                        check = false;
                    }
                }
                if(check){
                    for(int h = i; h<lenW; h++){
                        cout<<w[h];
                    }
                    cout<<endl;
                }
            }
        }    
    }
}