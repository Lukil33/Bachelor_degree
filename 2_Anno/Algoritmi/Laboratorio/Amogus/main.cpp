#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=a; i<b; i++)
using namespace std;

vector<vector<vector<int>>> listaAdiacenza;
vector<int> valVentole;
map<pair<int,int>,int> arcoToVentole;
set<int> disposableTime;
map<int,set<int>> timeToNode;
map<int,tuple<bool,bool,int>> nodeToTime; // tuple definition: (cattivo, buono, tempo di attivazione)
int numNodi,I,S,F;

void changeValue(int,int,int);
int findVentola(int,int);

int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");

    int M,K;

    in>>numNodi>>M>>K>>I>>S>>F;
    listaAdiacenza.resize(numNodi);
    valVentole.resize(K, -1);

    rep(i,0,M){
        int U,V,T;
        in>>U>>V>>T;
        vector<int> collegamento = {V,T};
        listaAdiacenza[U].push_back(collegamento);
    }

    rep(i,0,K){
        int U,V,Tmin,Tmax;
        in>>U>>V>>Tmin>>Tmax;
        vector<int> colleg;
        if(Tmin == Tmax){
            colleg = {V,Tmin};
        }else{
            colleg = {V,Tmin,Tmax};
        }
        valVentole[i] = Tmin;
        arcoToVentole[{U,V}] = i;
        listaAdiacenza[U].push_back(colleg);
    }
    
    int time = 0;
    timeToNode[0].insert(I);
    nodeToTime[I] = {true,false,0};
    timeToNode[0].insert(S);
    nodeToTime[S] = {false,true,0};
    disposableTime.insert(time);
    bool finito = false;
    while(!finito){
        time = *(disposableTime.begin());

        // Debugging
        //cout<<"T -> "<<time<<endl;

        for(int nodoPrec : timeToNode[time]){

            // Debugging
            //cout<<"Nodo consid -> "<<nodoPrec<<" <"<<get<0>(nodeToTime[nodoPrec])<<", "<<get<1>(nodeToTime[nodoPrec])<<", "<<get<2>(nodeToTime[nodoPrec])<<">"<<endl;

            if(nodoPrec == F){
                // Ricordati di non mettere alcun break, ci potrebbero essere casi di pareggio finale
                finito = true;
            }else{
                for(vector<int> nodo : listaAdiacenza[nodoPrec]){
                    //Assegnazione costo
                    if(nodo.size() == 3){
                        if(get<0>(nodeToTime[nodoPrec]) && get<1>(nodeToTime[nodoPrec])){
                            changeValue(nodoPrec, nodo[0], time + nodo[2]);
                            valVentole[findVentola(nodoPrec,nodo[0])] = nodo[2];
                        }else if(get<0>(nodeToTime[nodoPrec])){
                            changeValue(nodoPrec, nodo[0], time + nodo[1]);
                        }else{
                            changeValue(nodoPrec, nodo[0], time + nodo[2]);
                            valVentole[findVentola(nodoPrec,nodo[0])] = nodo[2];
                        }
                    }else{
                        changeValue(nodoPrec, nodo[0], time + nodo[1]);
                    }
                }
            }
        }
        disposableTime.erase(time);
    }

    switch(get<0>(nodeToTime[F])*10+get<1>(nodeToTime[F])){
        case 1: out<<2; break;
        case 10: out<<1; break;
        case 11: out<<0; break;
        default: out<<"Error"; break;
    }
    out<<endl;

    if(get<0>(nodeToTime[F]) && get<1>(nodeToTime[F])){
        out<<get<2>(nodeToTime[F])<<" "<<get<2>(nodeToTime[F])<<endl;
    }else{
        out<<get<2>(nodeToTime[F])<<endl;
    }

    rep(i,0,(int)valVentole.size()){
        out<<valVentole[i]<<" ";
    }
    out<<endl;

    return 0;
}

int findVentola(int nodoPrec, int nodoSucc){
    return arcoToVentole[{nodoPrec,nodoSucc}];
}

void changeValue(int nodoPrec, int nodoSucc, int tempo){
    if(nodeToTime.find(nodoSucc) == nodeToTime.end()){
        nodeToTime[nodoSucc] = {get<0>(nodeToTime[nodoPrec]),get<1>(nodeToTime[nodoPrec]),tempo};
        timeToNode[tempo].insert(nodoSucc);
        disposableTime.insert(tempo);
    }else if(get<2>(nodeToTime[nodoSucc]) > tempo){
        timeToNode[get<2>(nodeToTime[nodoSucc])].erase(nodoSucc);
        if(timeToNode[get<2>(nodeToTime[nodoSucc])].size() == 0){
            disposableTime.erase(get<2>(nodeToTime[nodoSucc]));
        }
        nodeToTime[nodoSucc] = {get<0>(nodeToTime[nodoPrec]),get<1>(nodeToTime[nodoPrec]),tempo};
        timeToNode[tempo].insert(nodoSucc);
        disposableTime.insert(tempo);
    }else if(get<2>(nodeToTime[nodoSucc]) == tempo){
        nodeToTime[nodoSucc] = {get<0>(nodeToTime[nodoPrec]) + get<0>(nodeToTime[nodoSucc]), get<1>(nodeToTime[nodoPrec]) + get<1>(nodeToTime[nodoSucc]), tempo};
    }
}