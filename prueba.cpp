#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include "resolver_sudoku.cpp"
#include "validar_sudoku.cpp"
#include <random>

using namespace std;

int main()
{
    vector<vector<int>> sudoku {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    int n = 3;
    vector<Celda> celdas_vacias = iniciar_celdas(sudoku, n);
    imprimir_celdas_vacias(celdas_vacias);
    cout << celdas_vacias.size() << endl;
    resolver_uno(sudoku, celdas_vacias, true);
    imprimir_celdas_vacias(celdas_vacias);
    if(resolver_sudoku(sudoku, n, celdas_vacias))
    {
        cout << "bien";
    }
    else
    {
        cout << "mal";
    }
    imprimir_sudoku(sudoku, n);
}