#ifndef PILA_H
#define PILA_H

struct Stack;

Stack * init();
int pop(Stack *);
void push(Stack *, int);
bool isEmpty(Stack *);
void quit(Stack * &);

#endif