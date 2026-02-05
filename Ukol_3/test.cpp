#include "gtest/gtest.h"
#include "main.cpp" 
#include <stdexcept> // Pro std::out_of_range

bool matricesEqual(const Matrix& matrixA, const Matrix& matrixB) {
    if (matrixA.getRows() != matrixB.getRows() || matrixA.getCols() != matrixB.getCols()) {
        return false;
    }
    for (int i = 0; i < matrixA.getRows(); ++i) {
        for (int j = 0; j < matrixA.getCols(); ++j) {
            try {
                if (matrixA.getValue(i, j) != matrixB.getValue(i, j)) {
                    return false;
                }
            } catch (const std::exception&) {
                return false; 
            }
        }
    }
    return true;
}

class MatrixOperationsTest : public ::testing::Test {
protected:
    Matrix* matA;
    Matrix* matB;
    Matrix* matIdent;

    void SetUp() override {
        matA = new Matrix(2, 2);
        matB = new Matrix(2, 2);
        matIdent = new Matrix(2, 2);

        // matA = {{1, 2}, {3, 4}}
        matA->setValue(0, 0, 1); matA->setValue(0, 1, 2);
        matA->setValue(1, 0, 3); matA->setValue(1, 1, 4);

        // matB = {{5, 6}, {7, 8}}
        matB->setValue(0, 0, 5); matB->setValue(0, 1, 6);
        matB->setValue(1, 0, 7); matB->setValue(1, 1, 8);
        
        // matIdent = {{1, 0}, {0, 1}}
        matIdent->setValue(0, 0, 1); matIdent->setValue(0, 1, 0);
        matIdent->setValue(1, 0, 0); matIdent->setValue(1, 1, 1);
    }

    void TearDown() override {
        delete matA;
        delete matB;
        delete matIdent;
    }
};

TEST(AllocationTest, ConstructorAndGetters) {
    int rows = 5, cols = 10;
    Matrix mat(rows, cols);
    
    ASSERT_EQ(mat.getRows(), rows);
    ASSERT_EQ(mat.getCols(), cols);
    
    ASSERT_NO_THROW(mat.getValue(0, 0));
    EXPECT_EQ(mat.getValue(0, 0), 0);
    
    ASSERT_NO_THROW(mat.getValue(rows - 1, cols - 1));
    EXPECT_EQ(mat.getValue(rows - 1, cols - 1), 0);

    ASSERT_NO_THROW(mat.setValue(1, 1, 123));
    ASSERT_NO_THROW(mat.getValue(1, 1));
    EXPECT_EQ(mat.getValue(1, 1), 123);
}

TEST(AllocationTest, ConstructorNegativeSize) {
    Matrix mat(-5, -10);
    ASSERT_EQ(mat.getRows(), 0);
    ASSERT_EQ(mat.getCols(), 0);
    
    ASSERT_THROW(mat.getValue(0, 0), std::out_of_range);
    ASSERT_THROW(mat.setValue(0, 0, 1), std::out_of_range);
}

TEST(AllocationTest, CopyConstructor) {
    Matrix matA(2, 2);
    matA.setValue(0, 0, 1);
    matA.setValue(1, 1, 4);

    Matrix matB = matA;

    ASSERT_EQ(matB.getRows(), 2);
    ASSERT_EQ(matB.getCols(), 2);
    ASSERT_TRUE(matricesEqual(matA, matB));

    matA.setValue(0, 0, 99);
    
    ASSERT_NO_THROW(matB.getValue(0, 0));
    EXPECT_NE(matB.getValue(0, 0), 99);
    EXPECT_EQ(matB.getValue(0, 0), 1);
}

TEST(AllocationTest, InvalidAccess) {
    Matrix mat(3, 3);
    
    ASSERT_THROW(mat.getValue(10, 10), std::out_of_range);
    ASSERT_THROW(mat.getValue(-1, 0), std::out_of_range);
    ASSERT_THROW(mat.getValue(0, -1), std::out_of_range);
    ASSERT_THROW(mat.getValue(3, 0), std::out_of_range);
    ASSERT_THROW(mat.getValue(0, 3), std::out_of_range);

    ASSERT_THROW(mat.setValue(10, 10, 100), std::out_of_range);
    ASSERT_THROW(mat.setValue(-1, 0, 100), std::out_of_range);
    ASSERT_THROW(mat.setValue(0, -1, 100), std::out_of_range);
    ASSERT_THROW(mat.setValue(3, 0, 100), std::out_of_range);
    ASSERT_THROW(mat.setValue(0, 3, 100), std::out_of_range);

    ASSERT_NO_THROW(mat.getValue(1, 1));
    ASSERT_NO_THROW(mat.setValue(1, 1, 100));
}

TEST_F(MatrixOperationsTest, Addition) {
    Matrix expected(2, 2);
    // {{6, 8}, {10, 12}}
    expected.setValue(0, 0, 6); expected.setValue(0, 1, 8);
    expected.setValue(1, 0, 10); expected.setValue(1, 1, 12);

    Matrix result = matA->add(*matB);
    
    ASSERT_EQ(result.getRows(), 2);
    ASSERT_EQ(result.getCols(), 2);

    EXPECT_TRUE(matricesEqual(result, expected));
}

TEST_F(MatrixOperationsTest, AdditionInvalid) {
    Matrix smallMat(1, 1);
    Matrix result = matA->add(smallMat);
    EXPECT_EQ(result.getRows(), 0);
    EXPECT_EQ(result.getCols(), 0);
}

TEST_F(MatrixOperationsTest, Subtraction) {
    Matrix expected(2, 2);
    // {{-4, -4}, {-4, -4}}
    expected.setValue(0, 0, -4); expected.setValue(0, 1, -4);
    expected.setValue(1, 0, -4); expected.setValue(1, 1, -4);

    Matrix result = matA->subtract(*matB);
    
    ASSERT_EQ(result.getRows(), 2);
    ASSERT_EQ(result.getCols(), 2);
    
    EXPECT_TRUE(matricesEqual(result, expected));
}

TEST_F(MatrixOperationsTest, Transpose) {
    Matrix expected(2, 2);
    // {{1, 3}, {2, 4}}
    expected.setValue(0, 0, 1); expected.setValue(0, 1, 3);
    expected.setValue(1, 0, 2); expected.setValue(1, 1, 4);

    Matrix result = matA->transpose();
    
    ASSERT_EQ(result.getRows(), 2);
    ASSERT_EQ(result.getCols(), 2);

    EXPECT_TRUE(matricesEqual(result, expected));
}

TEST(TransposeNonSquare, Transpose) {
    Matrix matA(2, 3);
    matA.setValue(0, 0, 1); matA.setValue(0, 1, 2); matA.setValue(0, 2, 3);
    matA.setValue(1, 0, 4); matA.setValue(1, 1, 5); matA.setValue(1, 2, 6);
    
    Matrix expected(3, 2);
    expected.setValue(0, 0, 1); expected.setValue(0, 1, 4);
    expected.setValue(1, 0, 2); expected.setValue(1, 1, 5);
    expected.setValue(2, 0, 3); expected.setValue(2, 1, 6);

    Matrix result = matA.transpose();
    
    ASSERT_EQ(result.getRows(), 3);
    ASSERT_EQ(result.getCols(), 2);
    
    EXPECT_TRUE(matricesEqual(result, expected));
}


TEST_F(MatrixOperationsTest, MultiplicationIdentity) {
    Matrix result = matA->multiply(*matIdent);
    
    ASSERT_EQ(result.getRows(), 2);
    ASSERT_EQ(result.getCols(), 2);
    
    EXPECT_TRUE(matricesEqual(result, *matA));
}

TEST_F(MatrixOperationsTest, MultiplicationComplex) {
    Matrix expected(2, 2);
    // A * B = {{1*5+2*7, 1*6+2*8}, {3*5+4*7, 3*6+4*8}}
    //       = {{19, 22}, {43, 50}}
    expected.setValue(0, 0, 19); expected.setValue(0, 1, 22);
    expected.setValue(1, 0, 43); expected.setValue(1, 1, 50);

    Matrix result = matA->multiply(*matB);
    
    ASSERT_EQ(result.getRows(), 2);
    ASSERT_EQ(result.getCols(), 2);
    
    EXPECT_TRUE(matricesEqual(result, expected));
}

TEST(MultiplicationNonSquare, Multiply) {
    Matrix matA(2, 3);
    // {{1, 2, 3}, {4, 5, 6}}
    matA.setValue(0, 0, 1); matA.setValue(0, 1, 2); matA.setValue(0, 2, 3);
    matA.setValue(1, 0, 4); matA.setValue(1, 1, 5); matA.setValue(1, 2, 6);

    Matrix matB(3, 2);
    // {{7, 8}, {9, 10}, {11, 12}}
    matB.setValue(0, 0, 7); matB.setValue(0, 1, 8);
    matB.setValue(1, 0, 9); matB.setValue(1, 1, 10);
    matB.setValue(2, 0, 11); matB.setValue(2, 1, 12);

    Matrix expected(2, 2);
    // {{58, 64}, {139, 154}}
    expected.setValue(0, 0, 58); expected.setValue(0, 1, 64);
    expected.setValue(1, 0, 139); expected.setValue(1, 1, 154);

    Matrix result = matA.multiply(matB);
    
    ASSERT_EQ(result.getRows(), 2);
    ASSERT_EQ(result.getCols(), 2);
    
    EXPECT_TRUE(matricesEqual(result, expected));
}

TEST(MultiplicationNonSquare, MultiplyInvalid) {
    Matrix matA(2, 3);
    Matrix matB(2, 2);
    
    Matrix result = matA.multiply(matB);
    EXPECT_EQ(result.getRows(), 0);
    EXPECT_EQ(result.getCols(), 0);
}
