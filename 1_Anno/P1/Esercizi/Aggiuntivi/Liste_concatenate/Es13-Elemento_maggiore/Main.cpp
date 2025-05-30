#include <iostream>
using namespace std;

struct block{
    int number;
    block* next;
};

void create_list(block*& list);
void print_list(block* list);
block* larger_element(block* list);
int element(block* list);
void delete_list(block*& list);

int main(){
    srand(time(NULL));
    block* list;
    
    create_list(list);
    print_list(list);
    block* answer=larger_element(list);
    print_list(answer);
    delete_list(list);
    delete_list(answer);
    return 0;
}

void create_list(block*& list){
    int dim_list;
    cout<<"Lunghezza lista: ";
    cin>>dim_list;

    for(int i=0; i<dim_list; i++){
        block* created=new block {rand()%10, nullptr};
        if(i==0){
            list=created;
        }else{
            block* pointer=list;
            while(pointer->next != nullptr){
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

block* larger_element(block* list){
    block* answer=nullptr;
    while(list != nullptr){
        block* created=new block{element(list), nullptr};
        if(answer == nullptr){
            answer=created;
        }else{
            block* pointer=answer;
            while(pointer->next != nullptr){
                pointer=pointer->next;
            }
            pointer->next=created;
        }
        list=list->next;
    }
    return answer;
}

int element(block* list){
    block* pointer=list->next;
    while(pointer != nullptr){
        if((pointer->number)>(list->number)){
            return pointer->number;
        }
        else{
            pointer=pointer->next;
        }
    }
    return 0;
}

void delete_list(block*& list){
    while(list != nullptr){
        block* pointer=list;
        list=list->next;
        delete[] pointer;
    }
    delete[] list;
}