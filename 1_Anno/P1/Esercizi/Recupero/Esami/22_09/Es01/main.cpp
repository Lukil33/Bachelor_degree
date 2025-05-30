#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char* argv[]){
    if(argc != 3){
        cerr<<"Error: ./a.out <input_file> <output_file>"<<endl;
        return -1;
    }
    fstream inp, outp;
    inp.open(argv[1], ios::in);
    if(inp.fail()){
        cerr<<"Error: error during file opening"<<endl;
        return -2;
    }
    outp.open(argv[2], ios::out);
    if(inp.fail()){
        cerr<<"Error: error during file opening"<<endl;
        inp.close();
        return -2;
    }

    char line[255];
    char longest[255];
    int max = 0;

    while(inp.getline(line, 255)){
        int len = 0;

        for(int i=0; line[i] != '\0'; i++){
            len+=1;
        }

        if(len >= max){
            max = len;
        }

        for(int i=0; line[i] != '\0'; i++){
            longest[i] = line[i];
        }

        outp<<len<<endl;
    }

    outp<<longest<<" - "<<max<<endl;

    inp.close();
    outp.close();
    return 0;
}