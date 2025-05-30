#ifndef PILA_H
#define PILA_H

struct nodoPila {
	char value;
	nodoPila* next;
};
typedef nodoPila* listaPila;

void pila_init();
bool pila_push(char);
bool pila_top(char &);
bool pila_pop();
void pila_deinit();
void pila_print();

#endif