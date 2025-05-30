#include <iostream>
#include <fstream>
using namespace std;

long conversion(long number);
long pow(int esponente, int base);

int main(int argc, char* argv[]){
    if(argc != 3){
        cerr<<"Error: ./a.out <input_fle> <output_file>"<<endl;
        exit(1);
    }

    fstream input, output;
    input.open(argv[1], ios::in);
    if(input.fail()){
        cerr<<"Error during file opening"<<endl;
        exit(2);
    }
    output.open(argv[2], ios::out);
    if(output.fail()){
        cerr<<"Error during file opening"<<endl;
        input.close();
        exit(2);
    }

    //da controllare
    char word[100];

    while(input>>word){
        long number=atoi(word);
        output<<conversion(number)<<endl;
    }

    //fine da controllare

    input.close();
    output.close();
    return 0;
}

long conversion(long number){
    long result=0;
    while(number > 0){
        int esponente=0;
        while((number-pow(esponente+1, 10))>=0){ //base di partenza
            esponente++;
        }
        number-=pow(esponente, 10); //base di partenza
        result+=1*pow(esponente, 2); //base convertita
    }
    cout<<result<<endl;
    return result;
}

long pow(int esponente, int base){
    int risultato=1;
    while(esponente>0){
        risultato*=base;
        esponente--;
    }
    return risultato;
}