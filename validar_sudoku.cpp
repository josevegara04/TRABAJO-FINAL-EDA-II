#include <set> 
#include <vector> 

using namespace std;

//Función para validar cualquier sudoku
bool validar_sudoku(const vector<vector<int>>& sudoku, int n)
{
    set<int> verificados;

    //Verificar filas
    for(int i = 0; i < sudoku.size(); i++)
    {
        for(int j = 0; j < sudoku.size(); j++)
        {
            if(sudoku[i][j] == 0 || verificados.count(sudoku[i][j]) > 0)
            {
                return false;
            }
            verificados.insert(sudoku[i][j]);
        }
        verificados.clear();
    }

    //Verificar columnas
    for(int i = 0; i < sudoku.size(); i++)
    {
        for(int j = 0; j < sudoku.size(); j++)
        {
            if(sudoku[j][i] == 0 || verificados.count(sudoku[j][i]) > 0)
            {
                return false;
            }
            verificados.insert(sudoku[j][i]);
        }
        verificados.clear();
    }
    
    //Verificar regiones
    for(int fila_region = 0; fila_region < sudoku.size(); fila_region += n)
    {
        for(int columna_region = 0; columna_region < sudoku.size(); columna_region += n)
        {
            for(int fila = fila_region; fila < fila_region + n; fila++)
            {
                for(int columna = columna_region; columna < columna_region + n; columna++)
                {
                    if(sudoku[fila][columna] == 0 || verificados.count(sudoku[fila][columna]) > 0)
                    {
                        return false;
                    }
                    verificados.insert(sudoku[fila][columna]);
                }
            }
            verificados.clear();
        }
    }
    return true;
}