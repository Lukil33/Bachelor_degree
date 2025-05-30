#include <iostream>
using namespace std;

struct block{
    int number;
    block* next;
};

void create_random_list(block*& list);
void reverse_value(block*& list);
void print_list(block* list);
int lenght(block* list);
block* find_element(block* list, int number);
void delete_list(block*& list);

int main(){
    srand(time(NULL));
    block* list;
    create_random_list(list);
    print_list(list);
    reverse_value(list);
    print_list(list);
    delete_list(list);
    return 0;
}

void create_random_list(block*& list){
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

void print_list(block* list){
    cout<<"List-> ";
    while(list != nullptr){
        cout<<list->number<<" ";
        list=list->next;
    }
    cout<<endl;
}

void reverse_value(block*& list){
    int len_list=lenght(list);

    for(int i=0; i<(len_list/2); i++){
        block* first_element=find_element(list, i);
        block* second_element=find_element(list, len_list-i-1);
        int number= first_element->number;
        first_element->number=second_element->number;
        second_element->number=number;
    }
}

int lenght(block* list){
    int i=0;
    while(list != nullptr){
        list= list->next;
        i++;
    }
    return i;
}

block* find_element(block* list, int number){
    for(int i=0; i<number; i++){
        list=list->next;
    }
    return list;
}

void delete_list(block*& list){
    while(list != nullptr){
        block* pointer=list;
        list=list->next;
        delete[] pointer;
    }
    delete[] list;
}