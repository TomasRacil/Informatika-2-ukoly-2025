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
void Matrix::allocateMatrix() {
    if (rows_ > 0 && cols_ > 0) {
        // 1. Alokujte pole pointerů (řádky)
        data_ = new int*[rows_];
        for (int i = 0; i < rows_; ++i) {
            // 2. Alokujte pole intů pro každý řádek (sloupce)
            data_[i] = new int[cols_];
            // 3. Inicializujte všechny prvky na 0
            for (int j = 0; j < cols_; ++j) {
                data_[i][j] = 0;
            }
        }
    } else {
        // Zajistíme konzistenci rozměrů
        rows_ = 0; 
        cols_ = 0;
        data_ = nullptr;
    }
}

void Matrix::deallocateMatrix() {
   if (data_ != nullptr) {
            for (int i = 0; i < rows_; i++) {
                delete[] data_[i];
            }
            delete[] data_;
            data_ = nullptr;
    }
}
//
// Matrix::Matrix(int rows, int cols) {
//    // ... vaše implementace z Ukolu 3 ...
// }
//
// ... atd. pro (destruktor, getRows, getValue, setValue, subtract, transpose...)


// ===================================================================
// KROK 2: IMPLEMENTACE OPERÁTORŮ PRO ÚKOL 4
// ===================================================================

Matrix::Matrix()
:rows_(0), cols_(0), data_(nullptr)
{
}

Matrix::Matrix(int rows, int cols)
    : rows_(rows >= 0 ? rows : 0),
      cols_(cols >= 0 ? cols : 0),
      data_(nullptr)
{
    allocateMatrix();
}

Matrix::~Matrix()
{
    deallocateMatrix();
}

Matrix::Matrix(const Matrix &other)
: rows_(other.rows_), cols_(other.cols_), data_(nullptr)
{
allocateMatrix();
    if (data_ != nullptr) {
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                data_[i][j] = other.data_[i][j];
            }
        }
    }
}

int Matrix::getRows() const
{
    return rows_;
}

int Matrix::getCols() const
{
    return cols_;
}


int Matrix::getValue(int row, int col) const
{
     if (data_ == nullptr || row < 0 || row >= rows_ || col < 0 || col >= cols_) {
             throw std::out_of_range("Index out of range or matrix is null.");
        }
    return data_[row][col];
}

void Matrix::setValue(int row, int col, int value)
{
        if (data_ == nullptr || row < 0 || row >= rows_ || col < 0 || col >= cols_) {
                throw std::out_of_range("Index out of range or matrix is null.");
            }
        data_[row][col] = value;
}

Matrix Matrix::subtract(const Matrix &other)
{
   if (rows_ != other.rows_ || cols_ != other.cols_) {
        std::cerr << "Error: Matrix dimensions must match for subtraction." << std::endl;
        return Matrix(0, 0);
    }

    Matrix result(rows_, cols_);
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            result.data_[i][j] = this->data_[i][j] - other.data_[i][j];
        }
    }
    return result;
}

Matrix Matrix::T()
{
   Matrix result(cols_, rows_);

    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            result.data_[j][i] = this->data_[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator+(const Matrix &other)
{
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        std::cerr << "Error: Matrix dimensions must match for addition (operator+)." << std::endl;
        return Matrix(0, 0);
    }

    Matrix result(rows_, cols_);
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            result.data_[i][j] = this->data_[i][j] + other.data_[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator*(const Matrix &other)
{
   if (cols_ != other.rows_) {
        std::cerr << "Error: Matrix dimensions invalid for multiplication (A.cols != B.rows) (operator*)." << std::endl;
        return Matrix(0, 0);
    }

    Matrix result(rows_, other.cols_);

    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < other.cols_; ++j) {
            int sum = 0;
            for (int k = 0; k < cols_; ++k) {
                sum += this->data_[i][k] * other.data_[k][j];
            }
            result.data_[i][j] = sum;
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
                result.data_[i][j] = this->data_[i][j] * scalar;
            }
        }
    }
    return result;
}

std::ostream &operator<<(std::ostream &os, const Matrix &mat)
{
    os << "Matrix (" << mat.getRows() << "x" << mat.getCols() << ")" << std::endl;
    
    if (mat.getRows() == 0 || mat.getCols() == 0) {
        os << "[]" << std::endl;
        return os;
    }
    
    try {
        for (int i = 0; i < mat.getRows(); ++i) {
            os << "[";
            for (int j = 0; j < mat.getCols(); ++j) {
                // Používáme getValue pro bezpečný přístup.
                os << std::setw(4) << mat.getValue(i, j); 
            }
            os << " ]" << std::endl;
        }
    } catch (const std::out_of_range&) {
        // V tomto kontextu by to nemělo nastat, ale ponecháno pro robustnost.
    }
    
    return os;
}
