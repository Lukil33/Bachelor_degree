#ifndef PILA_H
#define PILA_H
 
struct nodoPila {
    char value;
    nodoPila* next;
};
typedef nodoPila* listaPila;
 
void pila_init();
bool pila_push(char character);
bool pila_top(char &character);
bool pila_pop();
void pila_deinit();
void pila_print();
 
#endif