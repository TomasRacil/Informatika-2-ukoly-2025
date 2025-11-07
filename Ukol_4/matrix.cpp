#include "matrix.h"

#include <iostream>
#include <iomanip>
#include <stdexcept> // pro std::out_of_range

using namespace std;

// ===================================================================
// KROK 1: IMPLEMENTACE Z ÚKOLU 3
// ===================================================================

// TODO: Zkopírujte sem implementace (těla) metod z vašeho hotového Ukolu 3.
// (s výjimkou metod add, multiply a print, které budou nahrazeny operátory)
// Nezapomeňte ke každé metodě přidat prefix 'Matrix::'

// Příklad:
void Matrix::allocateMatrix()
{
    if (rows_ == 0 || cols_ == 0)
    {
        data_ = nullptr;
        return;
    }
    data_ = nullptr;
    data_ = new int *[rows_];
    for (int i = 0; i < rows_; i++)
    {
        data_[i] = new int[cols_]();
    }
}
void Matrix::deallocateMatrix()
{
    if (data_ == nullptr)
    {
        return;
    }
    else
    {
        for (int i = 0; i < rows_; i++)
        {
            if (data_[i] != nullptr)
            {
                delete[] data_[i];
            }
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
{
    rows_ = 0;
    cols_ = 0;
    data_ = nullptr;
}

Matrix::Matrix(int rows, int cols)
{
    this->rows_ = (rows < 0) ? 0 : rows;
    this->cols_ = (cols < 0) ? 0 : cols;
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

    if (data_ != nullptr && other.data_ != nullptr)
    {
        for (int i = 0; i < rows_; i++)
        {
            for (int j = 0; j < cols_; j++)
            {
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
    if (row < 0 || row >= rows_ || col < 0 || col >= cols_)
    {
        throw out_of_range("Mimo rozsah");
    }
    else if (data_ == nullptr)
    {
        throw out_of_range("Mimo rozsah");
    }

    return data_[row][col];
}

void Matrix::setValue(int row, int col, int value)
{
    if (row < 0 || row >= rows_ || col < 0 || col >= cols_)
    {
        throw out_of_range("Mimo rozsah");
    }
    else if (data_ == nullptr)
    {
        throw out_of_range("Mimo rozsah");
    }
    data_[row][col] = value;
}

Matrix Matrix::subtract(const Matrix &other)
{
    if (this->cols_ != other.cols_ || this->rows_ != other.rows_)
    {
        return Matrix(0, 0);
    }
    if (data_ == nullptr || other.data_ == nullptr)
    {
        return Matrix(0, 0);
    }
    Matrix result(rows_, cols_);
    for (int i = 0; i < rows_; i++)
    {
        for (int j = 0; j < cols_; j++)
        {
            int sub = this->getValue(i, j) - other.getValue(i, j);
            result.setValue(i, j, sub);
        }
    }

    return result;
}

Matrix Matrix::T()
{
    Matrix result(cols_, rows_);

    for (int i = 0; i < rows_; i++)
    {
        for (int j = 0; j < cols_; j++)
        {
            result.setValue(j, i, this->getValue(i, j));
        }
    }
    return result;
}

Matrix Matrix::operator+(const Matrix &other)
{
    if (this->rows_ != other.rows_ || this->cols_ != other.cols_)
    {
        return Matrix(0, 0);
    }
    if (rows_ == 0 || cols_ == 0 || data_ == nullptr || other.data_ == nullptr)
    {
        return Matrix(0, 0);
    }
    Matrix result(rows_, cols_);
    for (int i = 0; i < rows_; i++)
    {
        for (int j = 0; j < cols_; j++)
        {
            int sum = this->getValue(i, j) + other.getValue(i, j);
            result.setValue(i, j, sum);
        }
    }
    return result;
}

Matrix Matrix::operator*(const Matrix &other)
{
    if (this->cols_ != other.rows_)
    {
        return Matrix(0, 0);
    }
    if (rows_ == 0 || cols_ == 0 || other.rows_ == 0 || other.cols_ == 0 ||
        data_ == nullptr || other.data_ == nullptr)
    {
        return Matrix(0, 0);
    }
    Matrix result(rows_, other.cols_);
    for (int i = 0; i < rows_; i++)
    {
        for (int j = 0; j < other.cols_; j++)
        {
            int sum = 0;
            for (int k = 0; k < cols_; k++)
            {
                sum = sum + (this->getValue(i, k) * other.getValue(k, j));
            }
            result.setValue(i, j, sum);
        }
    }
    return result;
}

Matrix Matrix::operator*(int scalar)
{
    if (rows_ == 0 || cols_ == 0 || data_ == nullptr)
    {
        return Matrix(0, 0);
    }
    Matrix result(rows_, cols_);
    for (int i = 0; i < rows_; i++)
    {
        for (int j = 0; j < cols_; j++)
        {
            result.setValue(i, j, this->getValue(i, j) * scalar);
        }
    }
    return result;
}

std::ostream &operator<<(std::ostream &os, const Matrix &mat)
{
    os << "Matrix (" << mat.getRows() << "x" << mat.getCols() << ")" << std::endl;
    for (int i = 0; i < mat.rows_; i++)
    {
        for (int j = 0; j < mat.cols_; j++)
        {
            os << std::setw(4) << mat.getValue(i, j) << "\t";
        }
        os << "\n";
    }
    return os;
}
