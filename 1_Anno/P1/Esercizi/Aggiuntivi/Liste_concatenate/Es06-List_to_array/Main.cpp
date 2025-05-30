#include <iostream>
#include <fstream>
using namespace std;
#define DIM 10

struct block{
    int number;
    block* next;
};

void create_list(block*& list, char* argv);
void print_list(block* list);
void create_array(block* list, int* array);
void delete_list(block*& list);

int main(int argc, char* argv[]){
    if(argc != 2){
        cerr<<"Error: ./a.out <input_file>"<<endl;
        return -1;
    }
    int array[DIM];
    block* list;
    create_list(list, argv[1]);
    print_list(list);
    create_array(list, array);
    delete_list(list);
    return 0;
}

void create_list(block*& list, char* argv){
    fstream input;
    input.open(argv, ios::in);

    char word[255];
    while(input>>word){
        int number=atoi(word);
        block* created=new block{number, nullptr};
        if(list == nullptr){
            list=created;
        }else{
            block* pointer=list;
            while(pointer->next != nullptr){
                pointer=pointer->next;
            }
            pointer->next=created;
        }
    }

    input.close();
}

void print_list(block* list){
    cout<<"List-> ";
    while(list != nullptr){
        cout<<list->number<<" ";
        list=list->next;
    }
    cout<<endl;
}

void create_array(block* list, int* array){
    int i=0;
    cout<<"Array-> ";
    while(list != nullptr){
        array[i]=list->number;
        cout<<array[i]<<" ";
        i++;
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