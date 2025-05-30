//
// Scrivere un programma che prenda in input un carattere
// da tastiera, lo memorizzi in una variabile
// e lo stampi a video.
//
#include <iostream>
#include <string>

using namespace std;

int main() {
  char c;
  cout << "Dammi un carattere: ";
  cin >> c;
  cout << "Hai scritto: " << c << endl;
  return 0;
}