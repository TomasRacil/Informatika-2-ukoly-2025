#include "matrix.h"

// TODO: Vložte sem potřebné #include (např. <iostream>, <iomanip>)
#include <iostream>
#include <iomanip>
#include <stdexcept> // pro std::out_of_range

// ===================================================================
// KROK 1: IMPLEMENTACE Z ÚKOLU 3
// ===================================================================

// TODO: Zkopírujte sem implementace (těla) metod z vašeho hotového Ukolu 3.
// (s výjimkou metod add, multiply a print, které budou nahrazeny operátory)
// Nezapomeňte ke každé metodě přidat prefix 'Matrix::'

// Příklad:
// void Matrix::allocateMatrix() {
//    // ... vaše implementace z Ukolu 3 ...
// }
//
// Matrix::Matrix(int rows, int cols) {
//    // ... vaše implementace z Ukolu 3 ...
// }
//
// ... atd. pro (destruktor, getRows, getValue, setValue, subtract, transpose...)


// ===================================================================
// KROK 2: IMPLEMENTACE OPERÁTORŮ PRO ÚKOL 4
// ===================================================================


void Matrix::allocateMatrix()
{
    if (rows_ > 0 && cols_ > 0) {
            data_ = new int*[rows_];
            for (int i = 0; i < rows_; ++i) {
                data_[i] = new int[cols_];
                for (int j = 0; j < cols_; ++j) {
                    data_[i][j] = 0;
                }
            }
        } else {
            data_ = nullptr;
        }
}

void Matrix::deallocateMatrix()
{
    if (data_ != nullptr) {
            for (int i = 0; i < rows_; ++i) {
                delete[] data_[i];
            }
            delete[] data_; // Uvolnění pole pointerů
            data_ = nullptr;
        }
}

Matrix::Matrix()
{
    rows_ = 0;
    cols_ = 0;
    data_ = nullptr;
    allocateMatrix();
}

Matrix::Matrix(int rows, int cols)
{
    rows_ = rows;
    cols_ = cols;
    allocateMatrix();

}

Matrix::~Matrix()
{

    deallocateMatrix();

}

Matrix::Matrix(const Matrix &other)
{
    rows_ = other.rows_;
    cols_ = other.cols_;
    
    allocateMatrix();
    
    if (other.data_ != nullptr && data_ != nullptr) {
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                this->data_[i][j] = other.data_[i][j];
            }
        }
    }
}

int Matrix::getRows() const
{
    if (data_ != nullptr) {
            return rows_;
        } else {
            return 0;
        }
    return 0;
}

int Matrix::getCols() const
{
    if (data_ != nullptr) {
            return cols_;
        } else {
            return 0;
        }
    return 0;
}

int Matrix::getValue(int row, int col) const
{
    if (data_ != nullptr) {
            if (row >= 0 && row < rows_ && col >= 0 && col < cols_) {
                return data_[row][col];
            } else {
                throw std::out_of_range("Neplatne indexy");
            }
        } else {
            throw std::out_of_range("data_ == nullptr");
        }
    return 0;
}

void Matrix::setValue(int row, int col, int value)
{
    if (data_ != nullptr) {
            if (row >= 0 && row < rows_ && col >= 0 && col < cols_) {
                data_[row][col] = value;
            } else {
                throw std::out_of_range("Neplatne indexy");
            }
        } else {
            throw std::out_of_range("data_ == nullptr");
        }
}

Matrix Matrix::subtract(const Matrix &other)
{
    if (data_ != nullptr && other.data_ != nullptr) {
            if (rows_ != other.rows_ || cols_ != other.cols_) {
                return Matrix(0, 0);
            }
        }

        Matrix result(rows_, cols_);

        if (data_ != nullptr && other.data_ != nullptr) {
            for (int i = 0; i < rows_; ++i) {
                for (int j = 0; j < cols_; ++j) {
                    result.setValue(i, j, this->getValue(i, j) - other.getValue(i, j));
                }
            }
        }

        return result;
}

Matrix Matrix::T()
{
    Matrix result(cols_, rows_);

        if (data_ != nullptr) {
            for (int i = 0; i < rows_; ++i) {
                for (int j = 0; j < cols_; ++j) {
                    result.setValue(j, i, this->getValue(i, j));                 
                }
            }
        }

        return result;
}

Matrix Matrix::operator+(const Matrix &other)
{
    if (data_ != nullptr && other.data_ != nullptr) {
            if (rows_ != other.rows_ || cols_ != other.cols_) {
                return Matrix(0, 0);
            }
        }

        Matrix result(rows_, cols_);

        if (data_ != nullptr && other.data_ != nullptr) {
            for (int i = 0; i < rows_; ++i) {
                for (int j = 0; j < cols_; ++j) {
                    result.setValue(i, j, this->getValue(i, j) + other.getValue(i, j));
                }
            }
        }

        return result;
}


Matrix Matrix::operator*(const Matrix &other)
{
    if (data_ != nullptr && other.data_ != nullptr) {
            if (cols_ != other.rows_) {
                return Matrix(0, 0);
            }
        }

        Matrix result(rows_, other.cols_);

        if (data_ != nullptr && other.data_ != nullptr) {
            for (int i = 0; i < rows_; ++i) {
                for (int j = 0; j < other.cols_; ++j) {
                    int suma = 0;
                    for (int k = 0; k < cols_; ++k) {
                        suma += this->getValue(i, k) * other.getValue(k, j);
                    }
                    result.setValue(i, j, suma);
                }
            }
        }

        return result;
}

Matrix Matrix::operator*(int scalar)
{
    Matrix result(rows_, cols_);

        if (data_ != nullptr) {
            for (int i = 0; i < rows_; ++i) {
                for (int j = 0; j < cols_; ++j) {
                    result.setValue(i, j, this->getValue(i, j) * scalar);
                }
            }
        }

        return result;
}

std::ostream &operator<<(std::ostream &os, const Matrix &mat)
{
    if (mat.data_ != nullptr) {
        for (int i = 0; i < mat.rows_; ++i) {
            for (int j = 0; j < mat.cols_; ++j) {
                os << mat.getValue(i, j) << " ";
            }
            os << "\n";
        }
    }
    return os;
}