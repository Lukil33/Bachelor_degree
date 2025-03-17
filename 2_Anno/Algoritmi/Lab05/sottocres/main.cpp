#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void insert_in_order(vector<pair<int,int>>& DP, pair<int,int> elem){
    if(DP.empty()){
        //Se DP è vuoto semplicemente inserire elem
        DP.push_back(elem);
    }else{
        //Se DP ha degli elementi inserisco elem in modo ordinato
        int low = 0, high = DP.size()-1;

        while(low <= high){
            int mid = low + (high - low) / 2;

            if(DP[mid].second >= elem.second){
                low = mid + 1;
            }else{
                high = mid - 1;
            }
        }

        DP.insert(DP.begin()+low, elem);
    }
}

int main(){
    // Apri file input.txt
    ifstream fin("input.txt");
    int N = 0, v = 0;
    fin >> N;

    // Salva array
    vector<int> vec;
    vector<pair<int,int>> DP; // <OrginalNumber,ValueFromThatNumber>
    while (fin >> v){
        vec.push_back(v);
    }

    // Eseguo
    int MAX = 0;
    for(int elem : vec){
        bool check = false;
        
        //Controllo se ci sono valori più piccoli prima del valore appena selezionato
        for(int pos = 0; pos < (int)DP.size() && !check; pos++){
            //In caso affermativo seleziono il primo valore più piccolo che trovo
            if(elem > DP[pos].first){
                MAX = max(MAX, elem+DP[pos].second);
                insert_in_order(DP, make_pair(elem, elem+DP[pos].second));
                check = true;
            }
        }

        //Nel caso in cui non trovassi alcun elemento più piccolo lo aggiungo in maniera ordinata
        if(!check){
            insert_in_order(DP, make_pair(elem, elem));
            MAX = max(MAX, elem);
        }
    }

    // Apro file di output
    ofstream out("output.txt");
    out << MAX << endl;
}