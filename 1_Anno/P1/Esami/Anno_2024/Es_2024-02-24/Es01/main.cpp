#include <iostream>
#include <fstream>
using namespace std;

double Percentuale(int, int);

int main(int argc, char* argv[]){
    if(argc != 3){
        cerr<<"Error: ./a.out <motore_1> <motore_2>"<<endl;
        return -1;
    }
    fstream mot1, mot2;
    mot1.open(argv[1], ios::in);
    if(mot1.fail()){
        cerr<<"Error during file opening"<<endl;
        return -2;
    }
    mot2.open(argv[2], ios::in);
    if(mot2.fail()){
        cerr<<"Error during file opening"<<endl;
        mot1.close();
        return -2;
    }

    double num1;
    double num2;
    int misurazioni = 0;
    int maggiore = 0;

    while(mot1>>num1){
        mot2>>num2;
        if(num1>num2){
            maggiore += 1;
        }
        misurazioni += 1;
    }

    if(misurazioni != 0){
        cout<<"Percentuale: "<<Percentuale(maggiore, misurazioni)<<"%"<<endl;
    }else{
        cout<<"Errore, nel file non sono presenti misurazioni"<<endl;
    }

    mot1.close();
    mot2.close();
    return 0;
}

double Percentuale(int maggiori, int misurazioni){
    return maggiori*100/misurazioni;
}