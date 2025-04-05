#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// numCicli - numero di cicli totali
int N, numElementiVivi;
//VARIABILI PER LO SCRAPING
// Lista di adiacenza per il grafo
vector<vector<int>> graphFigli;
// Lista di adiacenza per il grafo inverso
vector<vector<int>> graphPadri;
// Numero puntatori padri dei nodi
vector<int> numIn;
//Numero puntatori figli dei nodi
vector<int> numOut;

//VARIABILI PER TROVARE I CICLI
// Controllo se i vari nodi sono già stati visitati
vector<bool> visited;
// Tiene traccia di dove sono passato nel grafo
vector<int> pila;

//VARIABILI PER LA CONCLUSIONE
//Vettore nel quale salverò il primo e secondo ciclo per le varie soluzioni
vector<vector<int>> cicli;

bool scrapingCicle(vector<int>, vector<int>, vector<int>);
int scraping(vector<int>&, vector<int>&, int);
void trovaCicli(vector<int>&, vector<int>&);
void conclusions();

int main(){
    ifstream in("input.txt");

    int M;
    in >> N >> M;
    numElementiVivi = N;

    //Setto le dimensioni per i vari vettori
    graphFigli.resize(N,vector<int>());
    graphPadri.resize(N,vector<int>());

    numIn.resize(N, 0);
    numOut.resize(N, 0);

    visited.resize(N,false);

    //Inserisco i nodi all'interno del grafo e li memorizzo
    for(int i=0; i<M; i++){
        int from, to;
        in >> from >> to;
        // Inserico il nodo nel grafo
        graphFigli[from].push_back(to);
        // Inserico il nodo nel grafo inverso
        graphPadri[to].push_back(from);

        numOut[from] +=1;
        numIn[to] +=1;
    }

    //Elimino i nodi che non fanno parte di un ciclo
    for(int i=0; i<N; i++){
        if((numIn[i] == 0 || numOut[i] == 0)){
            numElementiVivi -= scraping(numIn, numOut, i);
        }
    }
    
    //Trovo un primo ciclo
    trovaCicli(numIn, numOut);

    //Controllo se senza il ciclo trovato la componente connessa continua ad esistere
    conclusions();

    return 0;
}


//Funzione che elimina per tutti i nodi con 0 padri il nodo stesso e che diminuisce di 1 il contatore per i figli
int deleteFather(vector<int>& vettorePadri, vector<int>& vettoreFigli, int num){
    int res = 1;

    // ciclo per ogni figlio presente nella lista di adiacenza
    for(int i : graphFigli[num]){
        if(vettoreFigli[i] > 0){
            vettorePadri[i] -= 1;

            // Vado in ricorsione se il figlio non ha più padri
            if(vettorePadri[i] == 0){
                res += deleteFather(vettorePadri, vettoreFigli, i);
            }
        }
    }
    vettoreFigli[num] = 0;
    return res;
}
//Funzione che elimina per tutti i nodi con 0 figli il nodo stesso e che diminuisce di 1 il contatore per i padri
int deleteSon(vector<int>& vettorePadri, vector<int>& vettoreFigli, int num){
    int res = 1;

    // ciclo per ogni padre presente nella lista di adiacenza
    for(int i : graphPadri[num]){
        if(vettorePadri[i] > 0){
            vettoreFigli[i] -= 1;

            // Vado in ricorsions se il padre non ha più figli
            if(vettoreFigli[i] == 0){
                res += deleteSon(vettorePadri, vettoreFigli, i);
            }
        }
    }
    vettorePadri[num] = 0;
    return res;
}
int scraping(vector<int>& vettorePadri, vector<int>& vettoreFigli, int num){
    int res = 0;
    //Controllo se il nodo ha sia padri che figli
    if((vettorePadri[num] == -1 && vettoreFigli[num] == -1)||(graphPadri[num].size() == 0 && graphFigli[num].size() == 0)){
        vettorePadri[num] = 0;
        vettoreFigli[num] = 0;
        res += deleteFather(vettorePadri, vettoreFigli, num);
        res += deleteSon(vettorePadri, vettoreFigli, num);
        return res-1;
    }
    // Controllo se il nodo ha padri
    else if(vettorePadri[num] == 0 && vettoreFigli[num] != 0){
        res += deleteFather(vettorePadri, vettoreFigli, num);
    }
    // Controllo se il nodo ha figli
    else if(vettoreFigli[num] == 0 && vettorePadri[num] != 0){
        res += deleteSon(vettorePadri, vettoreFigli, num);
    }
    // per esclusione dei due casi precedenti il nodo ha padri e figli, non faccio nulla in quanto potrebbe avere un ciclo
    return res;
}
//Funzione che calcola se c'è o meno una soluzione, (1 si soluz, 0 no soluzione)
bool scrapingCicle(vector<int> vettorePadri, vector<int> vettoreFigli, vector<int> ciclo){
    for(int i:ciclo){
        vettoreFigli[i] = -1;
        vettorePadri[i] = -1;
    }
    int res = 0;
    for(int i:ciclo){
        res += scraping(vettorePadri,vettoreFigli,i);
    }

    if(numElementiVivi == res){
        return true;
    }

    trovaCicli(vettorePadri, vettoreFigli);
    return false;
}
int scrapingSingleNode(vector<int> vettorePadri, vector<int> vettoreFigli, int nodo){
    vettoreFigli[nodo] = -1;
    vettorePadri[nodo] = -1;
    
    int res = scraping(vettorePadri,vettoreFigli,nodo);

    return res == numElementiVivi;
}


void aumentaCiclo(int num){
    // Inizializzo le variabili
    cicli.push_back({});
    bool isACicle = true;

    // Finchè il nodo pila[i] non è uguale all'inizio memorizzo gli elementi e torno indietro
    while(!pila.empty()){
        // Se non ho ancora trovato l'inizio del ciclo aggiungo l'ultimo elemento e lo rimuovo dalla pila
        if(isACicle){
            cicli[cicli.size()-1].push_back(pila.back());
            if(pila.back() == num){
                isACicle = false;
            }
        }

        // Svuoto pila e setto visited completamente a false
        visited[pila.back()] = false;
        pila.pop_back();
    }
}
void trovacicli_aux(vector<int>& vettorePadri, vector<int>& vettoreFigli, int nodoAttuale){
    // Segno la posizione attuale come visitata
    visited[nodoAttuale] = true;
    pila.push_back(nodoAttuale);

    // Ciclo per ogni figlio di nodoAttuale
    for(int i: graphFigli[nodoAttuale]){
        if(vettorePadri[i] != 0 && vettoreFigli[i] != 0){
            // Se ho già visitato il nodo figlio allora sono in un ciclo
            if(visited[i]){
                // Aumento il cicliPassanti per le posizioni da nodoAttuale ad i
                return aumentaCiclo(i);
            }else{
                // Altrimenti vado in ricorsione sul figlio
                return trovacicli_aux(vettorePadri, vettoreFigli, i);
            }
        }
    }
}
void trovaCicli(vector<int>& vettorePadri, vector<int>& vettoreFigli){
    int i = 0;
    // Salto eventuali nodi eliminati
    while(vettorePadri[i] == 0 || vettoreFigli[i] == 0){
        i++;
    }
    // Entro nel primo nodo che sicuramente ha un ciclo
    trovacicli_aux(vettorePadri, vettoreFigli, i);
}


void printWin(int number){
    //Funzione che stampa tutte le informazioni necessarie per il risultato possibile
    ofstream out("output.txt");
    out << number << endl;

    //Stampo il nodo vincitore ed il ciclo nel quale questo è presente
    out << cicli[0].size();
    for(int i = (int)cicli[0].size()-1; i>=0 ;i--){
        out << " " << cicli[0][i];
    }
}
void printLost(){
    //Funzione che stampa tutte le informazioni necessarie per un risultato non possibile
    ofstream out("output.txt");
    out << -1 << endl;

    //Prendo come nodo di partenza il primo del ciclo e successivamente vi inserisco il ciclo
    out << cicli[0][cicli[0].size()-1] <<endl;
    out << cicli[0].size();
    for(int i = (int)cicli[0].size()-1; i>=0 ;i--){
        out << " " << cicli[0][i];
    }
    out << endl;

    //Inserisco successivamente il secondo ciclo trovato in precedenza
    out << cicli[1].size();
    for(int i = (int)cicli[1].size()-1; i>=0 ;i--){
        out << " " << cicli[1][i];
    }
}
void conclusions(){
    //Controllo se il ciclo contiene la soluzione
    if(scrapingCicle(numIn, numOut, cicli[0])){
        //Setto la posizione dell'ultimo elemento
        int max = (int)cicli[0].size()-1;
        while(max >= 0 && (numIn[cicli[0][max]] <= 1 && numOut[cicli[0][max]] <= 1)){
            max -= 1;
        } 
        
        //Controllo se il ciclo ha entrate o uscite, in caso negativo la risposta è un qualsiasi elemento del ciclo
        if(max < 0){
            printWin(cicli[0][cicli[0].size()-1]);

        }else{
            //Ciclo per ogni elemento che contiene più nodi figli o padri
            bool valid = false;

            int res = 0;
            for(int i=0; i<max && !valid; i++){
                if(numIn[cicli[0][i]] > 1 || numOut[cicli[0][i]] > 1){
                    valid = scrapingSingleNode(numIn, numOut, cicli[0][i]);
                    if(valid){
                        res = cicli[0][i];
                    }
                }
            }

            if(valid){
                printWin(res);
            }else{
                printWin(cicli[0][max]);
            }
        }
    }else{
        printLost();
    }
}