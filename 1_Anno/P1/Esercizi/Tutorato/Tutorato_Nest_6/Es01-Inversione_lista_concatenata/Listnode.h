#ifndef LISTNODE_H
#define LISTNODE_H

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {};
    ListNode(int v) : val(v), next(nullptr) {};
    ListNode(int v, ListNode *n) : val(v), next(n) {};
};

ListNode *reverse_iterativa(ListNode *head);
ListNode *reverse_ricorsiva(ListNode *head);
ListNode *ausiliaria(ListNode *head, ListNode *prec, ListNode *att, ListNode *fut);

#endif