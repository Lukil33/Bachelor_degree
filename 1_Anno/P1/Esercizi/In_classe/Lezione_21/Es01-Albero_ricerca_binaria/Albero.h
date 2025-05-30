#ifndef ALBERO_H
#define ALBERO_H

struct node{
    int value;
    node * left;
    node * right;
};

void albero_init();
void albero_insert(node* &,int);
void albero_deinit();
void stampaAlbero(node* radice, int spazio=0);

#endif