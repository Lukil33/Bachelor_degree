#include <iostream>
#include <fstream>
#define DIM_Y 10000
#define DIM_X 100
using namespace std;

int main(int argc, char* argv[]){
    char* input_nome_file=argv[1];
    char* output_nome_file=argv[2];
    char words[DIM_Y][DIM_X];
    char word[DIM_X];
    fstream myin, myout;
    
    myin.open(input_nome_file,ios::in);

    int index=0;

    while(myin >> word){
        while(words[i]=='\0'){
            
        }
        words[index] = word;
        index++;
    }

    return 0;
}