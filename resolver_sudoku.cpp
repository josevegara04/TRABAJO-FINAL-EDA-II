#include <vector>
#include <set>
#include <iostream>

using namespace std;

// Funcion para imprimir el tablero
void imprimir_sudoku(const vector<vector<int>>& sudoku, int n) 
{
    cout << "Tamaño: " << n << " x " << n << endl << endl;
    for (int i = 0; i < sudoku.size(); i++) 
    {
        for (int j = 0; j < sudoku.size(); j++) 
        {
            cout << sudoku[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Funcion para verificar si un numero es valido en una celda
bool es_numero_valido(const vector<vector<int>>& sudoku, int n, int fila, int columna, int numero) 
{
    if(numero > sudoku.size())
    {
        return false;
    }
    // Verificar la fila
    for (int i = 0; i < sudoku.size(); i++) 
    {
        if (sudoku[fila][i] == numero) 
        {
            return false;
        }
    }

    // Verificar la columna
    for (int i = 0; i < sudoku.size(); i++) 
    {
        if (sudoku[i][columna] == numero) 
        {
            return false;
        }
    }

    // Verificar la region
    int inicioFila = (fila / n) * n;
    int inicioColumna = (columna / n) * n;
    for (int i = inicioFila; i < inicioFila + n; i++) 
    {
        for (int j = inicioColumna; j < inicioColumna + n; j++) 
        {
            if (sudoku[i][j] == numero) 
            {
                return false;
            }
        }
    }

    return true;
}

// Funcion para resolver el Sudoku 
bool resolver_sudoku(vector<vector<int>>& sudoku, int n, vector<int>& numeros) 
{
    for (int fila = 0; fila < sudoku.size(); fila++) 
    {
        for (int columna = 0; columna < sudoku.size(); columna++) 
        {
            if (sudoku[fila][columna] == 0) 
            { 
                for (int numero = 1; numero <= numeros.size(); numero++) 
                {
                    if (es_numero_valido(sudoku, n, fila, columna, numero)) 
                    {
                        sudoku[fila][columna] = numero;  
                        /* cout << sudoku[fila][columna] << endl; */

                        if (resolver_sudoku(sudoku, n, numeros)) 
                        {  
                            return true;
                        }

                        sudoku[fila][columna] = 0;  
                    }
                }
                return false;  
            }
        }
    }
    return true;  
}