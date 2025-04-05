#include <fstream>
// #include <iostream>
#include <vector>
using namespace std;
int main()
{
    // Apri file input.txt
    ifstream fin("input.txt");
    int N = 0, v = 0;
    fin >> N;
    // Salva array
    vector<int> A, DP;
    while (fin >> v)
    {
        A.push_back(v);
        DP.push_back(v);
    }
    // Eseguo
    int MAX = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (A[j] <= A[i])
            {
                DP[i] = max(DP[j] + A[i], DP[i]);
                MAX = max(MAX, DP[i]);
            }
        }
    }
    // Apro file di output
    ofstream fout("output.txt");
    fout << MAX << endl;
    // Stampa tutto DP
    // for (int i = 0; i < N; i++)
    // {
    //     cout << DP[i] << " ";
    // }
    // cout << endl;
}