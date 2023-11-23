#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include "resolver_sudoku.cpp"
#include "validar_sudoku.cpp"
#include <random>

using namespace std;


vector<vector<int>> leer_archivo(string nombre_archivo, int& n, int& symbol)
{
    ifstream file(nombre_archivo, ios::in);
    string line;
    vector<vector<int>> sudoku;
    
    if(file.is_open())
    {

        getline(file, line);
        n = stoi(line);
        symbol = log10(pow(n, 2)) + 1;

        sudoku.resize(pow(n, 2), vector<int>(pow(n, 2)));

        for(int i = 0; i < sudoku.size(); i++)
        {
            getline(file, line);
            vector<string> subcadenas;
            for (int j = 0; j < line.length(); j += symbol) 
            {
                string subcadena = line.substr(j, symbol);

                if (subcadena.find('-') != string::npos ) 
                {
                    subcadenas.push_back("0");
                } 
                else 
                {
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
    }
    else
    {
        cout << "Error al leer el archivo";
    }
    return sudoku;
}


int main()
{
    vector<vector<int>> sudoku;
    int n;
    int symbol;
    vector<Celda> celdas_vacias;

    sudoku = leer_archivo("Entrada.txt", n, symbol);
    celdas_vacias = iniciar_celdas(sudoku, n);
    imprimir_celdas_vacias(celdas_vacias);
    imprimir_sudoku(sudoku, n);
    /* resolver_uno(sudoku, celdas_vacias, true);
    imprimir_celdas_vacias(celdas_vacias); */
    if(resolver_sudoku(sudoku, n, celdas_vacias))
    {
        cout << "exito";
    }
    else
    {
        cout << "F";
    }
}
