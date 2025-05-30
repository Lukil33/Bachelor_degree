#include <iostream>
using namespace std;

struct block{
    int number;
    block* next;
};

void insert_number(block*& list);
void ordinate_insert(block*& list, block* pointer, block* back_pointer, int number);

void print(block* list);
void print_A(block* list);

void delete_list(block*& list);

int main(){
    block* list;
    insert_number(list);
    delete_list(list);
    return 0;
}

void insert_number(block*& list){
    int number;
    cout<<"Insert a number: ";
    cin>>number;

    block* pointer=list;
    block* back_pointer=nullptr;
    ordinate_insert(list, pointer, back_pointer, number);
    print(list);

    char letter;
    cout<<"Do you want to continue?(Y/N): ";
    cin>>letter;
    if(letter=='y'||letter=='Y'){
        insert_number(list);
    }else{
        return;
    }
}
void ordinate_insert(block*& list, block* pointer, block* back_pointer, int number){
    if((pointer!=nullptr) && (number)>=(pointer->number)){
        ordinate_insert(list, pointer->next, pointer, number);
    }else{
        block* created=new block{number, pointer};
        if(back_pointer != nullptr){
            back_pointer->next=created;
        }else{
            list=created;
        }
    }
    
}

void print(block* list){
    cout<<"List-> ";
    print_A(list);
    cout<<endl;
}
void print_A(block* list){
    if(list != nullptr){
        cout<<list->number<<" ";
        print_A(list->next);
    }
}

void delete_list(block*& list){
    if(list != nullptr){
        block* pointer=list;
        list=list->next;
        delete[] pointer;
        delete_list(list);
    }else{
        delete[] list;
    }
}