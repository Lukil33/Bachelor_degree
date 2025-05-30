#include <iostream>
#include <fstream>
using namespace std;

float * lista_temperature(int N, int M, char * argv[]);
void ordina_array(float * temperature, int S, int l);
void controllo_ordine(float * temperature, int S, bool & ordinato);

void stampa_valori_maggiori(float * temperature, int N);

int main(int argc, char* argv[]){
    int N = atoi(argv[2]);
    int M = atoi(argv[3]);

    if(argc>4){
        cerr<<"Hai inserito troppi valori"<<endl;
        return -1;
    }

    float * temperature = lista_temperature(N, M, argv);

    stampa_valori_maggiori(temperature, N);
    
    delete[] temperature;
    return 0;
}

float * lista_temperature(int N, int M, char * argv[]){
    float * temperature = new float [M];
    fstream input;
    input.open(argv[1], ios::in);
    char parola[6];
    while((input>>parola)&&(M>0)){
        M--;
        temperature[M] = atof(parola);
    }
    
    int S=atoi(argv[3])-M, l=0;
    ordina_array(temperature, S, l);
    
    return temperature;
}

void ordina_array(float * temperature, int S, int l){
    bool ordinato=true;
    controllo_ordine(temperature, S, ordinato);
    if((ordinato==true)){
    }else{
        if(l<=0){
            l=S-1;
        }
        if(temperature[l]>temperature[l-1]){
            temperature[l]+=temperature[l-1];
            temperature[l-1]=temperature[l]-temperature[l-1];
            temperature[l]-=temperature[l-1];
        }
        l--;
        ordina_array(temperature, S, l);
    }
}

void controllo_ordine(float * temperature, int S, bool & ordinato){
    int v=0;
    while((ordinato==true)&&(v+1<S)){
        if(temperature[v]<temperature[v+1]){
            ordinato=false;
        }
        v++;
    }
}

void stampa_valori_maggiori(float * temperature, int N){
    for(int i=0; i<N; i++){
        cout<<temperature[i]<<endl;
    }
}