#include <iostream>
#include <fstream>
using namespace std;

int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");

    int len;
    in >> len;
    
    if(len == 0){

        out << len;

    }else{
    
        int num;
        in >> num;

        int somma_massima = num;
        int somma_attuale = num;

        for(int i=1; i<len; i++){
            in >> num;
            if(somma_attuale < 0){
                somma_attuale = 0;
            }
            somma_attuale += num;
            if(somma_massima < somma_attuale){
                somma_massima = somma_attuale;
            }
        }

        out << somma_massima;

    }
    return 0;
}