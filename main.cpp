#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <set>

using namespace std;


bool recorrer(vector<vector<int>> sudoku, int n, int num, int fila, int columna)
{
    int region = n;
    int fila_region = (fila / region) * region;
    int columna_region = (columna / region) * region;

    for (int i = 0; i < pow(n, 2); i++) 
    {
        if (sudoku[i][columna] == num || sudoku[fila][i] == num) {
            return false;
        }
    }
    for (int i = fila_region; i < fila_region + region; i++) 
    {
        for (int j = columna_region; j < columna_region + region; j++) 
        {
            if (sudoku[i][j] == num) {
                return false;
            }
        }
    }
    return true;
}

bool verificar_todo(vector<vector<int>>& sudoku) {
    int n = pow(n, 2);  // Tamaño del sudoku (n x n)
    int subregion = 2; // Tamaño de cada subregión

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

vector<vector<int>> resolver(vector<vector<int>> sudoku, int n, vector<int> numeros, int fila, int columna, int num_k, int* ultimo)
{
    if(verificar_todo(sudoku))
    {
        return sudoku;
    }

    int num = sudoku[fila][columna];
    if(num == 0)
    { 
        for(int k = num_k; k < numeros.size(); k++)
        {
            sudoku[fila][columna] = numeros[k];
            if(recorrer(sudoku, n, numeros[k], fila, columna))
            {
                for(int i = 0; i < pow(n, 2); i++)
                {
                    for(int j = 0; j < pow(n, 2); j++)
                    {
                        cout << sudoku[i][j] << "|";
                    }
                    cout << endl;
                    cout << "---------------------";
                    cout << endl;
                }
                ultimo[0] = fila;
                ultimo[1] = columna;
                if(columna == pow(n, 2) - 1)
                {
                    sudoku = resolver(sudoku, n, numeros, fila + 1, 0, 0, ultimo);
                }
                else
                {
                    sudoku = resolver(sudoku, n, numeros, fila, columna + 1, 0, ultimo);
                }
            }
            else
            {
                sudoku[fila][columna] = 0;
            }
        } 
    }
    return sudoku;
}

int main()
{
    int n; 
    int symbol;

    ifstream file("Entrada.txt", ios::in);
    string line;
    

    if(file.is_open())
    {
        getline(file, line);
        n = stoi(line);
        symbol = log(pow(n, 2)) + 1;

        vector<vector<int>> sudoku(pow(n, 2), vector<int>(pow(n, 2)));
        vector<int> numeros;
        for(int i = 1; i <= pow(n, 2); i++)
        {
            numeros.push_back(i);
        }

        for(int i = 0; i < pow(n, 2); i++)
        {
            getline(file, line);
            vector<string> subcadenas;
            for (int j = 0; j < line.length(); j += 2) 
            {
                string subcadena = line.substr(j, symbol);
                /* cout << subcadena << endl; */

                if (subcadena == "--") {
                    subcadenas.push_back("0");
                } else {
                    subcadenas.push_back(subcadena);
                }
            }

            for (int k = 0; k < subcadenas.size(); k++) 
            {
                int num = stoi(subcadenas[k]);
                sudoku[i][k] = num;
                /* cout << sudoku[i][k] << endl; */
            }
        }
        file.close();

    

        sudoku = resolver(sudoku, n, numeros, 0, 0, 0, new int[2]);

        for(int i = 0; i < pow(n, 2); i++)
        {
            for(int j = 0; j < pow(n, 2); j++)
            {
                cout << sudoku[i][j] << "|";
            }
            cout << endl;
            cout << "---------------------";
            cout << endl;
        }
        
    }
    else
    {
        cout << "Error";
    }
    return 0;
}