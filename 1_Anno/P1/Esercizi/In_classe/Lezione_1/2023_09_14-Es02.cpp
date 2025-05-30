// Scrivete un programma che, data in input una temperatura in Fahrenheit,
// ritorni a video il corretto valore in Celsius.

#include <iostream>
using namespace std;

int main() {
  float temperaturaF, temperaturaC;
  cout<<"Inserisci la temperatura in gradi Fahrenheit: ";
  cin>>temperaturaF;

  temperaturaC= (temperaturaF-32)/1.8;

  cout<<"La temperatura in gradi Celsius è: "<<temperaturaC<<endl; 
  return 0;
}
