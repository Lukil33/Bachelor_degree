using namespace std;
#include<iostream>
#include<fstream>
#include<vector>
#include<queue>

vector<vector<int>> graph;
vector<vector<int>> distances;
vector<int> normaldist;
vector<int> dads;
int N,M,powarts;

int finddads(){
    vector<bool> visited;
    vector<int> kids;
    visited.resize(N,false);
    kids.resize(N,0);
    queue<int> q;

    q.push(powarts);
    visited[powarts]=true;
    while(!q.empty()){
        int pos=q.front();
        q.pop();

        vector<int> mydads;
        int candidatedad=-1;
        for(int i=0;i<graph[pos].size();i++){
            int c=graph[pos][i];

            if(normaldist[pos]==normaldist[c]+distances[pos][i]){//if c is my dad
                if(c!=powarts){
                    mydads.push_back(c);
                    //cout<<"node "<<pos<<" has dad "<<c<<endl;
                }
            }else if(normaldist[pos]+distances[pos][i]==normaldist[c] && !visited[c]){// if c is my son and also hasnt been visited
                q.push(c);
                visited[c]=true;
            }
        }


        bool multipledads=false;
        if(pos!=powarts){
            if(mydads.size()==0){
                candidatedad=pos;
            }else if(mydads.size()==1){
                candidatedad=(dads[mydads[0]]!=-1) ? dads[mydads[0]] : mydads[0];
            }else if(mydads.size()>1){
                candidatedad=dads[mydads[0]];
                for(int i=0;i<mydads.size();i++){
                    if(dads[mydads[i]]!=candidatedad){
                        multipledads=true;
                    }
                }
            }

            if(!multipledads){
                dads[pos]=candidatedad;
            }else{
                dads[pos]=pos;
            }
            kids[dads[pos]]++;
        }


    }

    int max=0;
    for(int i=0;i<N;i++){
        if(kids[i]>=kids[max]){
            max=i;
        }
    }

    return max;
}

int blockedstudents(vector<vector<int>> newgraph,int voldemort,vector<int> &blocked){
    if(voldemort==powarts) return -2;

    vector<int> newdist;
    newdist.resize(N,-1);

    newgraph[voldemort]={};


    queue<int> q;
    newdist[powarts]=0;
    q.push(powarts);
    while(!q.empty()){
        int pos=q.front();
        q.pop();

        for(int i=0;i<newgraph[pos].size();i++){
            int d=newdist[pos]+distances[pos][i];

            if(newdist[graph[pos][i]]==-1 || newdist[graph[pos][i]]>d){
                newdist[graph[pos][i]]=d;
                q.push(graph[pos][i]);
                //cout<<"node "<<pos<<" giving node "<<graph[pos][i]<<" newdist= "<<d<<endl;
            }
        }
    }

    //cout<<endl;

    int result=0;

    for(int i=0;i<graph.size();i++){
        //cout<<i<<": "<<newdist[i]<<endl;
        if(i==voldemort || normaldist[i]!=newdist[i]){
            result++;
            blocked.push_back(i);
        }
    }

    return result;
}

int main(){
    //Come puoi ben notare il codice non è il mio, ho risolto l'es con il Boss e il codice lo ha poi scritto lui
    ifstream in("input.txt");

    in>>N>>M>>powarts;

    vector<int> newdist;

    graph.resize(N);
    distances.resize(N);
    normaldist.resize(N,-1);
    newdist.resize(N,-1);
    dads.resize(N,-1);

    for(int i=0;i<M;i++){
        int node1,node2,dist;
        in>>node1>>node2>>dist;

        graph[node1].push_back(node2);
        graph[node2].push_back(node1);

        distances[node1].push_back(dist);
        distances[node2].push_back(dist);
    }

    queue<int> q;
    normaldist[powarts]=0;
    q.push(powarts);
    while(!q.empty()){
        int pos=q.front();
        q.pop();

        for(int i=0;i<graph[pos].size();i++){
            int d=normaldist[pos]+distances[pos][i];

            if(normaldist[graph[pos][i]]==-1 || normaldist[graph[pos][i]]>d){
                normaldist[graph[pos][i]]=d;
                q.push(graph[pos][i]);
                //cout<<"node "<<pos<<" giving node "<<graph[pos][i]<<" normaldist= "<<d<<endl;
            }
        }
    }

    int v=finddads();

    vector<int> bloccati;
    int max=blockedstudents(graph,v,bloccati);

    ofstream out("output.txt");
    out<<max;
    for(int i=0;i<bloccati.size();i++){
        out<<endl<<bloccati[i];
    }
}