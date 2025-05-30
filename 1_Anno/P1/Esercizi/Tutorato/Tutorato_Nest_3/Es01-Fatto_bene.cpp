#include <iostream>
#include <fstream>
using namespace std;

// Costanti derivate dalla descrizione dell'esercizio
const int MAX_PAROLE = 10000;
const int MAX_LUNGHEZZA = 101;

// Calcola la lunghezza della parola
int strlen(char parola [])
{
  int contatore = 0;
  while(parola[contatore] != '\0')
    contatore++;
  return contatore;
}

int main(int argc, char * argv [])
{
  // Array che conterrà tutte le parole valide del file
  // in input
  char parole[MAX_PAROLE][MAX_LUNGHEZZA];

  // Numero totale di parole valide lette
  int totale_parole = 0;

  // Controllo se il numero degli argomenti è corretto
  if (argc != 3)
  {
    cout << "Usage: esercizio2 <input_file> <output_file>" << endl;
    exit(1);
  }

  // Creo i miei stream
  fstream input, output;
  input.open(argv[1], ios::in);
  output.open(argv[2], ios::out);

  // Controllo se riesco ad aprire il file di input
  if (input.fail())
  {
    cout << "Non sono riuscito ad aprire il file " << argv[1] << endl;
    input.close();
    output.close();
    exit(1);
  }

  // Inizializzo un buffer e inizio a leggere il file di input.
  char buffer[MAX_LUNGHEZZA];
  while(input>>buffer)
  {
    // Verifico se la mia parola rispetta i criteri di selezione
    int lunghezza = strlen(buffer);
    if (lunghezza%2 == 0)
    {
      // Se la parola è valida, allora la copio all'interno
      // del mio array, ricordandomi di aggiungere il carattere
      // terminatore alla fine della stringa
      for (int i=0; i<lunghezza; i++)
      {
        parole[totale_parole][i] = buffer[i];
      }
      parole[totale_parole][lunghezza] = '\0';

      totale_parole++;
    }
  }

  // Come ultima operazione, copio l'array all'interno del mio file
  // in output, invertendo l'ordine delle parole
  for (int i=totale_parole-1; i>=0; i--)
  {
    output << parole[i] << " ";
  }
  output << endl;

  // Chiudo gli stream
  input.close();
  output.close();

  return 0;
}