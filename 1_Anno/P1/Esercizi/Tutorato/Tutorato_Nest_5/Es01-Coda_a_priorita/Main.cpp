#include <iostream>
#include "PriorityQ.h"
using namespace std;

int main() {
  priorityQueue *pq;
  int dim = 0;
  while (dim <= 0) {
    cout << "Number of priorities: ";
    cin >> dim;
    cout << endl;
  }
  pq = init(dim);

  char ans;
  char testo[MAX_DIM];
  int priority;
  do {
    cout << "'e' to insert a text\n";
    cout << "'d' to remove a text from the queue\n";
    cout << "'p' to print all the queue\n";
    cout << "'q' to quit\n";
    cin >> ans;
    switch (ans) {
    case 'e': {
      cout << "Text: ";
      cin >> testo;
      cout << "Priority: ";
      cin >> priority;
      cout << endl;
      enqueue(*pq, testo, priority);
      break;
    }
    case 'd': {
      ;
      if (dequeue(*pq)) {
        cout << "Value removed\n";
      }else{
        cout << "Queue is empty\n";
      }
      break;
    }
    case 'p': {
      print(*pq);
      break;
    }
    }
  } while (ans != 'q');

  dealloc(*pq);
  return 0;
}
