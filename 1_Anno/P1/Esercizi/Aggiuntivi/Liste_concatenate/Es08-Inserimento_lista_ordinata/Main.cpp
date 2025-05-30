#include <iostream>
using namespace std;

struct block{
    int number;
    block* next;
};

void insert_number(block*& list);
void ordinate_insert(block*& list, int number);
void print(block* list);
void delete_list(block*& list);

int main(){
    block* list;
    insert_number(list);
    delete_list(list);
    return 0;
}

void insert_number(block*& list){
    char letter;
    do{
        int number;
        cout<<"Insert a number: ";
        cin>>number;

        ordinate_insert(list, number);
        print(list);

        cout<<"Do you want to continue?(Y/N): ";
        cin>>letter;
    }while(letter=='y'||letter=='Y');
}

void ordinate_insert(block*& list, int number){
    block* pointer=list;
    block* back_pointer=nullptr;
    while((pointer!=nullptr) && (number)>=(pointer->number)){
        back_pointer=pointer;
        pointer=pointer->next;
    }
    block* created=new block{number, pointer};
    if(back_pointer != nullptr){
        back_pointer->next=created;
    }else{
        list=created;
    }
}

void print(block* list){
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