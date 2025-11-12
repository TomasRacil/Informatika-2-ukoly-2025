#include <iostream>
#include <iomanip> // Pro std::setw
#include <stdexcept> // Pro případné výjimky

// ===================================================================
// 1. ČÁST: DEFINICE A IMPLEMENTACE TŘÍDY MATRIX
// ===================================================================

/**
 * @brief Třída reprezentující matici a operace nad ní.
 * Implementace metod je psána přímo v těle třídy.
 */

class Matrix {
private:
    int rows_;
    int cols_;
    int** data_;

    void allocateMatrix() {
        if (rows_ <= 0 || cols_ <= 0) {
            rows_ = 0;
            cols_ = 0;
            data_ = nullptr;
            return;
        }

        data_ = new int*[rows_];
        for (int i = 0; i < rows_; ++i)
            data_[i] = new int[cols_];

        for (int i = 0; i < rows_; ++i)
            for (int j = 0; j < cols_; ++j)
                data_[i][j] = 0;
    }

    void deallocateMatrix() {
        if (data_ != nullptr) {
            for (int i = 0; i < rows_; ++i)
                delete[] data_[i];
            delete[] data_;
            data_ = nullptr;
        }
    }

public:
    Matrix(int rows, int cols) {
        rows_ = rows;
        cols_ = cols;
        data_ = nullptr;
        allocateMatrix();
    }

    ~Matrix() {
        deallocateMatrix();
    }

    Matrix(const Matrix& other) {
        rows_ = other.rows_;
        cols_ = other.cols_;
        data_ = nullptr;
        allocateMatrix();

        if (other.data_ != nullptr && data_ != nullptr) {
            for (int i = 0; i < rows_; ++i)
                for (int j = 0; j < cols_; ++j)
                    data_[i][j] = other.data_[i][j];
        }
    }

    int getRows() const { return rows_; }
    int getCols() const { return cols_; }

    int getValue(int row, int col) const {
        if (data_ == nullptr)
            throw std::out_of_range("Matrix is not initialized");
        if (row < 0 || row >= rows_ || col < 0 || col >= cols_)
            throw std::out_of_range("Invalid matrix indices");
        return data_[row][col];
    }

    void setValue(int row, int col, int value) {
        if (data_ == nullptr)
            throw std::out_of_range("Matrix is not initialized");
        if (row < 0 || row >= rows_ || col < 0 || col >= cols_)
            throw std::out_of_range("Invalid matrix indices");
        data_[row][col] = value;
    }

    void print() const {
        std::cout << "Matrix (" << rows_ << "x" << cols_ << ")\n";
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                std::cout << std::setw(4) << getValue(i, j);
            }
            std::cout << "\n";
        }
    }

    Matrix add(const Matrix& other) const {
        if (rows_ != other.rows_ || cols_ != other.cols_)
            return Matrix(0, 0);

        Matrix result(rows_, cols_);
        for (int i = 0; i < rows_; ++i)
            for (int j = 0; j < cols_; ++j)
                result.setValue(i, j, getValue(i, j) + other.getValue(i, j));
        return result;
    }

    Matrix subtract(const Matrix& other) const {
        if (rows_ != other.rows_ || cols_ != other.cols_)
            return Matrix(0, 0);

        Matrix result(rows_, cols_);
        for (int i = 0; i < rows_; ++i)
            for (int j = 0; j < cols_; ++j)
                result.setValue(i, j, getValue(i, j) - other.getValue(i, j));
        return result;
    }

    Matrix multiply(const Matrix& other) const {
        if (cols_ != other.rows_)
            return Matrix(0, 0);

        Matrix result(rows_, other.cols_);
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < other.cols_; ++j) {
                int sum = 0;
                for (int k = 0; k < cols_; ++k)
                    sum += getValue(i, k) * other.getValue(k, j);
                result.setValue(i, j, sum);
            }
        }
        return result;
    }

    Matrix transpose() const {
        Matrix result(cols_, rows_);
        for (int i = 0; i < rows_; ++i)
            for (int j = 0; j < cols_; ++j)
                result.setValue(j, i, getValue(i, j));
        return result;
    }

    // --------------------------------------------------------------
    // ✅ NOVÉ TESTOVACÍ METODY PRO DEMONSTRACI VÝSLEDKŮ
    // --------------------------------------------------------------

    void testMultiply(const Matrix& other) const {
        Matrix matC = multiply(other);
        std::cout << "\nVysledek A * B (" << matC.getRows() << "x" << matC.getCols() << "):" << std::endl;
        matC.print();
    }

    void testTranspose() const {
        Matrix matT = transpose();
        std::cout << "\nTransponovana matice (" << matT.getRows() << "x" << matT.getCols() << "):" << std::endl;
        matT.print();
    }

    void testAdd(const Matrix& other) const {
        Matrix matSum = add(other);
        std::cout << "\nVysledek A + B (" << matSum.getRows() << "x" << matSum.getCols() << "):" << std::endl;
        matSum.print();
    }
};



// ===================================================================
// 2. ČÁST: HLAVNÍ FUNKCE (PRO VAŠE TESTOVÁNÍ)
// ===================================================================

// Tento soubor se nespustí, pokud jsou spuštěny testy (díky __TEST__ definici)
#ifndef __TEST__
int main() {
    std::cout << "--- Testovani tridy Matrix ---" << std::endl;
    
    // Vytvoření matice A
    Matrix matA(2, 3);
    matA.setValue(0, 0, 1);
    matA.setValue(0, 1, 2);
    matA.setValue(0, 2, 3);
    matA.setValue(1, 0, 4);
    matA.setValue(1, 1, 5);
    matA.setValue(1, 2, 6);

    std::cout << "Matice A (2x3):" << std::endl;
    matA.print();

    // Vytvoření matice B
    Matrix matB(3, 2);
    matB.setValue(0, 0, 7);
    matB.setValue(0, 1, 8);
    matB.setValue(1, 0, 9);
    matB.setValue(1, 1, 10);
    matB.setValue(2, 0, 11);
    matB.setValue(2, 1, 12);

    std::cout << "\nMatice B (3x2):" << std::endl;
    matB.print();

    // Test násobení
    Matrix matC = matA.multiply(matB);
    std::cout << "\nVysledek A * B (2x2):" << std::endl;
    matC.print();

    // Test transpozice
    Matrix matT = matA.transpose();
    std::cout << "\nTransponovana matice A (3x2):" << std::endl;
    matT.print();

    // Test sčítání
    Matrix matA2(2, 3);
    matA2.setValue(0, 0, 10);
    matA2.setValue(1, 1, 10);
    
    std::cout << "\nMatice A2 (2x3):" << std::endl;
    matA2.print();
    
    Matrix matSum = matA.add(matA2);
    std::cout << "\nVysledek A + A2 (2x3):" << std::endl;
    matSum.print();


    // Test kopírovacího konstruktoru
    std::cout << "\nTest kopie matice A:" << std::endl;
    Matrix matA_copy = matA;
    matA_copy.print();
    
    // Ověření hluboké kopie
    matA.setValue(0, 0, 99);
    std::cout << "\nMatice A po zmene (0,0) na 99:" << std::endl;
    matA.print();
    std::cout << "\nKopie matice A (mela by zustat nezmenena):" << std::endl;
    matA_copy.print();


    std::cout << "\n--- Testovani dokonceno ---" << std::endl;

    return 0;
}
#endif // __TEST__
    