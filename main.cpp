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
    int opcion;

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

        //Pedir la opción a realizar
        cout << endl << "Escoja una opción: " << endl;
        cout << "1. Resolver sudoku" << endl << "2. Validar sudoku" << endl << "3. Generar sudoku" << endl << "4. Imprimir sudoku" << endl <<  "0. Salir del programa" << endl;
        cin >> opcion;

        //De acuerdo a la opción seleccionada, se escoje un algoritmo

        while(opcion != 0)
        {
            switch(opcion)
            {
                case 1:
                    if(resolver_sudoku(sudoku, n, numeros))
                    {
                        cout << endl << "-----" << "¡Sudoku resuelto!" << "-----" << endl << endl;
                        imprimir_sudoku(sudoku, n);
                    }
                    else
                    {
                        cout << "No se pudo resolver el sudoku" << endl;
                        imprimir_sudoku(sudoku, n);
                    }
                    break;
                case 2:
                    if(validar_sudoku(sudoku, n, numeros))
                    {
                        cout << endl << "-----" << "¡Sudoku valido!" << "-----" << endl << endl;
                        imprimir_sudoku(sudoku, n);
                    }
                    else
                    {
                        cout << "El sudoku no es valido" << endl;
                        imprimir_sudoku(sudoku, n);
                    }
                    break;
                case 4:
                    imprimir_sudoku(sudoku, n);
                    break;
            }
            cout << endl << "Escoja una opción: " << endl;
            cout << "1. Resolver sudoku" << endl << "2. Validar sudoku" << endl << "3. Generar sudoku" << endl << "4. Imprimir sudoku" << endl <<  "0. Salir del programa" << endl;
            cin >> opcion;
        }
        cout << "Programa finalizado con éxito" << endl << endl;
    }
    else
    {
        cout << "Error al leer el archivo";
    }
    return 0;
}