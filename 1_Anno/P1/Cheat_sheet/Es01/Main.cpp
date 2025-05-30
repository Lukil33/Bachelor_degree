#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char* argv[]){
    if(argc != 3){
        cerr<<"Error: ./a.out <input_fle> <output_file>"<<endl;
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

    //da controllare
    char word[];

    while(input>>word){

    }

    char riga[];
    while(input.getline(riga)){

    }
    //fine da controllare

    input.close();
    output.close();
    return 0;
}