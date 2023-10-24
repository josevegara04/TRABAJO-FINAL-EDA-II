#include <iostream>
#include <vector>

// Función para imprimir el tablero del Sudoku
void imprimirSudoku(std::vector<std::vector<int>>& sudoku) 
{
    for (int i = 0; i < 9; i++) 
    {
        for (int j = 0; j < 9; j++) 
        {
            std::cout << sudoku[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// Función para verificar si un número es válido en una celda
bool esNumeroValido(const std::vector<std::vector<int>>& sudoku, int fila, int columna, int numero) 
{
    // Verificar la fila
    for (int i = 0; i < 9; i++) 
    {
        if (sudoku[fila][i] == numero) 
        {
            return false;
        }
    }

    // Verificar la columna
    for (int i = 0; i < 9; i++) 
    {
        if (sudoku[i][columna] == numero) 
        {
            return false;
        }
    }

    // Verificar el cuadro 3x3
    int inicioFila = (fila / 3) * 3;
    int inicioColumna = (columna / 3) * 3;
    for (int i = inicioFila; i < inicioFila + 3; i++) 
    {
        for (int j = inicioColumna; j < inicioColumna + 3; j++) 
        {
            if (sudoku[i][j] == numero) 
            {
                return false;
            }
        }
    }

    return true;
}

// Función para resolver el Sudoku recursivamente
bool resolverSudoku(std::vector<std::vector<int>>& sudoku) 
{
    for (int fila = 0; fila < 9; fila++) 
    {
        for (int columna = 0; columna < 9; columna++) 
        {
            if (sudoku[fila][columna] == 0) 
            {  // Celda vacía
                for (int numero = 1; numero <= 9; numero++) 
                {
                    if (esNumeroValido(sudoku, fila, columna, numero)) 
                    {
                        sudoku[fila][columna] = numero;  // Intenta un número

                        if (resolverSudoku(sudoku)) 
                        {  // Llama recursivamente
                            return true;
                        }

                        sudoku[fila][columna] = 0;  // Si no es válido, deshacer
                    }
                }
                return false;  // No se puede resolver
            }
        }
    }
    return true;  // Sudoku resuelto
}

int main() {
    std::vector<std::vector<int>> sudoku = 
    {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    if (resolverSudoku(sudoku)) 
    {
        std::cout << "Sudoku resuelto:" << std::endl;
        imprimirSudoku(sudoku);
    } else 
    {
        std::cout << "No se encontró solución para el Sudoku." << std::endl;
    }

    return 0;
}
