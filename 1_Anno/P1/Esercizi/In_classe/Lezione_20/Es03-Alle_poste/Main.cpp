#include <iostream>
using namespace std;
#include "Coda.h"

int main() {
  init();

  char ans;
  char nome[MAX_DIM];
  do {
    cout << "'e' to insert a person\n";
    cout << "'d' to remove a person from the queue\n";
    cout << "'p' to print the queue\n";
    cout << "'q' to quit\n";
    cin >> ans;
    switch (ans) {
    case 'e': {
      cout << "Nome: ";
      cin >> nome;
      cout << endl;
      enqueue(nome);
      break;
    }
    case 'd': {
      if (dequeue() == 0) {
        cout << "Queue is empty\n";
      } else {
        cout << "Value removed\n";
      }
      break;
    }
    case 'p': {
      print();
      break;
    }
    }
  } while (ans != 'q');

  deinit();
  return 0;
}