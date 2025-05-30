#include <iostream>
using namespace std;
#define DIM 5

struct block{
    int column;
    int row;
    block* next;
};

void create_matrix(int matrix[DIM][DIM]);
void start_and_end(int matrix[DIM][DIM], int start[2], int end[2]);
bool find_a_path(block*& pile, int matrix[DIM][DIM],int start[2], int end[2]);
bool recursive(block*& pile, int matrix[DIM][DIM], int end[2]);
bool repetition(block* pile);

int main(){
    srand(time(NULL));
    block* pile = nullptr;
    int matrix[DIM][DIM];
    create_matrix(matrix);
    int start[2], end[2];
    start_and_end(matrix, start, end);
    if(find_a_path(pile, matrix, start, end)){
        cout<<"Passaggio trovato"<<endl;
    }else{
        cout<<"Non esistono passaggi"<<endl;
    }
    return 0;
}

void create_matrix(int matrix[DIM][DIM]){
    for(int i=0; i<DIM; i++){
        for(int g=0; g<DIM; g++){
            matrix[i][g]=rand()%2;
            cout<<matrix[i][g]<<" ";
        }
        cout<<endl;
    }
}

void start_and_end(int matrix[DIM][DIM], int start[2], int end[2]){
    cout<<endl;
    do{
        cout<<"Inserire le coordinate del punto di partenza (colonna, riga): "<<endl;
        cin>>start[0];
        cin>>start[1];
        if((start[0]>4||start[0]<0)||(start[1]>4||start[1]<0)){
            cout<<"Le coordinate inserite non rispettano i limiti imposti"<<endl;
        }
        if(matrix[start[0]][start[1]] == 1){
            cout<<"Nella matrice la cella "<<start[0]<<"-"<<start[1]<<" rappresenta un muro"<<endl;
        }
    }while((start[0]>4||start[0]<0)||(start[1]>4||start[1]<0)||(matrix[start[0]][start[1]]==1));
    cout<<endl;
    do{
        cout<<"Inserire le coordinate del punto da raggiungere (colonna, riga): "<<endl;
        cin>>end[0];
        cin>>end[1];
        if((end[0]>4||end[0]<0)||(end[1]>4||end[1]<0)){
            cout<<"Le coordinate inserite non rispettano i limiti imposti"<<endl;
        }
        if(matrix[end[0]][end[1]] == 1){
            cout<<"Nella matrice la cella "<<end[0]<<"-"<<end[1]<<" rappresenta un muro"<<endl;
        }
    }while((end[0]>4||end[0]<0)||(end[1]>4||end[1]<0)||(matrix[end[0]][end[1]]==1));
}

bool find_a_path(block*& pile, int matrix[DIM][DIM],int start[2], int end[2]){
    block* created=new block{start[0], start[1], nullptr};
    pile=created;
    return recursive(pile, matrix, end);
}

bool recursive(block*& pile, int matrix[DIM][DIM], int end[2]){
    int colonna=pile->column;
    int riga=pile->row;
    if(repetition(pile)||(matrix[colonna][riga] == 1)){
        return 0;
    }
    if((colonna == end[0])&&(riga == end[1])){
        return 1;
    }
    if(colonna-1>=0){
        block* created = new block{colonna-1, riga, pile};
        pile=created;
        if(recursive(pile, matrix, end)){
            return 1;
        }else{
            block* pointer=pile;
            pile=pile->next;
            delete[] pointer;
        }
    }
    if(colonna+1<DIM){
        block* created = new block{colonna+1, riga, pile};
        pile=created;
        if(recursive(pile, matrix, end)){
            return 1;
        }else{
            block* pointer=pile;
            pile=pile->next;
            delete[] pointer;
        }
    }
    if(riga-1>=0){
        block* created = new block{colonna, riga-1, pile};
        pile=created;
        if(recursive(pile, matrix, end)){
            return 1;
        }else{
            block* pointer=pile;
            pile=pile->next;
            delete[] pointer;
        }
    }
    if(riga+1<DIM){
        block* created = new block{colonna, riga+1, pile};
        pile=created;
        if(recursive(pile, matrix, end)){
            return 1;
        }else{
            block* pointer=pile;
            pile=pile->next;
            delete[] pointer;
        }
    }
    return 0;
}

bool repetition(block* pile){
    int colonna=pile->column;
    int riga=pile->row;
    pile=pile->next;
    while(pile != nullptr){
        if((pile->column == colonna)&&(pile->row == riga)){
            return 1;
        }
        pile=pile->next;
    }
    return 0;
}