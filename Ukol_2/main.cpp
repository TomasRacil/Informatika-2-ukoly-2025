#include <iostream>
#include <iomanip> // Pro std::setw
#include <cassert>

/**
 * @brief Alokuje paměť pro matici o 'rows' řádcích a 'cols' sloupcích.
 * Inicializuje všechny prvky na 0.
 * @param rows Počet řádků.
 * @param cols Počet sloupců.
 * @return Ukazatel na alokovanou matici (int**). Vrací nullptr při chybných rozměrech.
 */
int** allocateMatrix(int rows, int cols) {
    if (rows <= 0 || cols <= 0) {
        return nullptr;
    }

    // 1) Alokujeme pole ukazatelů na řádky
    int** matrix = new int*[rows];

    // 2) Pro každý řádek alokujeme pole intů (sloupce) a inicializujeme na 0
    for (int i = 0; i < rows; ++i) {
        matrix[i] = new int[cols];
        for (int j = 0; j < cols; ++j) {
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
    if (matrix == nullptr) return;
    if (rows <= 0) {
        // Nic k uvolnění (nebo uživatel poslal špatné rows)
        delete[] matrix; // bezpečně uvolníme i pole pointerů
        return;
    }

    // 1) Uvolníme paměť pro každý řádek
    for (int i = 0; i < rows; ++i) {
        delete[] matrix[i];
    }
    // 2) Uvolníme pole ukazatelů na řádky
    delete[] matrix;
}

/**
 * @brief Vytiskne matici do konzole.
 * @param matrix Ukazatel na matici.
 * @param rows Počet řádků.
 * @param cols Počet sloupců.
 */
void printMatrix(int** matrix, int rows, int cols) {
    if (matrix == nullptr) {
        std::cout << "(null matrix)\n";
        return;
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << std::setw(4) << matrix[i][j];
        }
        std::cout << '\n';
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
    if (matrixA == nullptr || matrixB == nullptr || rows <= 0 || cols <= 0) {
        return nullptr;
    }

    int** result = allocateMatrix(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
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
    if (matrixA == nullptr || matrixB == nullptr || rows <= 0 || cols <= 0) {
        return nullptr;
    }

    int** result = allocateMatrix(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
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
    if (matrixA == nullptr || matrixB == nullptr || rowsA <= 0 || colsA <= 0 || colsB <= 0) {
        return nullptr;
    }

    // Výsledek bude rozměr rowsA x colsB
    int** result = allocateMatrix(rowsA, colsB);

    // Klasické maticové násobení: result[i][j] = sum_k A[i][k] * B[k][j]
    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < colsB; ++j) {
            int sum = 0;
            for (int k = 0; k < colsA; ++k) {
                sum += matrixA[i][k] * matrixB[k][j];
            }
            result[i][j] = sum;
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
    if (matrix == nullptr || rows <= 0 || cols <= 0) {
        return nullptr;
    }

    int** result = allocateMatrix(cols, rows);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result[j][i] = matrix[i][j];
        }
    }
    return result;
}


// --- Hlavní program (pro vaše vlastní testování) ---

#ifndef __TEST__
int main() {
    // Zde si můžete vytvořit vlastní testovací scénář

    int rowsM = 2, colsM = 3;
    int** matM = allocateMatrix(rowsM, colsM);
    matM[0][0] = 6; matM[0][1] = 5; matM[0][2] = 4;
    matM[1][0] = 3; matM[1][1] = 2; matM[1][2] = 1;

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

    std::cout << "\nMatice M:" << std::endl;
    printMatrix(matM, rowsM, colsM);


    // Test násobení
    //int** matC = multiplyMatrices(matA, matB, rowsA, colsA, colsB);
    //::cout << "\nVysledek A * B:" << std::endl;
    //(matC, rowsA, colsB);


    // Test transpozice
    //int** matT = transposeMatrix(matA, rowsA, colsA);
    //::cout << "\nTransponovana matice A:" << std::endl;
    //printMatrix(matT, colsA, rowsA);

    //Test sčítání
    int** matS = addMatrices(matA, matM, rowsA, colsA);
    std::cout << "\nVysledek A + M:" << std::endl;
    printMatrix(matS, rowsA, colsA);

    //Test odčítání
    int** matO = subtractMatrices(matA, matM, rowsA, colsA);
    std::cout << "\nVysledek A - M:" << std::endl;
    printMatrix(matO, rowsA, colsA);

    // Uvolnění paměti
    deallocateMatrix(matA, rowsA);
    deallocateMatrix(matB, rowsB);
    //deallocateMatrix(matC, rowsA);
    //deallocateMatrix(matT, colsA);
    deallocateMatrix(matM, colsM);
    deallocateMatrix(matS, rowsA);
    deallocateMatrix(matO, rowsA);

    return 0;
}
#endif // __TEST__
