#include <iostream>
using namespace std;

struct block{
    int number;
    block* next;
};

void create_list(block*&, int);
void print_list(block*);
void change_block(block*&, int);
void delete_list(block*&);

int main(){
    srand(time(NULL));
    block* list;
    
    int len_list;
    cout<<"Quanto deve essere lunga la lista?: ";
    cin>>len_list;
    
    create_list(list, len_list);
    print_list(list);
    change_block(list, len_list);
    print_list(list);
    delete_list(list);
    return 0;
}

void create_list(block*& list, int len_list){
    for(int i=0; i<len_list; i++){
        block* created=new block{rand()%10, nullptr};
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
    while(list!=nullptr){
        cout<<list->number<<" ";
        list=list->next;
    }
    cout<<endl;
}

void change_block(block*& list, int len_list){
    int first_index, second_index;
    cout<<"Inserire le posizioni da scambiare:"<<endl;
    cin>>first_index>>second_index;
    if((first_index>=len_list) || (second_index>=len_list)){
        cerr<<"Indici inseriti troppo alti"<<endl;
        return;
    }

    block* first_pointer=nullptr;
    block* first_element=list;
    for(int i=0; i<first_index; i++){
        if(i==0){
            first_pointer=list;
        }else{
            first_pointer=first_pointer->next;
        }
        first_element=first_pointer->next;
    }
    block* successiv_element=first_element->next;

    block* second_pointer=nullptr;
    block* second_element=list;
    for(int g=0; g<second_index; g++){
        if(g==0){
            second_pointer=list;
        }else{
            second_pointer=second_pointer->next;
        }
        second_element=second_pointer->next;
    }

    if(first_index==0){
        list=second_element;
    }else{
        first_pointer->next=second_element;
    }
    if(second_index==0){
        list=first_element;
    }else{
        second_pointer->next=first_element;
    }
    first_element->next=second_element->next;
    second_element->next=successiv_element;
}

void delete_list(block*& list){
    while(list!=nullptr){
        block* pointer=list;
        list=list->next;
        delete[] pointer;
    }
    delete[] list;
}