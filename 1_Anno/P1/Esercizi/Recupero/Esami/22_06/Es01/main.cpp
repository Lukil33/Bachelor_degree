#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

int main(int argc, char* argv[]){
    if(argc != 4){
        cerr<<"Error: ./a.out <input_file> <order_file> <output_file>"<<endl;
        return -1;
    }
    fstream input, order, output;
    input.open(argv[1], ios::in);
    if(input.fail()){
        cerr<<"Error during file opening"<<endl;
        return -2;
    }
    order.open(argv[2], ios::in);
    if(order.fail()){
        cerr<<"Error during file opening"<<endl;
        input.close();
        return -2;
    }
    output.open(argv[3], ios::out);
    if(output.fail()){
        cerr<<"Error during file opening"<<endl;
        input.close();
        order.close();
        return -2;
    }

    char word[100];
    input>>word;
    const int lenght = atoi(word);
    char archivio[lenght][100];

    for(int i=0; i<lenght; i++){
        input>>word;
        strcpy(archivio[i], word);
    }

    int num;
    while(order>>num){
        if(num >= 0 && num<=lenght){
            output<<archivio[num]<<" ";
        }else{
            output<<"MISSING ";
        }
    }

    input.close();
    order.close();
    output.close();
    return 0;
}