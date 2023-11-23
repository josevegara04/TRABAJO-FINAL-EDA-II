#include <vector>
#include <set>
#include <iostream>
#include <algorithm>

using namespace std;

//Esstructura de las celdas vacías
struct Celda
{
    int fila;
    int columna;
    set<int> candidatos; //Posibles candidatos para cada celda vacía
};

// Función para imprimir el tablero
void imprimir_sudoku(const vector<vector<int>>& sudoku, int n) 
{
    cout << "Tamaño: " << n << " x " << n << endl << endl; //Tamaño del sudoku
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

// Función para verificar si un número es válido en una celda
bool numero_valido(const vector<vector<int>>& sudoku, const int n, const int fila, const int columna, const int numero) 
{
    // Verificar en la fila y columna de la celda en cuestión
    for (int i = 0; i < sudoku.size(); i++) 
    {
        if (sudoku[fila][i] == numero || sudoku[i][columna] == numero) 
        {
            return false;
        }
    }

    // Verificar la región de la celda vacía
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

//Función para hacer y organizar las celdas vacías con sus posibles candidatos
vector<Celda> iniciar_celdas(const vector<vector<int>>& sudoku, const int n)
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
                    if(numero_valido(sudoku, n, fila, columna, i))
                    {
                        celda.candidatos.insert(i);
                    }
                }
                celdas_vacias.push_back(celda);
            }
        }
    }

    //Algoritmo para organizar las celdas vacías de menor a mayor en función de su total de candidatos
    sort(celdas_vacias.begin(), celdas_vacias.end(), [](const Celda& a, const Celda& b) 
    {
        return a.candidatos.size() < b.candidatos.size();
    });
    return celdas_vacias;
}

//Función para borrar candidatos
void borrar_candidatos(vector<Celda>& celdas_vacias, const int fila, const int columna, const int candidato)
{
    auto it = celdas_vacias.begin();
    while (it != celdas_vacias.end())
    {
        Celda& cel = *it;

        if (cel.fila == fila || cel.columna == columna)
        {
            cel.candidatos.erase(candidato);
        }

        if (cel.candidatos.empty())
        {
            it = celdas_vacias.erase(it);
        }
        else
        {
            ++it;
        }
    }

    //Algoritmo para organizar las celdas vacías de menor a mayor en función de su total de candidatos
    sort(celdas_vacias.begin(), celdas_vacias.end(), [](const Celda& a, const Celda& b) 
    {
        return a.candidatos.size() < b.candidatos.size();
    });
}

//Función para encontrar celdas con solo una posibilidad
bool encontrar_uno(vector<Celda>& celdas_vacias)
{
    bool res = false;
    for(const Celda& cel : celdas_vacias)
    {
        if(cel.candidatos.size() == 1)
        {
            res = true;
        }
    }
    return res;
}

//Función para resolver las celdas con solo una posibilidad
void resolver_uno(vector<vector<int>>& sudoku, vector<Celda>& celdas_vacias, bool cen)
{
    if(!cen)
    {
        return;
    }
    for(const Celda& cel : celdas_vacias)
    {
        if(cel.candidatos.size() == 1)
        {
            for(int candidato : cel.candidatos)
            {
                sudoku[cel.fila][cel.columna] = candidato;
                borrar_candidatos(celdas_vacias, cel.fila, cel.columna, candidato);
            }
        }
    }
    if(!encontrar_uno(celdas_vacias))
    {
        cen = false;
    }
    resolver_uno(sudoku, celdas_vacias, cen);
}

bool resolver_sudoku(vector<vector<int>>& sudoku, const int n, const vector<Celda>& celdas_vacias)
{
    for(const Celda& cel : celdas_vacias)
    {
        if(sudoku[cel.fila][cel.columna] == 0)
        {
            for(int candidato : cel.candidatos)
            {
                if(numero_valido(sudoku, n, cel.fila, cel.columna, candidato))
                {
                    sudoku[cel.fila][cel.columna] = candidato;
                    if(resolver_sudoku(sudoku, n, celdas_vacias))
                    {
                        return true;
                    }
                    sudoku[cel.fila][cel.columna] = 0;
                }
            }
            return false;
        }
    }
    return true;
}

//Función para imprimir las celdas vacías
void imprimir_celdas_vacias(const vector<Celda>& celdas_vacias)
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