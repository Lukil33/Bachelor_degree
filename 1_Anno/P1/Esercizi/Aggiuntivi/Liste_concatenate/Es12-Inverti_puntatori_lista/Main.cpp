#include <iostream>
using namespace std;

struct block{
    int number;
    block* next;
};

void create_list(block*& list);
void print_list(block* list);
void reverse_pointer(block*& list);
void delete_list(block*& list);

int main(){
    srand(time(NULL));
    block* list;
    create_list(list);
    print_list(list);
    reverse_pointer(list);
    print_list(list);
    delete_list(list);
    return 0;
}

void print_list(block* list){
    cout<<"List-> ";
    while(list != nullptr){
        cout<<list->number<<" ";
        list=list->next;
    }
    cout<<endl;
}

void create_list(block*& list){
    int dim_list;
    cout<<"Lunghezza lista: ";
    cin>>dim_list;

    for(int i=0; i<dim_list; i++){
        block* created=new block{rand()%10, nullptr};
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

void reverse_pointer(block*& list){
    block* back_list=nullptr;
    block* front_list=list->next;
    while(front_list != nullptr){
        list->next=back_list;
        back_list=list;
        list=front_list;
        front_list=front_list->next;
    }
    list->next=back_list;
}

void delete_list(block*& list){
    while(list != nullptr){
        block* pointer=list;
        list=list->next;
        delete[] pointer;
    }
    delete[] list;
}