#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <set>

using namespace std;

// Funcion para imprimir el tablero
void imprimir_sudoku(const vector<vector<int>>& sudoku) 
{
    for (int i = 0; i < sudoku.size(); i++) 
    {
        for (int j = 0; j < sudoku.size(); j++) 
        {
            cout << sudoku[i][j] << " ";
        }
        cout << std::endl;
    }
}

// Funcion para verificar si un numero es valido en una celda
bool es_numero_valido(const vector<vector<int>>& sudoku, int n, int fila, int columna, int numero) 
{
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
        for(int i = 1; i <= sudoku.size(); i++)
        {
            numeros.push_back(i);
        }

        for(int i = 0; i < sudoku.size(); i++)
        {
            getline(file, line);
            vector<string> subcadenas;
            for (int j = 0; j < line.length(); j += 2) 
            {
                string subcadena = line.substr(j, symbol);

                if (subcadena == "--") {
                    subcadenas.push_back("0");
                } else {
                    subcadenas.push_back(subcadena);
                }
            }

            for (int j = 0; j < subcadenas.size(); j++) 
            {
                int num = stoi(subcadenas[j]);
                sudoku[i][j] = num;
            }
        }
        file.close();

        if(resolver_sudoku(sudoku, n, numeros))
        {
            imprimir_sudoku(sudoku);
        }
        else
        {
            cout << "No se pudo resolver el sudoku" << endl;
        }
        
    }
    else
    {
        cout << "Error";
    }
    return 0;
}