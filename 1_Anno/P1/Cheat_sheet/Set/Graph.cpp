#include <iostream>
#include <fstream>
#include "Graph.h"
using namespace std;

void init(graph& g, int number_of_nodes){
    g.number_of_nodes=number_of_nodes;
    g.adjMatrix = new int*[g.number_of_nodes];
    for(int i=0; i<g.number_of_nodes; i++){
        g.adjMatrix[i] = new int [g.number_of_nodes];
    }
}

void fill_graph(graph& g, const char* file_path){
    fstream input;
    input.open(file_path, ios::in);
    if(input.fail()){
        cerr<<"Error in file opening"<<endl;
        exit(2);
    }

    int number_of_nodes=0;
    input>>number_of_nodes;
    init(g, number_of_nodes);

    int element, dependences;
    while(input>>element>>dependences){
        if((element>=g.number_of_nodes)||(element<0)){
            cerr<<"Node not permitted"<<endl;
            exit(3);
        }else{
            g.adjMatrix[dependences][element]=1;
        }
    }
}

void print_graph(graph& g){
    for(int i=0; i<g.number_of_nodes; i++){
        cout<<i<<": ";
        for(int t=0; t<g.number_of_nodes; t++){
            if(i==t){
                cout<<" - ";
            }else{
                cout<<" "<<g.adjMatrix[t][i]<<" ";
            }
        }
        cout<<endl;
    }
}

void dependences(graph& g, int node){
    set s;
    init(s);
    for(int i=0; i<g.number_of_nodes; i++){
        if((g.adjMatrix[i][node]!=0)){
            insert(s, i);
        }
    }

    cout<<node<<" -> [";
    print_set(s);
    cout<<"]"<<endl;

    while(!(empty(s))){
        int value;
        cout<<"Inserire l'elemento da rimuovere: ";
        cin>>value;
        remove_element(s, value);
        shrink(s);
    }
    
    dealloc(s);
    dealloc(g);
}

void dealloc(graph& g){
    for(int i=0; i<g.number_of_nodes; i++){
        delete[] g.adjMatrix[i];
    }
    delete[] g.adjMatrix;
}


void init(set& s){
    s.arrayList= new int[s.buffer_length];
}

void insert(set& s, int value){
    if(full(s)){
        expand(s);
    }
    if(!(contains(s, value))){
        s.arrayList[s.current_size]=value;
        s.current_size++;
    }
}

void remove_element(set& s, int value){
    if(contains(s, value)){
        int i=0;
        while(contains(s, value)){
            if(s.arrayList[i]==value){
                while(i<(s.current_size-1)){
                    s.arrayList[i]=s.arrayList[i+1];
                    i++;
                }
                s.current_size--;
            }
            i++;
        }
        cout<<"Element "<<value<<" removed"<<endl;
    }else{
        cout<<"Inserted element not found"<<endl;
    }

}

bool contains(set& s, int value){
    bool exist=false;
    for(int i=0; i<s.current_size; i++){
        if(value==s.arrayList[i]){
            exist=true;
        }
    }
    return exist;
}

void expand(set& s){
    s.buffer_length*=2;
}

void shrink(set& s){
    if((float(s.current_size))<=(float(s.buffer_length))*(s.LOAD)){
        s.buffer_length=(float(s.buffer_length))/s.EXPANSION_FACTOR;
    }
}

bool empty(set& s){
    return (s.current_size==0);
}

bool full(set &s){
    return (s.current_size>=s.buffer_length);
}

void print_set(set& s){
    for(int i=0; i<s.current_size; i++){
        cout<<" "<<s.arrayList[i]<<" ";
    }
}

void dealloc(set& s){
    delete[] s.arrayList;
}