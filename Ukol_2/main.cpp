#include <iostream>
#include <iomanip> // Pro std::setw

/**
 * @brief Alokuje paměť pro matici o 'rows' řádcích a 'cols' sloupcích.
 * Inicializuje všechny prvky na 0.
 * @param rows Počet řádků.
 * @param cols Počet sloupců.
 * @return Ukazatel na alokovanou matici (int**).
 */
int** allocateMatrix(int rows, int cols) {
    int** matrix = new int*[rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
        // Initialize all elements to 0
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = 0;
        }
    }
    return matrix;
}

/**
 * @brief Uvolní paměť alokovanou pro matici.
 * @param matrix Ukazatel na matici.
 * @param rows Počet řádků matice.
 */
void deallocateMatrix(int** matrix, int rows) {
    if (matrix != nullptr) {
        for (int i = 0; i < rows; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }
}

/**
 * @brief Vytiskne matici do konzole.
 * @param matrix Ukazatel na matici.
 * @param rows Počet řádků.
 * @param cols Počet sloupců.
 */
void printMatrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << std::setw(4) << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

/**
 * @brief Sečte dvě matice A a B.
 * @param matrixA První matice.
 * @param matrixB Druhá matice.
 * @param rows Počet řádků.
 * @param cols Počet sloupců.
 * @return Ukazatel na novou matici, která je výsledkem součtu.
 */
int** addMatrices(int** matrixA, int** matrixB, int rows, int cols) {
    int** result = allocateMatrix(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = matrixA[i][j] + matrixB[i][j];
        }
    }
    return result;
}

/**
 * @brief Odečte matici B od matice A (A - B).
 * @param matrixA První matice.
 * @param matrixB Druhá matice.
 * @param rows Počet řádků.
 * @param cols Počet sloupců.
 * @return Ukazatel na novou matici, která je výsledkem rozdílu.
 */
int** subtractMatrices(int** matrixA, int** matrixB, int rows, int cols) {
    int** result = allocateMatrix(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = matrixA[i][j] - matrixB[i][j];
        }
    }
    return result;
}

/**
 * @brief Vynásobí matici A maticí B (A * B).
 * @param matrixA První matice.
 * @param matrixB Druhá matice.
 * @param rowsA Počet řádků matice A.
 * @param colsA Počet sloupců matice A (a řádků matice B).
 * @param colsB Počet sloupců matice B.
 * @return Ukazatel na novou matici, která je výsledkem násobení.
 */
int** multiplyMatrices(int** matrixA, int** matrixB, int rowsA, int colsA, int colsB) {
    int** result = allocateMatrix(rowsA, colsB);
    
    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB; j++) {
            result[i][j] = 0;
            for (int k = 0; k < colsA; k++) {
                result[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
    return result;
}
/**
 * @brief Vytvoří transponovanou matici.
 * @param matrix Původní matice.
 * @param rows Počet řádků původní matice.
 * @param cols Počet sloupců původní matice.
 * @return Ukazatel na novou transponovanou matici (cols x rows).
 */
int** transposeMatrix(int** matrix, int rows, int cols) {
    int** result = allocateMatrix(cols, rows);
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[j][i] = matrix[i][j];
        }
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