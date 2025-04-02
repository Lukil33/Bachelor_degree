#include <iostream>
#include <fstream>
using namespace std;

int funct(int,int);

int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");
    
    int rep;
    in>>rep;

    for(int i=0; i<rep; i++){
        int mess, ora, t = 0, camminate = 2;
        in>>mess;

        for(int j=0; j<mess; j++){
            in>>ora;
            camminate -= funct(ora,t);
            t = ora;
        }
        ora = 1440;
        camminate -= funct(ora,t);
        
        if(camminate > 0){
            out<<"NO"<<endl;
        }else{
            out<<"YES"<<endl;
        }

    }
}

int funct(int ora, int t){
    if(ora-t<120){
        return 0;
    }else{
        return funct(ora, t+120) + 1;
    }
}