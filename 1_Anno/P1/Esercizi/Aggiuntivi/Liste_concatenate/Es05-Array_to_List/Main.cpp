#include <iostream>
#include <fstream>
using namespace std;
#define DIM 10

struct block{
    int number;
    block* next;
};

void create_array(int* array, char* argv);
void create_list(block*& list, int* array);
void print_list(block* list);
void delete_list(block*& list);

int main(int argc, char* argv[]){
    if(argc != 2){
        cerr<<"Error: ./a.out <input_file>"<<endl;
        return -1;
    }
    int array[DIM];
    block* list;
    create_array(array, argv[1]);
    create_list(list, array);
    print_list(list);
    delete_list(list);
    return 0;
}

void create_array(int* array, char* argv){
    fstream input;
    input.open(argv, ios::in);

    char word[100];
    int i=0;
    cout<<"Array-> ";
    while(input>>word){
        int num=atoi(word);
        array[i]=num;
        cout<<array[i]<<" ";
        i++;
    }
    cout<<endl;

    input.close();
}

void create_list(block*& list, int* array){
    for(int i=0; i<DIM; i++){
        block* created=new block{array[i], nullptr};
        if(i==0){
            list=created;
        }else{
            block* pointer=list;
            while(pointer->next!=nullptr){
                pointer=pointer->next;
            }
            pointer->next=created;
        }
    }
}

void print_list(block* list){
    cout<<"List-> ";
    while(list != nullptr){
        cout<<list->number<<" ";
        list=list->next;
    }
    cout<<endl;
}

void delete_list(block*& list){
    while(list != nullptr){
        block* pointer=list;
        list=list->next;
        delete[] pointer;
    }
    delete[] list;
}