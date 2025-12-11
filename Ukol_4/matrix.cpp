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

Matrix::Matrix()
{

}

Matrix::Matrix(int rows, int cols)
{
    if (rows <= 0 || cols <= 0) {
            rows_ = 0;
            cols_ = 0;
            data_ = nullptr;
            return;
        }
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

    if (data_ != nullptr && other.data_ != nullptr) {
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
void Matrix::allocateMatrix()
{
    data_ = new int*[rows_];
        for (int i = 0; i < rows_; ++i) {
            data_[i] = new int[cols_];
            for (int j = 0; j < cols_; ++j) {
                data_[i][j] = 0; // Inicializace na nulu
            }
        }
}

int Matrix::getValue(int row, int col) const
{
    if (row < 0 || row >= rows_ || col < 0 || col >= cols_ || data_ == nullptr) {
            throw std::out_of_range("Nefacha");
        }
        return data_[row][col];
}

void Matrix::setValue(int row, int col, int value)
{
    if (row < 0 || row >= rows_ || col < 0 || col >= cols_ || data_ == nullptr) {
            throw std::out_of_range("Nefacha");
        }
        data_[row][col] = value;
}

Matrix Matrix::subtract(const Matrix &other)
{
    if (rows_ != other.rows_ || cols_ != other.cols_) {
            return Matrix(0, 0);
        }

        Matrix result(rows_, cols_);
        // ... doplňte výpočet
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                int diff = this->getValue(i, j) - other.getValue(i, j);
                result.setValue(i, j, diff);
            }
        }
        return result;
}

Matrix Matrix::T()
{
    Matrix result(cols_, rows_);

        // TODO: Proveďte transpozici
        // (Projděte původní matici a hodnoty ukládejte do 'result' na prohozené pozice)
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                result.setValue(j, i, this->getValue(i, j));
            }
        }
        return result;
}

Matrix Matrix::operator+(const Matrix &other)
{
    if (rows_ != other.rows_ || cols_ != other.cols_) {
            return Matrix(0, 0);
        }
        
        // TODO: Vytvořte novou matici 'result' pro výsledek
        Matrix result(rows_, cols_);
        
        // TODO: Proveďte sčítání prvek po prvku
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                int sum = this->getValue(i, j) + other.getValue(i, j);
                result.setValue(i, j, sum);
            }
        }

        
        return result;
}

Matrix Matrix::operator*(const Matrix &other)
{
    if (cols_ != other.rows_) {
            return Matrix(0, 0);
        }

        // TODO: Vytvořte novou matici 'result' (this->rows_ x other.cols_)
        Matrix result(rows_, other.cols_);

        // TODO: Proveďte násobení matic (tři vnořené cykly)
        // result.setValue(i, j, suma);
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < other.cols_; ++j) {
                int sum = 0;
                for (int k = 0; k < cols_; ++k) {
                    sum += this->getValue(i, k) * other.getValue(k, j);
                }
                result.setValue(i, j, sum);
            }
        }
        return result;
}

Matrix Matrix::operator*(int scalar)
{
    Matrix result(rows_, cols_);

        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                int prod = this->getValue(i, j) * scalar;
                result.setValue(i, j, prod);
            }
        }
    return result;
}

std::ostream &operator<<(std::ostream &os, const Matrix &mat)
{
    for (int i = 0; i < mat.getRows(); ++i) {
            for (int j = 0; j < mat.getCols(); ++j) {
                os << std::setw(5) << mat.getValue(i, j);
            }
            os << std::endl;
        }
    return os;
}
