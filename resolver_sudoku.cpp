#include <vector>
#include <set>
#include <iostream>
#include <algorithm>

using namespace std;

//Celdas vacías
struct Celda
{
    int fila;
    int columna;
    set<int> candidatos;
};

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
        if (sudoku[fila][i] == numero || sudoku[i][columna] == numero) 
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

//Función para hacer y organizar las celdas vacías con sus candidatos
vector<Celda> iniciar_celdas(const vector<vector<int>> sudoku, const int n)
{
    vector<Celda> celdas_vacias;
    for(int fila = 0; fila < sudoku.size(); fila++)
    {
        for(int columna = 0; columna < sudoku.size(); columna++)
        {
            if(sudoku[fila][columna] == 0)
            {
                Celda celda;
                celda.fila = fila;
                celda.columna = columna;
                for(int i = 1; i <= sudoku.size(); i++)
                {
                    if(es_numero_valido(sudoku, n, fila, columna, i))
                    {
                        celda.candidatos.insert(i);
                    }
                }
                celdas_vacias.push_back(celda);
            }
        }
    }
    sort(celdas_vacias.begin(), celdas_vacias.end(), [](const Celda& a, const Celda& b) 
    {
        return a.candidatos.size() < b.candidatos.size();
    });
    return celdas_vacias;
}

/* bool resolver(vector<vector<int>>& sudoku, const int n)
{
    vector<Celda> celdas_vacias = iniciar_celdas(sudoku, n);
    return resolver_sudoku(sudoku, n, celdas_vacias, 0);
} */
// Funcion para resolver el Sudoku 
bool resolver_sudoku(vector<vector<int>>& sudoku, const int n, vector<Celda> celdas_vacias, int index) 
{
    if(index == sudoku.size())
    {
        return true;
    }

    int fila = celdas_vacias[index].fila;
    int columna = celdas_vacias[index].columna;

    for(int candidato : celdas_vacias[index].candidatos)
    {
        if(es_numero_valido(sudoku, n, fila, columna, candidato))
        {
            sudoku[fila][columna] = candidato;
            if(resolver_sudoku(sudoku, n, celdas_vacias, index + 1))
            {
                return true;
            }
            sudoku[fila][columna] = 0;
        }
    }
    return false;
}

void imprimir_celdas_vacias(vector<Celda> celdas_vacias)
{
    cout << "Candidatos de celdas vacías:" << endl;
    for (const Celda& celda : celdas_vacias) 
    {
        cout << "Fila: " << celda.fila << ", Columna: " << celda.columna << ", Candidatos: ";
        for (int candidato : celda.candidatos) 
        {
            cout << candidato << " ";
        }
        cout << endl;
    } 
}