#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include "resolver_sudoku.cpp"
#include "validar_sudoku.cpp"
#include <random>

using namespace std;

vector<vector<int>> generar_sudoku(int n, int dificultad, vector<Celda> celdas_vacias)
{
    random_device rd;
    mt19937 generator(rd());
    vector<vector<int>> sudoku(pow(n, 2), vector<int>(pow(n,2), 0));
    double porcentaje;
    int casillas;
    int fila_random;
    int columna_random;
    int numero_random;
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

    for(int i = 0; i < casillas; i++)
    {
        fila_random = distribution(generator);
        columna_random = distribution(generator);
        numero_random = distri(generator);
        while(!es_numero_valido(sudoku, n, fila_random, columna_random, numero_random))
        {
            fila_random = distribution(generator);
            columna_random = distribution(generator);
            numero_random = distri(generator);
        }
        sudoku[fila_random][columna_random] = numero_random;
        cout << "Celda generada: " << fila_random << ", " 
                    << columna_random << endl << "Numero: " << numero_random << endl;
    }
    copia = sudoku;
    imprimir_sudoku(sudoku, n);

    celdas_vacias = iniciar_celdas(sudoku, n);
    for(int i = 0; i < celdas_vacias.size(); i ++)
    {
        Celda cel = celdas_vacias[i];
        cout << "Fila: " << cel.fila << ", Columna: " << cel.columna << ", Candidatos: ";
        for(int candidato : cel.candidatos)
        {
            cout << candidato << " ";
        }
        cout << endl;
    }
    while(!resolver_sudoku(sudoku, n, celdas_vacias, 0))
    {
        sudoku.clear();
        for(int i = 0; i < 3; i++)
        {
            fila_random = distribution(generator);
            columna_random = distribution(generator);
            numero_random = distri(generator);
            while(!es_numero_valido(sudoku, n, fila_random, columna_random, numero_random))
            {
                fila_random = distribution(generator);
                columna_random = distribution(generator);
                numero_random = distri(generator);
            }
            sudoku[fila_random][columna_random] = numero_random;
        }
        copia = sudoku;
    }

    
    cout << "Sudoku generado con éxito" << endl;
    
    /* for(int i = 0; i < casillas; i++)
    {
        fila_random = distribution(generator);
        columna_random = distribution(generator);
        while(copia[fila_random][columna_random] != 0)
        {
            fila_random = distribution(generator);
            columna_random = distribution(generator);
        }
        copia[fila_random][columna_random] = sudoku[fila_random][columna_random];
    } */
    return copia;
}

void sobreescribir_archivo(string nombre_archivo, vector<vector<int>> sudoku, int n)
{
    ofstream file(nombre_archivo);
    string numero;
    double numero_digitos = log10(pow(n, 2)) + 1;
    int round_numero = round(numero_digitos);
    string ceros(round_numero - 1, '0');

    if(file.is_open())
    {
        file << n << endl;
        for(int i = 0; i < sudoku.size(); i++)
        {
            for(int j = 0; j < sudoku.size(); j++)
            {
                if(sudoku[i][j] == 0)
                {
                    numero = string(round_numero, '-');
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

vector<vector<int>> leer_archivo(string nombre_archivo, int& n, double& symbol)
{
    ifstream file(nombre_archivo, ios::in);
    string line;
    vector<vector<int>> sudoku;
    
    if(file.is_open())
    {

        getline(file, line);
        n = stoi(line);
        symbol = log10(pow(n, 2)) + 1;
        int round_numero = round(symbol);

        sudoku.resize(pow(n, 2), vector<int>(pow(n, 2)));

        for(int i = 0; i < sudoku.size(); i++)
        {
            getline(file, line);
            vector<string> subcadenas;
            for (int j = 0; j < line.length(); j += 2) 
            {
                string subcadena = line.substr(j, round_numero);

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
    double symbol;
    int opcion;
    vector<vector<int>> sudoku;
    vector<Celda> celdas_vacias;
    
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
                sudoku = leer_archivo("Entrada.txt", n, symbol);
                celdas_vacias = iniciar_celdas(sudoku, n);
                if(resolver_sudoku(sudoku, n, celdas_vacias, 0))
                {
                    cout << endl << "-----" << "¡Sudoku resuelto!" << "-----" << endl << endl;
                    imprimir_sudoku(sudoku, n);
                    sobreescribir_archivo("Entrada.txt", sudoku, n);
                }
                else
                {
                    cout << "No se pudo resolver el sudoku" << endl;
                    imprimir_sudoku(sudoku, n);
                }
                break;
            case 2:
                sudoku = leer_archivo("Entrada.txt", n, symbol);
                if(validar_sudoku(sudoku, n))
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
            case 3:
                int dificultad;
                cout << "Seleccione la dificultad: " << endl 
                        << "1. Fácil" << endl << "2. Normal" << endl << "3. Difícil" << endl;
                cin >> dificultad;
                cout << "Seleccione el tamaño del sudoku representado por un dígito: " << endl;
                cin >> n;
                
                sudoku = generar_sudoku(n, dificultad, celdas_vacias);
                sobreescribir_archivo("Entrada.txt", sudoku, n);
                sudoku = leer_archivo("Entrada.txt", n, symbol);
                imprimir_sudoku(sudoku, n);
                break;
            case 4:
                sudoku = leer_archivo("Entrada.txt", n, symbol);
                imprimir_sudoku(sudoku, n);
                break;
        }
        cout << endl << "Escoja una opción: " << endl;
        cout << "1. Resolver sudoku" << endl << "2. Validar sudoku" << endl << "3. Generar sudoku" << endl << "4. Imprimir sudoku" << endl <<  "0. Salir del programa" << endl;
        cin >> opcion;
    }

    /* vector<vector<int>> sudoku {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    }; */

   /*  vector<vector<int>> sudoku; 
    vector<int> numeros = {1,2,3,4,5,6,7,8,9};
    sudoku = generar_sudoku(n, 1, numeros);
    imprimir_sudoku(sudoku, n); */
    cout << endl << "Programa finalizado con éxito" << endl << endl;
    return 0;
}