#include <iostream>
using namespace std;

struct block{
    int number;
    block* next;
};

void create_list(block*& list);
void ordinate_insert(block*& list, int number);
void print_list(block* list);
void merge_sort(block*& merge, block*& first_list, block*& second_list);

int main(){
    srand(time(NULL));
    block* first_list;
    block* second_list;
    block* merge;

    create_list(first_list);
    create_list(second_list);

    cout<<"First List-> ";
    print_list(first_list);
    cout<<"Second List-> ";
    print_list(second_list);

    merge_sort(merge, first_list, second_list);
    cout<<"Marge-> ";
    print_list(merge);

    return 0;
}

void create_list(block*& list){
    int dim_list;
    cout<<"Insert list lenght: ";
    cin>>dim_list;

    for(int i=0; i<dim_list; i++){
        int number=rand()%10;
        ordinate_insert(list, number);
    }
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

void print_list(block* list){
    while(list != nullptr){
        cout<<list->number<<" ";
        list=list->next;
    }
    cout<<endl;
}

void merge_sort(block*& merge, block*& first_list, block*& second_list){
    while((first_list != nullptr) || (second_list != nullptr)){
        if((first_list != nullptr)&&((second_list == nullptr)||(first_list->number)<=(second_list->number))){
            block* pointer=first_list;
            first_list=first_list->next;
            pointer->next=nullptr;
            if(merge==nullptr){
                merge=pointer;
            }else{
                block* end_merge=merge;
                while(end_merge->next != nullptr){
                    end_merge=end_merge->next;
                }
                end_merge->next=pointer;
            }
        }else{
            block* pointer=second_list;
            second_list=second_list->next;
            pointer->next=nullptr;
            if(merge==nullptr){
                merge=pointer;
            }else{
                block* end_merge=merge;
                while(end_merge->next != nullptr){
                    end_merge=end_merge->next;
                }
                end_merge->next=pointer;
            }
        }
    }
    delete[] first_list;
    delete[] second_list;
}