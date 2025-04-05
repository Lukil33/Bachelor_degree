#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

vector<char> vec;
vector<bool> res;

//Funzioni specifiche per questo es
void flatLand();
void possibilities(int, int, bool);
//Funzione che controlla se tale nodo è costretto a vincere
bool hasWon(int, int, bool);
//Funzione che controlla se tale nodo è costretto a perdere
bool hasLost(int, int, bool);
//Funzione che controlla se tale nodo è già stato visitato in tale verso
void callrecursion(int, int, bool);

//Funzioni stupide da riutilizzare
int count_left(int, int, char);
int count_right(int, int, char);

int main(){
    ifstream in("input.txt");

    int len;
    in >> len;

    //Inizializzo i miei vettori
    vec.resize(len);
    res.resize(len, false);

    for(int i=0; i<len; i++){
        in >> vec[i];
    }

    flatLand();

    return 0;
}

void flatLand(){
    //Funzione principale con funzione di wrapper e di stampa finale su file
    ofstream out("output.txt");

    //Considero la possibilità di dover calcolare un numero sia avanti che dietro
    possibilities(0, vec.size()-1, true);
    possibilities(0, vec.size()-1, false);

    //Stampo la dimensione e il risultato
    int num_elementi = 0;
    string result = "";
    for(int i=0; i<(int)res.size(); i++){
        if(res[i]){
            num_elementi += 1;
            //Passo il numero a string perchè da questo punto di vista C++ è abbastanza stupido
            result+= to_string(i) + " ";
        }
    }
    out << num_elementi << endl << result;
}

void possibilities(int start, int end, bool isGoingRight){
    //Funzione ricorsiva core nella quale controlliamo se un elemento ad una posizione deve vincere, deve perdere, può vincere o può perdere
    
    //Inseriamo la posizione che stiamo controllando nella lista di posizioni già controllate
    if(isGoingRight){
        //Se l'elemento vince forzatamente viene aggiunto a res e terminiamo la funzione
        if(hasWon(start, end, isGoingRight)){
            res[start] = true;
        }else{
            //Controlliamo se il nostro elemento è falso e può vincere e in quel caso lo aggiungiamo in res
            if(!res[start] && !hasLost(start, end, isGoingRight)){
                res[start] = true;
            }

            //Mandiamo la funzione in ricorsione per il primo elemento che può prendere il posto del nostro elemento
            callrecursion(start, end, isGoingRight);
        }
    }else{
        //Se l'elemento vince forzatamente viene aggiunto a res e terminiamo la funzione
        if(hasWon(start, end, isGoingRight)){
            res[end] = true;
        }else{
            //Controlliamo se il nostro elemento è falso e può vincere e in quel caso lo aggiungiamo in res
            if(!res[end] && !hasLost(start, end, isGoingRight)){
                res[end] = true;
            }

            //Mandiamo la funzione in ricorsione per il primo elemento che può prendere il posto del nostro elemento
            callrecursion(start, end, isGoingRight);
        }
    }
}

bool hasWon(int start, int end, bool isGoingRight){
    //Funzione che controlla se l'elemento in pos è costretto a vincere
    //ovvero se vale la formula (*+s=0 ^ *+d%2=1+s=1) con elemento in prima pos oppure in modo analogo (d=0+* ^ d=1+s%2=1+*) con elemento in ultima pos
    if(start == end){
        return true;
    }else{
        int num_element;
        int num_element_after;
        if(isGoingRight){
            num_element = count_right(start, end, 'd');
            num_element_after = count_right(start+num_element, end, 's');
            if(num_element_after == 0 || (num_element_after == 1 && num_element%2 == 1)){
                return true;
            }
        }else{
            num_element = count_left(start, end, 's');
            num_element_after = count_left(start, end-num_element, 'd');
            if(num_element_after == 0 || (num_element_after == 1 && num_element%2 == 1)){
                return true;
            }
        }
        return false;
    }
}

bool hasLost(int start, int end, bool isGoingRight){
    //Funzione che controlla se l'elemento in pos è costretto a perdere
    //ovvero se vale la formula (*+d=0+s%2=1) con elemento in prima pos oppure in modo analogo (d%2=1+s=0+*) con elemento in ultima pos
    if(isGoingRight && (count_right(start, end, 'd') == 0 && count_right(start, end, 's')%2 == 1)){
        return true;
    }else if(!isGoingRight && (count_left(start, end, 's') == 0 && count_left(start, end, 'd')%2 == 1)){
        return true;
    }
    return false;
}

void callrecursion(int start, int end, bool isGoingRight){
    int counter_d = 0;
    int counter_s = 0;
    bool found = false;

    if(isGoingRight){
        //Adesso controllo per ogni elemento nell'array se può prendere il posto al bordo dell'array
        while(start < end && !found){
            //Rimuovo il primo carattere e controllo se crea nuovi possibili elementi ai bordi e aggiorno il counter
            start += 1;

            if(vec[start] == 's'){
                if(counter_d > 0){
                    counter_d -= 1;
                }else{
                   possibilities(start+1, end, true);
                   found = true;
                }
            }else{
                if(counter_d != 0){
                    counter_d = 0;
                }else{
                    counter_d = 1;
                }
            }
        }
    }else{
        //Adesso controllo per ogni elemento nell'array se può prendere il posto al bordo dell'array
        while(start < end && !found){
            //Rimuovo l'ultimo carattere e controllo se crea nuovi possibili elementi ai bordi e aggiorno il counter
            end -= 1;

            if(vec[end] == 'd'){
                if(counter_s > 0){
                    counter_s -= 1;
                }else{
                    possibilities(start, end-1, false);
                    found = true;
                }
            }else{
                if(counter_s != 0){
                    counter_s = 0;
                }else{
                    counter_s = 1;
                }
            }
        }
    }
}

int count_left(int start, int end, char carattere){
    //Funzione che ritorna il numero di elementi di un tipo a sinistra rispetto alla posizione fornita
    //Si blocca al primo carattere di un tipo diverso: Es(sssdddsds, passo alla funzione start = 2, end=8, carattere = d, il risultato è 1)
    int res = 0;
    while(start<end-1 && vec[end-1] == carattere){
        end -= 1;
        res += 1;
    }
    return res;
}

int count_right(int start, int end, char carattere){
    //Funzione che ritorna il numero di elementi di un tipo a destra rispetto alla posizione fornita
    //Si blocca al primo carattere di un tipo diverso: Es(sssdddsds, passo alla funzione start = 2, end=8, carattere = d, il risultato è 3)
    int res = 0;
    while(start<end-1 && vec[start+1] == carattere){
        start += 1;
        res += 1;
    }
    return res;
}