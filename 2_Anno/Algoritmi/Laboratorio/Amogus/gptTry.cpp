#include <bits/stdc++.h>
using namespace std;

struct Arco {
    int to;
    bool hasVentola;
    int ventolaId;
    int Tmin, Tmax;
};

int numNodi, M, K, I, S, F;
vector<vector<Arco>> grafo;
vector<int> ventoleValori; // valore corrente di ogni ventola
map<pair<int, int>, int> arcoToVentola;

struct StatoMontresus {
    int tempo;
    int nodo;
    unordered_map<int, int> ventoleUsate;

    bool operator>(const StatoMontresus& other) const {
        return tempo > other.tempo;
    }
};

int dijkstraStudenti(const vector<int>& ventoleFinali) {
    vector<int> dist(numNodi, INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

    dist[S] = 0;
    pq.emplace(0, S);

    while (!pq.empty()) {
        auto [tempo, nodo] = pq.top(); pq.pop();
        if (tempo > dist[nodo]) continue;

        for (const auto& arco : grafo[nodo]) {
            int costo;
            if (arco.hasVentola) {
                costo = ventoleFinali[arco.ventolaId];
            } else {
                costo = arco.Tmin;
            }

            if (dist[arco.to] > tempo + costo) {
                dist[arco.to] = tempo + costo;
                pq.emplace(dist[arco.to], arco.to);
            }
        }
    }
    return dist[F];
}

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    in >> numNodi >> M >> K >> I >> S >> F;

    grafo.resize(numNodi);
    ventoleValori.resize(K, -1);

    // Archi normali
    for (int i = 0; i < M; ++i) {
        int U, V, T;
        in >> U >> V >> T;
        grafo[U].push_back({V, false, -1, T, T});
    }

    // Archi con ventola
    for (int i = 0; i < K; ++i) {
        int U, V, Tmin, Tmax;
        in >> U >> V >> Tmin >> Tmax;
        grafo[U].push_back({V, true, i, Tmin, Tmax});
        arcoToVentola[{U, V}] = i;
        ventoleValori[i] = Tmin;
    }

    // Dijkstra per Montresus
    map<pair<int, unordered_map<int, int>>, int> visited;
    priority_queue<StatoMontresus, vector<StatoMontresus>, greater<>> pq;
    pq.push({0, I, {}});

    int bestTempoM = INT_MAX, bestTempoS = -1;
    vector<int> bestVentole;

    while (!pq.empty()) {
        StatoMontresus stato = pq.top(); pq.pop();

        if (stato.nodo == F) {
            // Crea ventoleFinali
            vector<int> ventoleFinali = ventoleValori;
            for (const auto& [id, val] : stato.ventoleUsate) {
                ventoleFinali[id] = val;
            }

            int tempoS = dijkstraStudenti(ventoleFinali);
            if (stato.tempo < tempoS) {
                if (stato.tempo < bestTempoM || 
                   (stato.tempo == bestTempoM && tempoS > bestTempoS)) {
                    bestTempoM = stato.tempo;
                    bestTempoS = tempoS;
                    bestVentole = ventoleFinali;
                }
            }
            continue;
        }

        for (const auto& arco : grafo[stato.nodo]) {
            if (!arco.hasVentola) {
                pq.push({stato.tempo + arco.Tmin, arco.to, stato.ventoleUsate});
            } else {
                // Opzione 1: passa con Tmin, non cambia la ventola
                pq.push({stato.tempo + arco.Tmin, arco.to, stato.ventoleUsate});

                // Opzione 2: passa con Tmax, aggiorna ventola
                auto nuovoStato = stato.ventoleUsate;
                nuovoStato[arco.ventolaId] = arco.Tmax;
                pq.push({stato.tempo + arco.Tmax, arco.to, nuovoStato});
            }
        }
    }

    // OUTPUT
    if (bestTempoM == INT_MAX) {
        // Nessuna strategia vincente
        int tempoS = dijkstraStudenti(ventoleValori);
        if (tempoS == INT_MAX) {
            out << "Error\n";
        } else {
            out << "2\n";
            out << tempoS << "\n";
            for (int v : ventoleValori) out << v << " ";
            out << "\n";
        }
    } else {
        out << "0\n"; // Montresus vince
        out << bestTempoM << " " << bestTempoS << "\n";
        for (int v : bestVentole) out << v << " ";
        out << "\n";
    }

    return 0;
}
