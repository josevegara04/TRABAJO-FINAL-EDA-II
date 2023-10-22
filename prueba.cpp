#include <iostream>
#include <vector>
#include <set>
#include <cmath>

using namespace std;

bool verificar_todo(vector<vector<int>>& sudoku) {
    int n = sudoku.size();  // Tamaño del sudoku (n x n)
    int subregion = sqrt(n); // Tamaño de cada subregión

    // Conjuntos para filas, columnas y subregiones
    vector<set<int>> filas(n);
    vector<set<int>> columnas(n);
    vector<set<int>> subregiones(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int num = sudoku[i][j];

            // Verificar si el número ya existe en la fila
            if (filas[i].count(num) > 0) {
                return false;
            }
            filas[i].insert(num);

            // Verificar si el número ya existe en la columna
            if (columnas[j].count(num) > 0) {
                return false;
            }
            columnas[j].insert(num);

            // Calcular la subregión a la que pertenece la celda
            int sub_i = i / subregion;
            int sub_j = j / subregion;
            int sub_id = sub_i * subregion + sub_j;

            // Verificar si el número ya existe en la subregión
            if (subregiones[sub_id].count(num) > 0) {
                return false;
            }
            subregiones[sub_id].insert(num);
        }
    }

    // Si no se encontraron duplicados, el sudoku es válido
    return true;
}

int main()
{
    vector<vector<int>> sudoku = 
    {
        {3, 4, 1, 2},
        {2, 1, 3, 4},
        {4, 3, 2, 1},
        {1, 2, 4, 3}
    };

    bool cen = verificar_todo(sudoku);
    cout << sudoku.size();
    return 0;
}

