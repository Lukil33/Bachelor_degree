#include <iostream>
#include <fstream>
using namespace std;

struct block{
    int number;
    block* left;
    block* right;
};

void create_list(block*& list, char* argv);
void print_list(block* list);
void print_reversed_list(block* list);
void delete_list(block*& list);

int main(int argc, char* argv[]){
    if(argc != 2){
        cerr<<"Error: ./a.out <input>"<<endl;
        return -1;
    }

    block* list;

    create_list(list, argv[1]);
    print_list(list);
    print_reversed_list(list);
    delete_list(list);

    return 0;
}

void create_list(block*& list, char* argv){
    fstream input;
    input.open(argv, ios::in);
    if(input.fail()){
        cerr<<"Error in file opening"<<endl;
        exit(1);
    }

    char word[100];
    while(input>>word){
        int number=atoi(word);
        block* created=new block{number, nullptr, nullptr};
        if(list==nullptr){
            list=created;
        }else{
            block* pointer=list;
            while(pointer->right!=nullptr){
                pointer=pointer->right;
            }
            pointer->right=created;
            created->left=pointer;
        }
    }
    input.close();
}

void print_list(block* list){
    cout<<"List right-> ";
    while(list!=nullptr){
        cout<<list->number<<" ";
        list=list->right;
    }
    cout<<endl;
}

void print_reversed_list(block* list){
    cout<<"List left-> ";
    while(list->right!=nullptr){
        list=list->right;
    }
    while(list!=nullptr){
        cout<<list->number<<" ";
        list=list->left;
    }
    cout<<endl;
}

void delete_list(block*& list){
    while(list->right!=nullptr){
        block* pointer=list;
        list=list->right;
        list->left=nullptr;
        delete pointer;
    }
    delete list;
}