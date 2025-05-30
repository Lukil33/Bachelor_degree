#include <iostream>
using namespace std;

struct block{
    int number;
    block* next;
};

void create_list(block*& list);
void print_list(block* list);
void remove_duplicate(block*& list);
void delete_list(block*& list);

int main(){
    srand(time(NULL));
    block* list;

    create_list(list);

    cout<<"Initial list-> ";
    print_list(list);
    cout<<endl;

    remove_duplicate(list);

    cout<<"Final list-> ";
    print_list(list);
    cout<<endl;

    delete_list(list);
    return 0;
}

void create_list(block*& list){
    int dim_list;
    cout<<"Quanto deve essere lunga la lista?: ";
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
    while(list != nullptr){
        cout<<list->number<<" ";
        list=list->next;
    }
}

void remove_duplicate(block*& list){
    block* supporter=list;
    while(supporter != nullptr){
        block* pointer=supporter->next;
        block* back_pointer=supporter;
        while(pointer != nullptr){
            if(pointer->number == supporter->number){
                block* deletable=pointer;
                pointer=pointer->next;
                back_pointer->next=pointer;
                delete[] deletable;
            }else{
                back_pointer=pointer;
                pointer=pointer->next;
            }
        }
        supporter=supporter->next;
    }
}

void delete_list(block*& list){
    while(list != nullptr){
        block* pointer=list;
        list=list->next;
        delete[] pointer;
    }
    delete[] list;
}