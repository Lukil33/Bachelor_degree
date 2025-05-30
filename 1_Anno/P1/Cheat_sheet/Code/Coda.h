#ifndef CODA_H
#define CODA_H

struct nodoCoda {
	char value;
	nodoCoda* next;
};
typedef nodoCoda* listaCoda;

struct coda {
    listaCoda tail;
    listaCoda head;
};

void coda_init();
bool coda_enqueue(char);
bool coda_first(char &);
bool coda_dequeue();
void coda_deinit();
void coda_print();

#endif



