#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include "resolver_sudoku.cpp"
#include "validar_sudoku.cpp"
#include <random>

using namespace std;

void generar_sudoku(vector<vector<int>>& sudoku, int n, int dificultad, vector<Celda>& celdas_vacias, bool cen)
{
    if(cen)
    {
        return;
    }
    
    random_device rd;
    mt19937 generator(rd());
    double porcentaje;
    int casillas;
    int fila_random;
    int columna_random;
    int numero_random;
    int llenar;
    uniform_int_distribution<int> distribution(0, sudoku.size() - 1);
    uniform_int_distribution<int> distri(1, sudoku.size());
    vector<vector<int>> copia;

    switch(dificultad)
    {
        case 1:
            porcentaje = 0.4;
            break;
        case 2:
            porcentaje = 0.3;
            break;
        case 3:
            porcentaje = 0.2;
            break;
        case 4:
            porcentaje = 0.15;
            break;
    }
    casillas = static_cast<int>(porcentaje*pow(pow(n, 2), 2));
    

    switch(n)
    {
        case 2:
            llenar = 4;
            break;
        case 3:
            llenar = 4;
            break;
        case 4:
            llenar = 16;
            break;
    }
    //Se asigna numeros random en el sudoku
    for(int i = 0; i < llenar; i++)
    {
        fila_random = distribution(generator);
        columna_random = distribution(generator);
        numero_random = distri(generator);
        while(sudoku[fila_random][columna_random] != 0)
        {
            fila_random = distribution(generator);
            columna_random = distribution(generator);
        }
        while(!numero_valido(sudoku, n, fila_random, columna_random, numero_random))
        {
            numero_random = distri(generator);
        }
        sudoku[fila_random][columna_random] = numero_random;
    }
    
    copia = sudoku;
    celdas_vacias = iniciar_celdas(sudoku, n);

    if(resolver_sudoku(copia, n, celdas_vacias))
    {
        cen = true;
        for(int i = 0; i < casillas; i++)
        {
            fila_random = distribution(generator);
            columna_random = distribution(generator);
            while(sudoku[fila_random][columna_random] != 0)
            {
                fila_random = distribution(generator);
                columna_random = distribution(generator);
            }
            sudoku[fila_random][columna_random] = copia[fila_random][columna_random];
        }
    }
    else
    {
        //Poner todas las celdas vacias, es decir, con el valor 0
        for(int i = 0; i < sudoku.size(); i++)
        {
            for(int j = 0; j < sudoku.size(); j++)
            {
                sudoku[i][j] = 0;
            }
        }
    }
    generar_sudoku(sudoku, n, dificultad, celdas_vacias, cen);
}

void sobrescribir_archivo(string nombre_archivo, vector<vector<int>>& sudoku, int n)
{
    ofstream file(nombre_archivo);
    string numero;
    int numero_digitos = log10(pow(n, 2)) + 1;
    string ceros(numero_digitos - 1, '0');

    if(file.is_open())
    {
        file << n << endl;
        for(int i = 0; i < sudoku.size(); i++)
        {
            for(int j = 0; j < sudoku.size(); j++)
            {
                if(sudoku[i][j] == 0)
                {
                    numero = string(numero_digitos, '-');
                    file << numero;
                }
                else
                {
                    numero = to_string(sudoku[i][j]);
                    numero = ceros + numero;
                    file << numero;
                }
            }
            file << endl;
        }
    }
    else
    {
        cout << "F";
    }
}

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
    int n; 
    int symbol = 0;
    int opcion;
    vector<vector<int>> sudoku;
    vector<Celda> celdas_vacias;
    bool cen = false;

    cout << endl << "----------------" << endl << endl << "Entrada: " << endl << endl;
    sudoku = leer_archivo("Entrada.txt", n, symbol);
    imprimir_sudoku(sudoku, n);
    
    //Pedir la opción a realizar
    cout << endl << "Escoja una opción: " << endl;
    cout << "1. Resolver sudoku" << endl << "2. Validar sudoku" << endl << "3. Generar sudoku" << endl << "4. Imprimir sudoku" << endl <<  "0. Salir del programa" << endl;
    cin >> opcion;

    //De acuerdo a la opción seleccionada, se escoje un algoritmo
    while(opcion != 0)
    {
        sudoku.clear();
        
        switch(opcion)
        {
            case 1:
                sudoku = leer_archivo("Entrada.txt", n, symbol);
                celdas_vacias = iniciar_celdas(sudoku, n);
                /* resolver_uno(sudoku, celdas_vacias, true); */
                if(resolver_sudoku(sudoku, n, celdas_vacias))
                {
                    cout << endl << "-----" << "¡Sudoku resuelto!" << "-----" << endl;
                    cout << endl << "----" << "Verifique en la entrada" << "----" << endl << endl;
                    sobrescribir_archivo("Entrada.txt", sudoku, n);
                }
                else
                {
                    cout << "No se pudo resolver el sudoku" << endl;
                }
                break;
            case 2:
                sudoku = leer_archivo("Entrada.txt", n, symbol);
                if(validar_sudoku(sudoku, n))
                {
                    cout << endl << "-----" << "¡Sudoku valido!" << "-----" << endl << endl;
                }
                else
                {
                    cout << endl << "-----" << "El sudoku no es válido" << "-----" << endl << endl;
                }
                break;
            case 3:
                int dificultad;
                cout << "Seleccione la dificultad: " << endl 
                        << "1. Fácil" << endl << "2. Normal" << endl << "3. Difícil" << endl;
                cin >> dificultad;
                cout << "Seleccione el tamaño del sudoku representado por un dígito: " << endl;
                cin >> n;
                sudoku.resize(pow(n, 2), vector<int>(pow(n, 2)));
                
                generar_sudoku(sudoku, n, dificultad, celdas_vacias, cen);
                sobrescribir_archivo("Entrada.txt", sudoku, n);
                cout << endl << "-----" << "¡Sudoku generado!" << "-----" << endl;
                cout << endl << "----" << "Verifique en la entrada" << "----" << endl << endl;
                break;
            case 4:
                sudoku = leer_archivo("Entrada.txt", n, symbol);
                imprimir_sudoku(sudoku, n);
                break;
            case 5:
                sudoku = leer_archivo("Entrada.txt", n, symbol);
                celdas_vacias = iniciar_celdas(sudoku, n);
                imprimir_celdas_vacias(celdas_vacias);
                break;
        }
        cout << endl << "----------------" << endl << endl << "Entrada: " << endl << endl;
        sudoku = leer_archivo("Entrada.txt", n, symbol);
        imprimir_sudoku(sudoku, n);

        cout << endl << "Escoja una opción: " << endl;
        cout << "1. Resolver sudoku" << endl << "2. Validar sudoku" << endl << "3. Generar sudoku" << endl << "4. Imprimir sudoku" << endl <<  "0. Salir del programa" << endl;
        cin >> opcion;
    }

    cout << endl << "Programa finalizado con éxito" << endl << endl;
    return 0;
}