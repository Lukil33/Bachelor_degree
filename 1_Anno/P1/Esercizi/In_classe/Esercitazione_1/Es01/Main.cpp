#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
#define MAX_LENGHT 100

void convert_to_maiusc(char word[MAX_LENGHT]);
char last_word_character(char word[MAX_LENGHT]);

int main(int argc, char * argv []){
    if(argc != 3){
        cerr<<"Error: ./a.out <input_file> <output_file>"<<endl;
        exit(1);
    }

    fstream input, output;
    input.open(argv[1], ios::in);
    output.open(argv[2], ios::out);

    char word[MAX_LENGHT];

    input>>word;
    if((word[0]>'a')&&(word[0]<'z')){
        convert_to_maiusc(word);
    }
    output<<word<<" ";

    char character = last_word_character(word);

    while(input>>word){
        if(character == '.' || character == '!' || character == '?'){
            convert_to_maiusc(word);
        }
        output<<word<<" ";
        character = last_word_character(word);
    }

    input.close();
    output.close();
    return 0;
}

void convert_to_maiusc(char word[MAX_LENGHT]){
    word[0]+='A'-'a';
}

char last_word_character(char word[MAX_LENGHT]){
    char character=word[0];
    int i=0;
    while(word[i]!='\0'){
        character=word[i];
        i++;
    }
    return character;
}