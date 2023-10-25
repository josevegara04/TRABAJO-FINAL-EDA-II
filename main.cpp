#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include "resolver_sudoku.cpp"
#include "validar_sudoku.cpp"

using namespace std;

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
            imprimir_sudoku(sudoku, n);
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