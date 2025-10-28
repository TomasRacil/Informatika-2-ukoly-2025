#include <iostream>
#include <iomanip>
#include <new> // for std::nothrow

int** allocateMatrix(int rows, int cols) {
    if (rows <= 0 || cols <= 0) return nullptr;

    int** matrix = new(std::nothrow) int*[rows];
    if (!matrix) return nullptr;

    for (int i = 0; i < rows; i++) {
        matrix[i] = new(std::nothrow) int[cols];
        if (!matrix[i]) {
            // On failure, clean up previously allocated rows
            for (int j = 0; j < i; j++) {
                delete[] matrix[j];
            }
            delete[] matrix;
            return nullptr;
        }
        // Initialize row to zero
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = 0;
        }
    }
    return matrix;
}

void deallocateMatrix(int** matrix, int rows) {
    if (!matrix) return;
    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void printMatrix(int** matrix, int rows, int cols) {
    if (!matrix) return;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << std::setw(4) << matrix[i][j];
        }
        std::cout << '\n';
    }
}

int** addMatrices(int** matrixA, int** matrixB, int rows, int cols) {
    if (!matrixA || !matrixB) return nullptr;
    int** result = allocateMatrix(rows, cols);
    if (!result) return nullptr;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            result[i][j] = matrixA[i][j] + matrixB[i][j];
    return result;
}

int** subtractMatrices(int** matrixA, int** matrixB, int rows, int cols) {
    if (!matrixA || !matrixB) return nullptr;
    int** result = allocateMatrix(rows, cols);
    if (!result) return nullptr;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            result[i][j] = matrixA[i][j] - matrixB[i][j];
    return result;
}

int** multiplyMatrices(int** matrixA, int** matrixB, int rowsA, int colsA, int colsB) {
    if (!matrixA || !matrixB) return nullptr;
    int** result = allocateMatrix(rowsA, colsB);
    if (!result) return nullptr;
    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB; j++) {
            int sum = 0;
            for (int k = 0; k < colsA; k++) {
                sum += matrixA[i][k] * matrixB[k][j];
            }
            result[i][j] = sum;
        }
    }
    return result;
}

int** transposeMatrix(int** matrix, int rows, int cols) {
    if (!matrix) return nullptr;
    int** result = allocateMatrix(cols, rows);
    if (!result) return nullptr;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            result[j][i] = matrix[i][j];
    return result;
}

int main() {
    // small test: A (2x3) * B (3x2) -> C (2x2)
    int rowsA = 2, colsA = 3;
    int rowsB = 3, colsB = 2;

    int** A = allocateMatrix(rowsA, colsA);
    int** B = allocateMatrix(rowsB, colsB);
    if (!A || !B) {
        std::cerr << "Allocation failed\n";
        deallocateMatrix(A, rowsA);
        deallocateMatrix(B, rowsB);
        return 1;
    }

    // fill A
    int val = 1;
    for (int i = 0; i < rowsA; ++i)
        for (int j = 0; j < colsA; ++j)
            A[i][j] = val++;

    // fill B
    val = 1;
    for (int i = 0; i < rowsB; ++i)
        for (int j = 0; j < colsB; ++j)
            B[i][j] = val++;

    std::cout << "Matrix A:\n";
    printMatrix(A, rowsA, colsA);
    std::cout << "Matrix B:\n";
    printMatrix(B, rowsB, colsB);

    int** C = multiplyMatrices(A, B, rowsA, colsA, colsB);
    if (!C) {
        std::cerr << "Multiplication failed\n";
        deallocateMatrix(A, rowsA);
        deallocateMatrix(B, rowsB);
        return 1;
    }

    std::cout << "A * B =\n";
    printMatrix(C, rowsA, colsB);

    // cleanup
    deallocateMatrix(A, rowsA);
    deallocateMatrix(B, rowsB);
    deallocateMatrix(C, rowsA);
    return 0;
}