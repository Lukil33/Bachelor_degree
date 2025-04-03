using namespace std;
#include<fstream>
#include<vector>
#include<queue>

vector<vector<int>> graph;
vector<vector<int>> reversegraph;
vector<bool> visited;


int componentsize(int start){
    vector<bool> reachablenormal; 
    vector<bool> reachablereverse;

    reachablenormal.resize(graph.size(),false);
    reachablereverse.resize(graph.size(),false);

    queue<int> q;

    q.push(start);
    reachablenormal[start]=true;

    while(!q.empty()){
        int pos=q.front();
        q.pop();

        for(int adj : graph[pos]){
            if(!reachablenormal[adj]){
                reachablenormal[adj]=true;
                q.push(adj);
            }
        }
    }

    q.push(start);
    reachablereverse[start]=true;

    while(!q.empty()){
        int pos=q.front();
        q.pop();

        for(int adj : reversegraph[pos]){
            if(!reachablereverse[adj]){
                reachablereverse[adj]=true;
                q.push(adj);
            }
        }
    }

    int size=0;
    for(int i=0;i<graph.size();i++){
        if(reachablenormal[i] && reachablereverse[i]){
            size++;
            visited[i]=true;
        }
    }

    return size;
}


int main(){
    int N,M;

    ifstream in("input.txt");

    in>>N>>M;

    graph.resize(N);
    reversegraph.resize(N);

    for(int i=0;i<M;i++){
        int a,b;
        in>>a>>b;
        graph[a].push_back(b);
        reversegraph[b].push_back(a);
    }

    visited.resize(N,false);
    int maxsize=0;

    for(int i=0;i<N;i++){
        if(!visited[i]){
            maxsize=max(maxsize,componentsize(i));
        }
    }

    ofstream out("output.txt");
    out<<maxsize;
}