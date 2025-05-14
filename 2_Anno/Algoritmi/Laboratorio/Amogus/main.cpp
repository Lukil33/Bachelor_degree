#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=a; i<b; i++)
using namespace std;

struct nodeInformation{
    bool montresus;
    bool students;
    int activationTime;
};

vector<vector<vector<int>>> listaAdiacenza;
vector<int> valVentole;
map<pair<int,int>,int> arcoToVentole;
set<int> disposableTime;
map<int,set<int>> timeToNode;
map<int,vector<nodeInformation>> nodeToTime; // tuple definition: (cattivo, buono, tempo di attivazione)
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
    nodeToTime[I].push_back({true,false,0});
    timeToNode[0].insert(S);
    nodeToTime[S].push_back({false,true,0});
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
                        if(nodeToTime[nodoPrec].montresus && nodeToTime[nodoPrec].students){
                            changeValue(nodoPrec, nodo[0], time + nodo[2]);
                            valVentole[findVentola(nodoPrec,nodo[0])] = nodo[2];
                        }else if(nodeToTime[nodoPrec].montresus){
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

    // Print
    switch(nodeToTime[F].montresus*10+nodeToTime[F].students){
        case 1: out<<2; break;
        case 10: out<<1; break;
        case 11: out<<0; break;
        default: out<<"Error"; break;
    }
    out<<endl;

    if(nodeToTime[F].montresus && nodeToTime[F].students){
        out<<nodeToTime[F].activationTime<<" "<<nodeToTime[F].activationTime<<endl;
    }else if(nodeToTime[F].montresus){
        out<<nodeToTime[F].activationTime<<" "<<otherTime()<<endl;
    }else{
        out<<otherTime()<<" "<<nodeToTime[F].activationTime<<endl;
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
        nodeToTime[nodoSucc] = {nodeToTime[nodoPrec].montresus,nodeToTime[nodoPrec].students,tempo};
        timeToNode[tempo].insert(nodoSucc);
        disposableTime.insert(tempo);
    }else if(nodeToTime[nodoSucc].activationTime > tempo){
        timeToNode[nodeToTime[nodoSucc].activationTime].erase(nodoSucc);
        if(timeToNode[nodeToTime[nodoSucc].activationTime].size() == 0){
            disposableTime.erase(nodeToTime[nodoSucc].activationTime);
        }
        nodeToTime[nodoSucc] = {nodeToTime[nodoPrec].montresus,nodeToTime[nodoPrec].students,tempo};
        timeToNode[tempo].insert(nodoSucc);
        disposableTime.insert(tempo);
    }else if(nodeToTime[nodoSucc].activationTime == tempo){
        nodeToTime[nodoSucc] = {nodeToTime[nodoPrec].montresus || nodeToTime[nodoSucc].montresus, nodeToTime[nodoPrec].students || nodeToTime[nodoSucc].students, tempo};
    }
}