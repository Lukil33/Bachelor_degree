// Scrivete un programma che, dato in input il raggio,
// calcoli l’area e la circonferenza di un cerchio.
#include <iostream>
using namespace std;

int main() {
  
  float raggio, area, circonferenza;

  cout<<"Inserisci il modulo del raggio: ";
  cin>> raggio;

  area = 3.14*raggio*raggio;
  circonferenza= 2*3.14*raggio;

  cout<<"La circonferenza vale: "<<circonferenza<<endl<<"l'area vale: "<<area<<endl;
  
  return 0;
}