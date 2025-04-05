#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void callrecursion(vector<char>, int, int);
void print(vector<char>, int);

int main(){

    vector<char> vec = {'s','s','d','d','s','s','d','s','d'};

    callrecursion(vec, 0, 0);
    cout<<endl;
    callrecursion(vec, vec.size()-1, 0);

    return 0;
}

//todo: non capisco come mai quando la funzione entra in ricorsione non vengono analizzati tutti i casi ma ne viene analizzato solamente il primo
//Es: perchè di ddssdsd viene analizzato dsd e non anche d? o perchè dsd si sviluppa in d (notato come primo elemento) e non in d-d (notato come primo ed ultimo elemento)

void callrecursion(vector<char> vec, int pos, int count){
    count += 1;
    int counter_d = 0;
    int counter_s = 0;

    if(pos == 0){
        //Rimuovo il primo carattere che verrà perduto in qualsiasi caso e aggiorno il counter
        char first_character = vec.front();
        vec.erase(vec.begin());

        //Adesso controllo per ogni elemento nell'array se può prendere il posto al bordo dell'array
        while(!vec.empty()){
            //Rimuovo il primo carattere e controllo se crea nuovi possibili elementi ai bordi e aggiorno il counter
            first_character = vec.front();
            vec.erase(vec.begin());

            if(first_character == 's'){
                if(counter_s > 0){
                    counter_s -= 1;
                }else if(counter_d%2 == 0){
                    if(counter_d > 0){
                        counter_d -= 1;
                    }else{
                        counter_s += 1;
                    }
                    print(vec, count);
                    callrecursion(vec, 0, count);
                    callrecursion(vec, vec.size()-1, count+3);
                    print(vec, count);
                }else if(counter_d%2 == 1){
                    counter_d -= 1;
                }
            }else{
                counter_d += 1;
                if(counter_d%2 == 0 && counter_s%2 == 1){
                    print(vec, count);
                    callrecursion(vec, 0, count);
                    callrecursion(vec, vec.size()-1, count+3);
                    print(vec, count);
                }
            }
        }
    }else{
        //Rimuovo l'ultimo carattere che verrà perduto in qualsiasi caso e aggiorno il counter
        char last_character = vec.back();
        vec.pop_back();

        while(!vec.empty()){
            //Rimuovo l'ultimo carattere e controllo se crea nuovi possibili elementi ai bordi e aggiorno il counter
            last_character = vec.back();
            vec.pop_back();
            if(last_character == 'd'){
                if(counter_d > 0){
                    counter_d -= 1;
                }else if(counter_s%2 == 0){
                    if(counter_s > 0){
                        counter_s -= 1;
                    }else{
                        counter_d += 1;
                    }
                    print(vec, count);
                    callrecursion(vec, 0, count);
                    callrecursion(vec, vec.size()-1, count+3);
                    print(vec, count);
                }else if(counter_s%2 == 1){
                    counter_s -= 1;
                }
            }else{
                counter_s += 1;
                if(counter_d%2 == 1 && counter_s%2 == 0){
                    print(vec, count);
                    callrecursion(vec, 0, count);
                    callrecursion(vec, vec.size()-1, count+3);
                    print(vec, count);
                }
            }
        }
    }
}

void print(vector<char> vec, int count){
    for(int i=0; i<count-1; i++){
        cout<<"     ";
    }
    cout<<"vec -> ";
    for(char i : vec){
        cout<<i<<" ";
    }
    cout<<endl;
}