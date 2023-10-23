#include <iostream>
#include <vector>
#include <set> 
#include <cmath>

using namespace std;

bool recorrer(vector<vector<int>> sudoku, int n, int num, int fila, int columna)
{
    cout << "Region: " << n << ", Numero: " << num << ", Fila: " << fila << ", Columna: " << columna << endl;
    set<int> verificados;

    //loop para revisar que el numero no este repetido en la fila
    cout << endl << "Verificando fila..." << endl;
	for(int i = 0; i < sudoku.size(); i++)
    {
        if(sudoku[fila][sudoku.size() - 1] == num)
        {
            return false;
        }
        if(sudoku[fila][i] == num)
        {
            if(verificados.count(num) > 0)
            {
                return false;
            }
            verificados.insert(num);
        }
    }
    verificados.clear();

    //loop para revisar que el numero no este repetido en la columna
    cout << endl << "Verificando columna..." << endl;
	for(int i = 0; i < sudoku.size(); i++)
    {
        if(sudoku[sudoku.size() - 1][columna] == num)
        {
            return false;
        }
        if(sudoku[i][columna] == num)
        {
            if(verificados.count(num) > 0)
            {
                return false;
            }
            verificados.insert(num);
        }
    }
    verificados.clear();

    //loop para revisar que el numero no este repetido en la region 
    cout << endl << "Verificando region..." << endl;
    int fila_region = (fila / n) * n;
    int columna_region = (columna / n) * n;
    cout << "Empieza desde la fila: " << fila_region << " y la columna: " << columna_region << endl;

    for(int i = fila_region; i < fila_region + n; fila_region++)
    {
        for(int j = columna_region; j < columna_region + n; columna_region++)
        {
            if(sudoku[n - 1][n - 1] == num)
            {
                return false; 
            }
            if(sudoku[i][j] == num)
            {
                if(verificados.count(num) > 0)
                {
                    return false;
                }
                verificados.insert(num);
            }
        }
    }
    return true;
}

bool verificar_todo(vector<vector<int>> sudoku, int n) 
{
    set<int> verificados;

    //Se revisa que no haya ningun espacio en blanco
    for(int i = 0; i < sudoku.size(); i++)
    {
        for(int j = 0; j < sudoku.size(); j++)
        {
            if(sudoku[i][j] == 0)
            {
                return false;
            }
        }
    }

    //se verifican que los numeros no se repitan en las columnas
    for(int i = 0; i < sudoku.size(); i++)
    {
        for(int j = 0; j < sudoku.size(); j++)
        {
            verificados.insert(sudoku[j][i]);
        }
        for(int j = 0; j < verificados.size(); j++)
        {
            if(verificados.count(j) > 1)
            {
                return false;
            }
        }
        verificados.clear();
    }

    //Se verifica que los numeros no se repitan en las filas
    for(int i = 0; i < sudoku.size(); i++)
    {
        for(int j = 0; j < sudoku.size(); j++)
        {
            verificados.insert(sudoku[i][j]);
        }
        for(int j = 0; j < verificados.size(); j++)
        {
            if(verificados.count(j) > 1)
            {
                return false;
            }
        }
        verificados.clear();
    }

    //Se verifica que en cada region, no se repita ningun numero
    for(int fila_region = 0; fila_region < sudoku.size(); fila_region += n)
    {
        for(int columna_region = 0; columna_region < sudoku.size(); columna_region += n)
        {
            for(int i = fila_region; i < fila_region + n; fila_region++)
            {
                for(int j = columna_region; j < columna_region + n; columna_region++)
                {
                    verificados.insert(sudoku[i][j]);
                }
            }
            for(int k = 0; k < verificados.size(); k++)
            {
                if(verificados.count(k) > 1)
                {
                    return false;
                }
            }
            verificados.clear();
        }
    }
    return true;
}

void resolver(vector<vector<int>> sudoku, int n, vector<int> numeros, int fila, int columna, int num_k, int ultimo_i, int ultimo_j)
{
	cout << "Resolviendo..." << endl;
    if(verificar_todo(sudoku, n))
    {
    	cout << "¡Sudoku resuelto!" << endl;
        return;
    }

	cout << "No esta bien" << endl;
    cout << "Fila: " << fila << ", Columna: " << columna << " y el numero es: " << sudoku[fila][columna] << endl;
    if(sudoku[fila][columna] == 0)
    { 
        for(int k = num_k; k < numeros.size(); k++)
        {
            sudoku[fila][columna] = numeros[k];
            cout << "Verificando si el numero " << numeros[k] << " se puede poner..." << endl;
            if(recorrer(sudoku, n, sudoku[fila][columna], fila, columna))
            {
            	cout << "El numero cambio a: " << sudoku[fila][columna] << endl;
            	ultimo_i = fila;
                ultimo_j = columna;
                
                if(columna == sudoku.size() - 1)
                {
                    resolver(sudoku, n, numeros, fila + 1, 0, 1, ultimo_i, ultimo_j);
                }
                else
                {
                    resolver(sudoku, n, numeros, fila, columna + 1, 1, ultimo_i, ultimo_j);
                }
            }
            else
            {
            	cout << sudoku[fila][columna] << " Numero invalido " << endl;
                sudoku[fila][columna] = 0;
            }
        } 
    }
    else
    {
    	cout << "El numero no esta en blanco" << endl;
    	resolver(sudoku, n, numeros, fila, columna + 1, 0, ultimo_i, ultimo_j);
        
    }
}


int main()
{
    vector<vector<int>> sudoku = 
    {
        {6,0,1,0,0,4,0,8,0},
        {0,4,9,7,3,0,0,0,0},
        {8,2,3,0,0,0,0,4,9},
        {0,0,4,0,0,0,0,9,6},
        {0,0,7,0,0,0,2,0,0},
        {9,8,0,0,0,0,3,0,0},
        {4,1,0,0,0,0,9,6,5},
        {0,0,0,0,4,1,8,3,0},
        {0,5,0,2,0,0,4,0,7}
    };
    
    int n = 3;
    
    vector<int> numeros;
    for(int i = 1; i <= pow(n, 2); i++)
    {
        numeros.push_back(i);
    }
        
    
    int ultimo_i = 0;
    int ultimo_j = 0;
    resolver(sudoku, n, numeros, 0, 0, 0, ultimo_i, ultimo_j);

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
    return 0;
}
