#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

void rotate(char*, int);
void rotatetoleft(char*);

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
    cout<<"Inserire un numero di shifting: ";
    cin>>key;

    char word[255];

    while(input>>word){
        char end[255]={};
        
        int i=int(strlen(word))-1;
        while((word[i] < 'a' || word[i] > 'z')&&(word[i] < 'A' || word[i] > 'Z')){
            i--;
        }
        for(int j=i+1; j<int(strlen(word)); j++){
            end[j-i-1] = word[j];
        }
        word[i+1] = '\0';

        i=0;
        while((word[i] < 'a' || word[i] > 'z')&&(word[i] < 'A' || word[i] > 'Z')){
            output<<word[i];
            i++;
        }

        rotate(word, i);
        word[strlen(word)-i] = '\0';

        rotate(word,key);
        output<<word;
        
        output<<end<<" ";
    }
    
    
    return 0;
}

void rotate(char* a, int k){
    for(int i=0; i<k; i++){
        rotatetoleft(a);
    }
}

void rotatetoleft(char* a){
    char start = a[0];
    for(int i=1; i<int(strlen(a)); i++){
        a[i-1] = a[i];
    }
    a[strlen(a)-1] = start;
}