#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

vector<bool> res;

//Funzioni specifiche per questo es
void flatLand(vector<char>);
void possibilities(vector<char>, vector<pair<bool,bool>>&, int);
void possibilities_aus(vector<char>, vector<pair<bool,bool>>&, int, int);
//Funzione che controlla se tale nodo è costretto a vincere
bool hasWon(vector<char>, int);
//Funzione che controlla se tale nodo è costretto a perdere
bool hasLost(vector<char>, int);
//Funzione che controlla se tale nodo è già stato visitato in tale verso
bool hasntBeenVisited(vector<pair<bool,bool>>, int, int);
void callrecursion(vector<char>, vector<pair<bool,bool>>&, int, int);


//Funzioni stupide da riutilizzare
int count_left(vector<char>, int, char);
int count_right(vector<char>, int, char);
int max_num_contro(vector<char>, int, char);

int main(){
    ifstream in("input.txt");

    int len;
    in >> len;

    vector<char> vec;
    vec.resize(len);

    for(int i=0; i<len; i++){
        in >> vec[i];
    }

    flatLand(vec);

    return 0;
}

void flatLand(vector<char> vec){
    //Funzione principale con funzione di wrapper e di stampa finale su file
    ofstream out("output.txt");

    //Dimensiono res alla dimensione di vec e inizializzo tutti gli elementi a false
    res.resize(vec.size(), false);
    //Inizializzo visited alla dimensione di vec e inizializzo tutti gli elementi a false
    vector<pair<bool,bool>> visited;
    visited.resize(vec.size(), make_pair(false,false));

    possibilities(vec, visited, 0);

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

void possibilities(vector<char> vec, vector<pair<bool,bool>>& visited, int shifted_position){
    //Considero la possibilità di dover calcolare un numero sia avanti che dietro
    possibilities_aus(vec, visited, 0, shifted_position);
    possibilities_aus(vec, visited, vec.size()-1, shifted_position);
}

void possibilities_aus(vector<char> vec, vector<pair<bool,bool>>& visited, int winning_position, int shifted_position){
    //Funzione ricorsiva core nella quale controlliamo se un elemento ad una posizione deve vincere, deve perdere, può vincere o può perdere

    //Controllo di non aver già considerato l'elemento in quella posizione
    if(hasntBeenVisited(visited, winning_position, shifted_position)){

        //Inseriamo la posizione che stiamo controllando nella lista di posizioni già controllate
        if(winning_position == 0){
            visited[winning_position+shifted_position].first = true;
        }else{
            visited[winning_position+shifted_position].second = true;
        }
        //Se l'elemento vince forzatamente viene aggiunto a res e terminiamo la funzione
        if(hasWon(vec, winning_position)){
            res[winning_position+shifted_position] = true;
        }else{
            //Controlliamo se il nostro elemento è falso e può vincere e in quel caso lo aggiungiamo in res
            if(!res[winning_position+shifted_position] && !hasLost(vec,winning_position)){
                res[winning_position+shifted_position] = true;
            }

            //Mandiamo la funzione in ricorsione per tutti gli elementi che possono prendere il posto del nostro elemento
            callrecursion(vec, visited, winning_position, shifted_position);
        }

    }
}

bool hasWon(vector<char> vec, int pos){
    //Funzione che controlla se l'elemento in pos è costretto a vincere
    //ovvero se vale la formula (*+s=0 ^ *+d%2=1+s=1) con elemento in prima pos oppure in modo analogo (d=0+* ^ d=1+s%2=1+*) con elemento in ultima pos
    if(vec.size() == 1){
        return true;
    }else{
        int num_element;
        int num_element_after;
        if(pos == 0){
            num_element = count_right(vec, pos, 'd');
            num_element_after = count_right(vec, pos+num_element, 's');
            if(num_element_after == 0 || (num_element_after == 1 && num_element%2 == 1)){
                return true;
            }
        }else{
            num_element = count_left(vec, pos, 's');
            num_element_after = count_left(vec, pos-num_element, 'd');
            if(num_element_after == 0 || (num_element_after == 1 && num_element%2 == 1)){
                return true;
            }
        }
        return false;
    }
}

bool hasLost(vector<char> vec, int pos){
    //Funzione che controlla se l'elemento in pos è costretto a perdere
    //ovvero se vale la formula (*+d=0+s%2=1) con elemento in prima pos oppure in modo analogo (d%2=1+s=0+*) con elemento in ultima pos
    if(pos == 0 && (count_right(vec,pos,'d') == 0 && max_num_contro(vec,pos,'s')%2 == 1)){
        return true;
    }else if(pos != 0 && (count_left(vec,pos,'s') == 0 && max_num_contro(vec,pos,'d')%2 == 1)){
        return true;
    }
    return false;
}

bool hasntBeenVisited(vector<pair<bool,bool>> visited, int winning_position, int shifted_position){
    if(winning_position == 0){
        return !visited[shifted_position].first;
    }else{
        return !visited[winning_position+shifted_position].second;
    }
}

void callrecursion(vector<char> vec, vector<pair<bool,bool>>& visited, int pos, int shifted_position){
    int counter_d = 0;
    int counter_s = 0;

    if(pos == 0){
        //Rimuovo il primo carattere che verrà perduto in qualsiasi caso e aggiorno il counter
        char first_character = vec.front();
        vec.erase(vec.begin());
        shifted_position += 1;

        //Adesso controllo per ogni elemento nell'array se può prendere il posto al bordo dell'array
        while(!vec.empty()){
            //Rimuovo il primo carattere e controllo se crea nuovi possibili elementi ai bordi e aggiorno il counter
            first_character = vec.front();
            vec.erase(vec.begin());
            shifted_position += 1;

            if(first_character == 's'){
                if(counter_s > 0){
                    counter_s -= 1;
                }else if(counter_d%2 == 0){
                    if(counter_d > 0){
                        counter_d -= 1;
                    }else{
                        counter_s += 1;
                    }
                    possibilities(vec, visited, shifted_position);
                }else if(counter_d%2 == 1){
                    counter_d -= 1;
                }
            }else{
                counter_d += 1;
                if(counter_d%2 == 0 && counter_s%2 == 1){
                    possibilities(vec, visited, shifted_position);
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
                    possibilities(vec, visited, shifted_position);
                }else if(counter_s%2 == 1){
                    counter_s -= 1;
                }
            }else{
                counter_s += 1;
                if(counter_d%2 == 1 && counter_s%2 == 0){
                    possibilities(vec, visited, shifted_position);
                }
            }
        }
    }
}


int count_left(vector<char> vec, int pos_iniziale, char carattere){
    //Funzione che ritorna il numero di elementi che puntano a sinistra rispetto alla posizione fornita
    int pos = pos_iniziale;
    while(pos-1 >= 0 && vec[pos-1] == carattere){
        pos -= 1;
    }
    return pos_iniziale - pos;
}

int count_right(vector<char> vec, int pos_iniziale, char carattere){
    //Funzione che ritorna il numero di elementi che puntano a destra rispetto alla posizione fornita
    int pos = pos_iniziale;
    while(pos+1 < (int)vec.size() && vec[pos+1] == carattere){
        pos += 1;
    }
    return pos - pos_iniziale;
}

int max_num_contro(vector<char> vec, int pos, char carattere){
    //Funzione che conta il massimo numero di elementi che vogliono battere l'elemento in posizione vincente
    int ris_max = 0;
    int ris_attuale = 0;
    if(pos == 0){
        pos += 1;
        //L'ultimo elemento non va considerato perchè non lo possiamo usare
        while(pos != (int)vec.size()-1){
            if(vec[pos] == carattere){
                ris_attuale += 1;
            }else{
                ris_attuale -= 1;
            }
            if(ris_max < ris_attuale){
                ris_max = ris_attuale;
            }
            pos += 1;
        }    
    }else{
        pos -= 1;
        //Il primo elemento non va considerato perchè non lo possiamo usare
        while(pos > 0){
            if(vec[pos] == carattere){
                ris_attuale += 1;
            }else{
                ris_attuale -= 1;
            }
            if(ris_max < ris_attuale){
                ris_max = ris_attuale;
            }
            pos -= 1;
        }
    }
    return ris_max;
}
