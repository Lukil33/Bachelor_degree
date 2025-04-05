#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

bool is_not_zero(vector<int>, int);
int position_first_not_null(vector<int>, int);

int main(){
    ifstream in ("input.txt");
    ofstream out ("output.txt");

    int len;
    in >> len;

    vector<int> vec;

    //Popolo il vettore
    for(int i=0; i<len; i++){
        int num;
        in >> num;
        vec.push_back(num);

        //Setto a 0 tutti i numeri già ordinati
        if(vec[i] == i+1){
            vec[i] = 0;
        }
    }

    //Inizializzo i miei contatori
    int num_mosse = 0;
    int costo = 0;
    int last_min_pos = 0;

    while(is_not_zero(vec, last_min_pos)){

        //Pusho sul ciclo la posizione del primo numero non nullo
        last_min_pos = position_first_not_null(vec, last_min_pos);

        //Inizializzo le variabili
        int actual_num = vec[last_min_pos];
        int smallest = vec[last_min_pos];
        int summ = 0;
        int num_mosse_temp = 0;

        //Sommo le cifre che incontro e tengo traccia del minimo
        //Il ciclo termina quando il valore da dover scambiare vale 0
        while(vec[actual_num-1] != 0){
            int actual_indice = actual_num-1;
            actual_num = vec[actual_num-1];
            summ += actual_num;
            
            if(actual_num < smallest){
                smallest = actual_num;
            }

            //Se il numero attuale non punta alla fine del ciclo aumento il numero di mosse di 1
            if(vec[actual_num-1] != 0){
                num_mosse += 1;
                num_mosse_temp += 1;
            }

            vec[actual_indice] = 0;
        }
        //Tolgo il numero più piccolo dalla somma per coprire gli edge cases
        summ -= smallest;

        //Calcolo della somma in base ai casi
        if(smallest*num_mosse_temp < (smallest+1)*2 + num_mosse_temp){
            costo += smallest*num_mosse_temp + summ;
        }else{
            costo += (smallest+1)*2 + num_mosse_temp + summ;
        }
    }

    //carico i risultati e termino il programma
    out << num_mosse << " " << costo;

    return 0;
}

bool is_not_zero(vector<int> vec, int start){
    //Controlla se la tupla è completamente formata da zero
    bool check = false;
    for(int i=0; i<(int)vec.size() && !check; i++){
        if(vec[i] != 0){
            check = true;
        }
    }
    return check;
}

int position_first_not_null(vector<int> vec, int start){
    //Trova la posizione del primo elemento non nullo
    int counter = start;
    while(vec[counter] == 0){
        counter ++;
    }
    return counter;
}