#include <iostream>
#include <iomanip> // Pro std::setw
#include <stdexcept> // Pro případné výjimky

class Matrix {
private:
    int rows_;
    int cols_;
    int** data_;

    void allocateMatrix() {
        if (rows_ <= 0 || cols_ <= 0) {
            data_ = nullptr;
            return;
        }
        data_ = new int*[rows_];
        for (int i = 0; i < rows_; ++i) {
            data_[i] = new int[cols_];
            for (int j = 0; j < cols_; ++j) {
                data_[i][j] = 0;
            }
        }
    }

    void deallocateMatrix() {
        if (!data_) return;
        for (int i = 0; i < rows_; ++i) {
            delete[] data_[i];
        }
        delete[] data_;
        data_ = nullptr;
    }

public:
    Matrix(int rows, int cols) {
        if (rows <= 0 || cols <= 0) {
            rows_ = 0;
            cols_ = 0;
            data_ = nullptr;
            return;
        }
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
        if (data_ && other.data_) {
            for (int i = 0; i < rows_; ++i) {
                for (int j = 0; j < cols_; ++j) {
                    data_[i][j] = other.data_[i][j];
                }
            }
        }
    }

    // Matrix& operator=(const Matrix& other);

    int getRows() const {
        return rows_;
    }

    int getCols() const {
        return cols_;
    }

    int getValue(int row, int col) const {
        if (!data_ || row < 0 || col < 0 || row >= rows_ || col >= cols_) {
            throw std::out_of_range("Index mimo rozsah");
        }
        return data_[row][col];
    }

    void setValue(int row, int col, int value) {
        if (!data_ || row < 0 || col < 0 || row >= rows_ || col >= cols_) {
            throw std::out_of_range("Index mimo rozsah");
        }
        data_[row][col] = value;
    }

    void print() const {
        std::cout << "Matrix (" << rows_ << "x" << cols_ << ")" << std::endl;
        if (!data_) {
            std::cout << "[prázdná matice]" << std::endl;
            return;
        }
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                std::cout << std::setw(4) << data_[i][j];
            }
            std::cout << std::endl;
        }
    }

    Matrix add(const Matrix& other) const {
        if (rows_ != other.rows_ || cols_ != other.cols_) {
            return Matrix(0, 0);
        }
        Matrix result(rows_, cols_);
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                result.data_[i][j] = data_[i][j] + other.data_[i][j];
            }
        }
        return result;
    }

    Matrix subtract(const Matrix& other) const {
        if (rows_ != other.rows_ || cols_ != other.cols_) {
            return Matrix(0, 0);
        }
        Matrix result(rows_, cols_);
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                result.data_[i][j] = data_[i][j] - other.data_[i][j];
            }
        }
        return result;
    }

    Matrix multiply(const Matrix& other) const {
        if (cols_ != other.rows_) {
            return Matrix(0, 0);
        }
        Matrix result(rows_, other.cols_);
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < other.cols_; ++j) {
                int sum = 0;
                for (int k = 0; k < cols_; ++k) {
                    sum += data_[i][k] * other.data_[k][j];
                }
                result.data_[i][j] = sum;
            }
        }
        return result;
    }

    Matrix transpose() const {
        Matrix result(cols_, rows_);
        if (!data_) return result; // prázdná zůstane prázdná (rozměry přehodíme)
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                result.data_[j][i] = data_[i][j];
            }
        }
        return result;
    }
};

#ifndef __TEST__
int main() {
    std::cout << "--- Testovani tridy Matrix ---" << std::endl;

    Matrix matA(2, 3);
    matA.setValue(0, 0, 1);
    matA.setValue(0, 1, 2);
    matA.setValue(0, 2, 3);
    matA.setValue(1, 0, 4);
    matA.setValue(1, 1, 5);
    matA.setValue(1, 2, 6);

    std::cout << "Matice A (2x3):" << std::endl;
    matA.print();

    Matrix matB(3, 2);
    matB.setValue(0, 0, 7);
    matB.setValue(0, 1, 8);
    matB.setValue(1, 0, 9);
    matB.setValue(1, 1, 10);
    matB.setValue(2, 0, 11);
    matB.setValue(2, 1, 12);

    std::cout << "\nMatice B (3x2):" << std::endl;
    matB.print();

    Matrix matC = matA.multiply(matB);
    std::cout << "\nVysledek A * B (2x2):" << std::endl;
    matC.print();

    Matrix matT = matA.transpose();
    std::cout << "\nTransponovana matice A (3x2):" << std::endl;
    matT.print();

    Matrix matA2(2, 3);
    matA2.setValue(0, 0, 10);
    matA2.setValue(1, 1, 10);

    std::cout << "\nMatice A2 (2x3):" << std::endl;
    matA2.print();

    Matrix matSum = matA.add(matA2);
    std::cout << "\nVysledek A + A2 (2x3):" << std::endl;
    matSum.print();

    std::cout << "\nTest kopie matice A:" << std::endl;
    Matrix matA_copy = matA;
    matA_copy.print();

    matA.setValue(0, 0, 99);
    std::cout << "\nMatice A po zmene (0,0) na 99:" << std::endl;
    matA.print();
    std::cout << "\nKopie matice A (mela by zustat nezmenena):" << std::endl;
    matA_copy.print();

    std::cout << "\n--- Testovani dokonceno ---" << std::endl;
    return 0;
}
#endif // __TEST__
