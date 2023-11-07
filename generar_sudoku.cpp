#include <vector> 
#include <set>
#include <cmath>
#include <random>
#include "resolver_sudoku.cpp"
#include <iostream>

using namespace std;

vector<vector<int>> generar_sudoku(int n, int dificultad, vector<int>& numeros)
{
    random_device rd;
    mt19937 generator(rd());
    vector<vector<int>> sudoku(pow(n, 2), vector<int>(pow(n,2), 0));

    uniform_int_distribution<int> distribution(0, sudoku.size() - 1);
    int fila_random = distribution(generator);
    int columna_random = distribution(generator);
    int indice_random = distribution(generator);
    int numero_random = numeros[indice_random];

    cout << fila_random << endl << columna_random << endl;
    sudoku[fila_random][columna_random] = numero_random;

    vector<vector<int>> copia = sudoku;
    
    if(resolver_sudoku(sudoku, n, numeros))
    {
        cout << "Sudoku generado con éxito" << endl;
    }
    else
    {
        cout << "Error" << endl;
    }

    return sudoku;
}