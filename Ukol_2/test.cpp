#include "gtest/gtest.h"
#include "main.cpp"

// Pomocná funkce pro porovnání dvou matic
bool matricesEqual(int** matrixA, int** matrixB, int rows, int cols) {
    if (!matrixA || !matrixB) return false;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (matrixA[i][j] != matrixB[i][j]) {
                return false;
            }
        }
    }
    return true;
}

// Test Fixture pro operace
class MatrixOperationsTest : public ::testing::Test {
protected:
    int** matA;
    int** matB;
    int** matIdent;
    int rows = 2;
    int cols = 2;

    void SetUp() override {
        matA = allocateMatrix(rows, cols);
        matB = allocateMatrix(rows, cols);
        matIdent = allocateMatrix(rows, cols);

        // matA = {{1, 2}, {3, 4}}
        matA[0][0] = 1; matA[0][1] = 2;
        matA[1][0] = 3; matA[1][1] = 4;

        // matB = {{5, 6}, {7, 8}}
        matB[0][0] = 5; matB[0][1] = 6;
        matB[1][0] = 7; matB[1][1] = 8;
        
        // matIdent = {{1, 0}, {0, 1}}
        matIdent[0][0] = 1; matIdent[0][1] = 0;
        matIdent[1][0] = 0; matIdent[1][1] = 1;
    }

    void TearDown() override {
        deallocateMatrix(matA, rows);
        deallocateMatrix(matB, rows);
        deallocateMatrix(matIdent, rows);
    }
};

TEST(AllocationTest, AllocateAndDeallocate) {
    int rows = 5, cols = 10;
    int** matrix = allocateMatrix(rows, cols);
    ASSERT_NE(matrix, nullptr);
    ASSERT_NE(matrix[0], nullptr);
    
    // Otestujeme, zda je inicializováno na 0
    EXPECT_EQ(matrix[0][0], 0);
    EXPECT_EQ(matrix[rows - 1][cols - 1], 0);

    // Zapíšeme hodnotu
    matrix[1][1] = 123;
    EXPECT_EQ(matrix[1][1], 123);
    
    deallocateMatrix(matrix, rows);
}

TEST_F(MatrixOperationsTest, Addition) {
    int** expected = allocateMatrix(rows, cols);
    // {{6, 8}, {10, 12}}
    expected[0][0] = 6; expected[0][1] = 8;
    expected[1][0] = 10; expected[1][1] = 12;

    int** result = addMatrices(matA, matB, rows, cols);
    EXPECT_TRUE(matricesEqual(result, expected, rows, cols));

    deallocateMatrix(expected, rows);
    deallocateMatrix(result, rows);
}

TEST_F(MatrixOperationsTest, Subtraction) {
    int** expected = allocateMatrix(rows, cols);
    // {{-4, -4}, {-4, -4}}
    expected[0][0] = -4; expected[0][1] = -4;
    expected[1][0] = -4; expected[1][1] = -4;

    int** result = subtractMatrices(matA, matB, rows, cols);
    EXPECT_TRUE(matricesEqual(result, expected, rows, cols));

    deallocateMatrix(expected, rows);
    deallocateMatrix(result, rows);
}

TEST_F(MatrixOperationsTest, Transpose) {
    int** expected = allocateMatrix(cols, rows); // Rozměry jsou prohozené
    // {{1, 3}, {2, 4}}
    expected[0][0] = 1; expected[0][1] = 3;
    expected[1][0] = 2; expected[1][1] = 4;

    int** result = transposeMatrix(matA, rows, cols);
    EXPECT_TRUE(matricesEqual(result, expected, cols, rows)); // Kontrola s prohozenými rozměry

    deallocateMatrix(expected, cols);
    deallocateMatrix(result, cols);
}

TEST_F(MatrixOperationsTest, MultiplicationIdentity) {
    // Násobení identitou by mělo vrátit původní matici
    int** result = multiplyMatrices(matA, matIdent, rows, cols, cols);
    EXPECT_TRUE(matricesEqual(result, matA, rows, cols));
    deallocateMatrix(result, rows);
}

TEST_F(MatrixOperationsTest, MultiplicationComplex) {
    int** expected = allocateMatrix(rows, cols);
    // A * B = {{1*5+2*7, 1*6+2*8}, {3*5+4*7, 3*6+4*8}}
    //       = {{19, 22}, {43, 50}}
    expected[0][0] = 19; expected[0][1] = 22;
    expected[1][0] = 43; expected[1][1] = 50;

    int** result = multiplyMatrices(matA, matB, rows, cols, cols);
    EXPECT_TRUE(matricesEqual(result, expected, rows, cols));

    deallocateMatrix(expected, rows);
    deallocateMatrix(result, rows);
}

TEST(MultiplicationNonSquare, Multiply) {
    int rowsA = 2, colsA = 3;
    int rowsB = 3, colsB = 2;

    int** matA = allocateMatrix(rowsA, colsA);
    // {{1, 2, 3}, {4, 5, 6}}
    matA[0][0] = 1; matA[0][1] = 2; matA[0][2] = 3;
    matA[1][0] = 4; matA[1][1] = 5; matA[1][2] = 6;

    int** matB = allocateMatrix(rowsB, colsB);
    // {{7, 8}, {9, 10}, {11, 12}}
    matB[0][0] = 7; matB[0][1] = 8;
    matB[1][0] = 9; matB[1][1] = 10;
    matB[2][0] = 11; matB[2][1] = 12;

    int** expected = allocateMatrix(rowsA, colsB);
    // {{58, 64}, {139, 154}}
    expected[0][0] = 58; expected[0][1] = 64;
    expected[1][0] = 139; expected[1][1] = 154;

    int** result = multiplyMatrices(matA, matB, rowsA, colsA, colsB);
    EXPECT_TRUE(matricesEqual(result, expected, rowsA, colsB));

    deallocateMatrix(matA, rowsA);
    deallocateMatrix(matB, rowsB);
    deallocateMatrix(expected, rowsA);
    deallocateMatrix(result, rowsA);
}