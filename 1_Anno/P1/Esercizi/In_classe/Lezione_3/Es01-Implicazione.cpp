#include <iostream>
using namespace std;

bool defbool(char var){
    bool valore = 0;

    do{
        cin>>var;
    }while(var != '1'&&var != 't'&&var != 'T'&&var != '0'&&var != 'f'&&var != 'F');

    if(var == '1'||var == 't'||var == 'T'){
        valore = 1;
    }
    if(var == '0'||var == 'f'||var == 'F'){
        valore = 0;
    }

    return valore;
}

int main(){
    bool P, Q;
    char var;
    cout<<"Inserisci le due variabili booleane"<<endl;

    P=defbool(var);
    Q=defbool(var);
    
    cout<<"inseriti P e Q allora: "<<(! P||Q)<<endl;

    return 0;
}