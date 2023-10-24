#include <iostream>
#include <vector>
#include <set> 
#include <cmath>

using namespace std;


vector<vector<int>> resolver_1(vector<vector<int>> sudoku, vector<int> numeros)
{
    set<int> verificados;

    for(int i = 0; i < sudoku.size(); i++)
    {
        for(int j = 0; j < sudoku.size(); j++)
        {
            if(sudoku[i][j] != 0)
            {
                verificados.insert(sudoku[i][j]);
            }
        }
        if(verificados.size() == 8)
        {
            for(int j = 0; j < sudoku.size(); j++)
            {
                if(sudoku[i][j] == 0)
                {
                    for(int num : numeros)
                    {
                        if(!verificados.count(num))
                        {
                            sudoku[i][j] = num;
                        }
                    }
                }
            }
        }
        verificados.clear();
    }

    //Loop que llena columnas con solo un numero faltante
    for(int i = 0; i < sudoku.size(); i++)

    {
        for(int j = 0; j < sudoku.size(); j++)
        {
            if(sudoku[j][i] != 0)
            {
                verificados.insert(sudoku[j][i]);
            }
        }
        if(verificados.size() == 8)
        {
            for(int j = 0; j < sudoku.size(); j++)
            {
                if(sudoku[j][i] == 0)
                {
                    for(int num : numeros)
                    {
                        if(!verificados.count(num))
                        {
                            sudoku[j][i] = num;
                        }
                    }
                }
            }
        }
        verificados.clear();
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
    

    /* vector<vector<int>> sudoku = 
    {
        {6,0,1,0,0,4,0,8,0},
        {0,4,9,7,3,0,0,0,0},
        {8,2,3,0,0,0,0,4,9},
        {0,0,4,0,0,0,0,9,6},
        {0,0,7,0,0,0,2,0,0},
        {9,8,1,2,4,5,3,6,0},
        {4,1,0,0,0,0,9,6,5},
        {0,0,0,0,4,1,8,3,0},
        {0,5,0,2,0,0,4,0,7}
    }; */
    
    int n = 3;
    
    vector<int> numeros;
    for(int i = 1; i <= pow(n, 2); i++)
    {
        numeros.push_back(i);
    }

    
        
    bool cen = true;

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