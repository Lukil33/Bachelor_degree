#ifndef PRIORITYQUEUE_PRIORITYQ_H
#define PRIORITYQUEUE_PRIORITYQ_H

#include <iostream>
#define MAX_DIM 100000

struct node {
  char testo[MAX_DIM];
  node *left = nullptr;
  node *right = nullptr;
};

struct priorityQueue {
  node **queue;
  int dim;
};

priorityQueue *init(int dim);
void enqueue(priorityQueue &pq, char *testo, int priority);
bool dequeue(priorityQueue &pq);
void print(priorityQueue &pq);
void dealloc(priorityQueue &pq);

#endif