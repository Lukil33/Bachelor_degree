#include <iostream>
#include <cstdlib>
using namespace std;

char lettera_randomica();
void controllo_maiuscola(char lettera_inserita, char lettera);
void controllo_vocale(char lettera_inserita, char lettera);

int main(){
    srand(time(NULL));
    char lettera=lettera_randomica();
    char lettera_inserita;

    cout<<"Benvento al gioco piu' noioso al mondo"<<endl;
    cout<<"Se sei qui vuol dire che non hai proprio nulla di meglio da fare"<<endl;
    cout<<"Vabbe', cominciamo..."<<endl;
    cout<<"Inserisci la lettera: ";
    cin>>lettera_inserita;

    while(lettera_inserita!=lettera){
        controllo_maiuscola(lettera_inserita, lettera);
        controllo_vocale(lettera_inserita, lettera);
        cout<<"Hai sbagliato, inserisci nuovamente la lettera: ";
        cin>>lettera_inserita;
    }
    cout<<"Bravo, hai indovinato"<<endl;
    return 0;
}

char lettera_randomica(){
    char lettera=rand()%57+65;
    while(lettera>'Z'&&lettera<'a'){
        lettera=rand()%57+65;
    }
    return lettera;
}

void controllo_maiuscola(char lettera_inserita, char lettera){
    if(lettera<='Z'){
        if(lettera_inserita<='Z'){
            cout<<"Maiuscola/Minuscola: Si!"<<endl;
        }else{
            cout<<"Maiuscola/Minuscola: No!"<<endl;
        }
    }else{
        if(lettera_inserita>='a'){
            cout<<"Maiuscola/Minuscola: Si!"<<endl;
        }else{
            cout<<"Maiuscola/Minuscola: No!"<<endl;
        }
    }
}

void controllo_vocale(char lettera_inserita, char lettera){
    if(lettera=='A'||lettera=='E'||lettera=='I'||lettera=='O'||lettera=='U'||
       lettera=='a'||lettera=='e'||lettera=='i'||lettera=='o'||lettera=='u'){
        if(lettera_inserita=='A'||lettera_inserita=='E'||lettera_inserita=='I'||lettera_inserita=='O'||lettera_inserita=='U'||
           lettera_inserita=='a'||lettera_inserita=='e'||lettera_inserita=='i'||lettera_inserita=='o'||lettera_inserita=='u'){
            cout<<"Vocale/Consonante: Si!"<<endl;
        }else{
            cout<<"Vocale/Consonante: No!"<<endl;
        }
    }else{
        if(lettera_inserita=='A'||lettera_inserita=='E'||lettera_inserita=='I'||lettera_inserita=='O'||lettera_inserita=='U'||
           lettera_inserita=='a'||lettera_inserita=='e'||lettera_inserita=='i'||lettera_inserita=='o'||lettera_inserita=='u'){
            cout<<"Vocale/Consonante: No!"<<endl;
        }else{
            cout<<"Vocale/Consonante: Si!"<<endl;
        }
    }
}