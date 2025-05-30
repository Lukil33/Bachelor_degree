#include <iostream>
#include <stdlib.h>
#include "Listnode.h"
using namespace std;

int main(int argc, char **argv){
    ListNode *head = nullptr;
    {
        ListNode *cur = head;
        for(int i = 1; i < argc; i++){
            if(head == nullptr){
                head = new ListNode(atoi(argv[i]));
                cur = head;
            }else{
                cur->next = new ListNode(atoi(argv[i]));
                cur = cur->next;
            }
        }
    }

    head = reverse_iterativa(head);
    head = reverse_ricorsiva(head);

    {
        ListNode *cur = head;
        while(cur != nullptr){
            cout << cur->val << " ";
            cur = cur->next;
        }
        cout <<endl;
    }
}