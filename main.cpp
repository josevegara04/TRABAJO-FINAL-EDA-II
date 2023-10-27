#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include "resolver_sudoku.cpp"
#include "validar_sudoku.cpp"

vector<vector<int>> leer_archivo(string nombre_archivo, int& n, int& symbol, vector<int>& numeros)
{
    ifstream file(nombre_archivo, ios::in);
    string line;
    vector<vector<int>> sudoku;
    
    if(file.is_open())
    {
        getline(file, line);
        n = stoi(line);
        symbol = log(pow(n, 2)) + 1;

        sudoku.resize(pow(n, 2), vector<int>(pow(n, 2)));

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
        for(int i = 1; i <= sudoku.size(); i++)
        {
            numeros.push_back(i);
        }
    }
    else
    {
        cout << "Error al leer el archivo";
    }
    return sudoku;
}

using namespace std;

int main()
{
    int n = 0; 
    int symbol = 0;
    int opcion;
    vector<vector<int>> sudoku;
    vector<int> numeros;
    
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
                sudoku = leer_archivo("Entrada.txt", n, symbol, numeros);
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
                sudoku = leer_archivo("Entrada.txt", n, symbol, numeros);
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
                sudoku = leer_archivo("Entrada.txt", n, symbol, numeros);
                imprimir_sudoku(sudoku, n);
                break;
        }
        cout << endl << "Escoja una opción: " << endl;
        cout << "1. Resolver sudoku" << endl << "2. Validar sudoku" << endl << "3. Generar sudoku" << endl << "4. Imprimir sudoku" << endl <<  "0. Salir del programa" << endl;
        cin >> opcion;
    }
    cout << endl << "Programa finalizado con éxito" << endl << endl;
    return 0;
}