#include <iostream>
using namespace std;

struct block{
    int number;
    block* next;
};

void create_list(block*& list);
void print_list(block* list);
void search_in_list(block*& list);
void delete_list(block*& list);

int main(){
    srand(time(NULL));
    block* list;
    create_list(list);
    print_list(list);
    search_in_list(list);
    print_list(list);
    delete_list(list);
    return 0;
}

void create_list(block*& list){
    int len_lista;
    cout<<"Quanto deve essere lunga la lista?: ";
    cin>>len_lista;

    for(int i=0; i<len_lista; i++){
        block* created=new block{rand()%10+1, nullptr};
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
    cout<<"list-> ";
    while(list!=nullptr){
        cout<<list->number<<" ";
        list=list->next;
    }
    cout<<endl;
}

void search_in_list(block*& list){
    int searched, ricorsioni=0;
    cout<<"Inserire il numero da eliminare: ";
    cin>>searched;
    block* pointer=list;
    block* back=nullptr;
    while(pointer!=nullptr){
        if(pointer->number==searched){
            ricorsioni++;
            block* removable=pointer;
            if(back==nullptr){
                list=pointer->next;
            }else{
                back->next=pointer->next;
            }
            pointer=pointer->next;
            delete[] removable;
        }else{
            back=pointer;
            pointer=pointer->next;
        }
    }

    if(ricorsioni!=0){
        cout<<"Sono state rimosse "<<ricorsioni<<" celle"<<endl;
    }else{
        cout<<"Numero inserito non presente nella lista"<<endl;
    }
}

void delete_list(block*& list){
    while(list!=nullptr){
        block* pointer=list;
        list=list->next;
        delete[] pointer;
    }
    delete[] list;
}