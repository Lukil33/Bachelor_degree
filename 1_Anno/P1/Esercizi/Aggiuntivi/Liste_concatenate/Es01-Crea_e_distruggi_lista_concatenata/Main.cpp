#include <iostream>
#include <fstream>
using namespace std;

struct cella{
    int number;
    cella* next;
};

void crea_lista(cella*& lista, char* argv);
void stampa_lista(cella* lista);
void stampa_lista_ricorsiva(cella* lista);
void elimina_lista(cella*& lista);

int main(int argc, char* argv[]){
    if(argc != 2){
        cerr<<"Error: ./a.out <input_file>"<<endl;
        return -1;
    }

    cella* lista;

    crea_lista(lista, argv[1]);

    stampa_lista(lista);

    cout<<"Lista ricorsiva: ";
    stampa_lista_ricorsiva(lista);
    cout<<endl;

    elimina_lista(lista);
    return 0;
}

void crea_lista(cella*& lista, char* argv){
    fstream input;
    input.open(argv, ios::in);
    if(input.fail()){
        cerr<<"Error during file opening"<<endl;
        exit(1);
    }

    char word[100];
    while(input>>word){
        int number=atoi(word);
        cella* created= new cella{number, nullptr};
        if(lista==nullptr){
            lista=created;
        }else{
            cella* pointer=lista;
            while(pointer->next!=nullptr){
                pointer=pointer->next;
            }
            pointer->next=created;
        }
    }
    input.close();
}

void stampa_lista(cella* lista){
    cout<<"Lista iterativa: ";
    if(lista==nullptr){
        cout<<"Vuota";
    }else{
        while(lista!=nullptr){
            cout<<lista->number<<" ";
            lista=lista->next;
        }
    }
    cout<<endl;
}

void stampa_lista_ricorsiva(cella* lista){
    if(lista!=nullptr){
        cout<<lista->number<<" ";
        stampa_lista_ricorsiva(lista->next);
    }
}

void elimina_lista(cella*& lista){
    while(lista!=nullptr){
        cella* pointer=lista;
        lista=lista->next;
        delete[] pointer;
    }
}