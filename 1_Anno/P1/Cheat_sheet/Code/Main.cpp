#include <iostream>
#include <fstream>
using namespace std;
#include "Pila.h"
#include "Coda.h"

int main(){
    coda_init();
    pila_init();

    char word[101];
    cout << "Insert the word: ";
    cin >> word;
    cout << endl;

    int i=0;
    while(word[i]!='\0'){
        coda_enqueue(word[i]);
        pila_push(word[i]);
        i++;
    }

    char lettera_coda, lettera_pila;
    bool palindroma=true;
    while((coda_first(lettera_coda))&&(pila_top(lettera_pila))){
        if(lettera_coda!=lettera_pila){
            palindroma=false;
        }
        coda_dequeue();
        pila_pop();
    }

    if(palindroma){
        cout<<"The word is palindrome"<<endl;
    }else{
        cout<<"The word is not palindrome"<<endl;
    }

    coda_deinit();
    pila_deinit();
  return 0;
}