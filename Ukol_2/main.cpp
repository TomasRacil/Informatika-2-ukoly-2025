#include <iostream>
#include <iomanip> // Pro std::setw


int** allocateMatrix(int rows, int cols) 
{
for (int i = 0; i < rows; ++i)
    {
        matrix[i] = new int[cols];        
        for (int j = 0; j < cols; ++j) 
        {
            matrix[i][j] = 0;               
        }
    }
    return nullptr;
}

/**
 * @brief Uvolní paměť alokovanou pro matici.
 * @param matrix Ukazatel na matici.
 * @param rows Počet řádků matice.
 */
void deallocateMatrix(int** matrix, int rows) 
{
for (int i = 0; i < rows; ++i) 
{
        delete[] matrix[i];
}
 delete[] matrix;
}

void printMatrix(int** matrix, int rows, int cols) 
{
for (int i = 0; i < rows; ++i) 
{
        for (int j = 0; j < cols; ++j) 
        {
            std::cout << std::setw(4) << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


int** addMatrices(int** matrixA, int** matrixB, int rows, int cols) 
{
    int** result = allocateMatrix(rows, cols);
     for (int i = 0; i < rows; ++i) 
     {
        for (int j = 0; j < cols; ++j)
            {
            result[i][j] = matrixA[i][j] + matrixB[i][j];
            }
    }
    return result;
}



int** subtractMatrices(int** matrixA, int** matrixB, int rows, int cols) {
    int** result = allocateMatrix(rows, cols);
 for (int i = 0; i < rows; ++i) 
 {
        for (int j = 0; j < cols; ++j) 
        {
            result[i][j] = matrixA[i][j] - matrixB[i][j];
        }
    }
    return result;
}

int** multiplyMatrices(int** matrixA, int** matrixB, int rowsA, int colsA, int colsB) {
    int** result = allocateMatrix(rowsA, colsB);
for (int i = 0; i < rowsA; ++i) 
{
        for (int j = 0; j < colsB; ++j) 
        {
            for (int k = 0; k < colsA; ++k) 
            {
                result[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    return result;
}


int** transposeMatrix(int** matrix, int rows, int cols) {
    int** result = allocateMatrix(cols, rows);
 for (int i = 0; i < rows; ++i) 
 {
        for (int j = 0; j < cols; ++j) 
        {
            result[j][i] = matrix[i][j];
        }
    return result;
}


// --- Hlavní program (pro vaše vlastní testování) ---

#ifndef __TEST__
int main() {
    // Zde si můžete vytvořit vlastní testovací scénář
    
    int rowsA = 2, colsA = 3;
    int** matA = allocateMatrix(rowsA, colsA);
    matA[0][0] = 1; matA[0][1] = 2; matA[0][2] = 3;
    matA[1][0] = 4; matA[1][1] = 5; matA[1][2] = 6;

    std::cout << "Matice A:" << std::endl;
    printMatrix(matA, rowsA, colsA);

    int rowsB = 3, colsB = 2;
    int** matB = allocateMatrix(rowsB, colsB);
    matB[0][0] = 7; matB[0][1] = 8;
    matB[1][0] = 9; matB[1][1] = 10;
    matB[2][0] = 11; matB[2][1] = 12;

    std::cout << "\nMatice B:" << std::endl;
    printMatrix(matB, rowsB, colsB);

    // Test násobení
    int** matC = multiplyMatrices(matA, matB, rowsA, colsA, colsB);
    std::cout << "\nVysledek A * B:" << std::endl;
    printMatrix(matC, rowsA, colsB);

    // Test transpozice
    int** matT = transposeMatrix(matA, rowsA, colsA);
    std::cout << "\nTransponovana matice A:" << std::endl;
    printMatrix(matT, colsA, rowsA);


    // Uvolnění paměti
    deallocateMatrix(matA, rowsA);
    deallocateMatrix(matB, rowsB);
    deallocateMatrix(matC, rowsA);
    deallocateMatrix(matT, colsA);

    return 0;
}
#endif // __TEST__
