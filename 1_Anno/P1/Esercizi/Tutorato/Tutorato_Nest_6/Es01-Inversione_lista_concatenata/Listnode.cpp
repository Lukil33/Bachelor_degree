#include <iostream>
#include "Listnode.h"
using namespace std;

ListNode *reverse_iterativa(ListNode *head){
    ListNode *prec=nullptr;
    ListNode *att=head;
    ListNode *fut=head;

    while(att!=nullptr){
        fut=att->next;

        att->next=prec;

        prec=att;
        att=fut;
    }

    return prec;
}

ListNode *reverse_ricorsiva(ListNode *head){
    ListNode *prec=nullptr;
    ListNode *att=head;
    ListNode *fut=head;
    head = ausiliaria(head, prec, att, fut);
    return head;
}

ListNode *ausiliaria(ListNode *head, ListNode *prec, ListNode *att, ListNode *fut){
    if(fut==nullptr){
        att->next=prec;
        head=att;
    }else{
        ausiliaria(head, att, fut, fut->next);
        att->next=prec;
    }
    return head;
}