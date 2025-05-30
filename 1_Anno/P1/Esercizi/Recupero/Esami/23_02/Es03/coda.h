#ifndef CODA_H
#define CODA_H

struct nodoCoda {
	int value;
	nodoCoda* next;
};
typedef nodoCoda* listaCoda;

struct coda {
    listaCoda tail;
    listaCoda head;
};

void init();
bool enqueue(int);
bool first(int &);
bool dequeue();
void deinit();
void print();

#endif