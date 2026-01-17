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

void Matrix::allocateMatrix()
{
    if (rows_ <= 0 || cols_ <= 0)
    {
        data_ = nullptr;
        rows_ = 0;
        cols_ = 0;
        return;
    }

    data_ = new int *[rows_];

    for (int i = 0; i < rows_; i++)
    {
        data_[i] = new int[cols_]();
    }
}

void Matrix::deallocateMatrix()
{
    if (data_ != nullptr && rows_ > 0)
    {
        for (int i = 0; i < rows_; i++)
        {
            delete[] data_[i];

            data_[i] = nullptr;
        }

        delete[] data_;
        data_ = nullptr;
    }
}

// ===================================================================
// KROK 2: IMPLEMENTACE OPERÁTORŮ PRO ÚKOL 4
// ===================================================================

// defaultní konstruktor, když se zavolá vytvoření objektu bez parametrů
Matrix::Matrix() : rows_(0), cols_(0), data_(nullptr) { }

Matrix::Matrix(int rows, int cols)
{
    this->rows_ = rows;
    this->cols_ = cols;

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

    data_ = nullptr;
    allocateMatrix();

    if (data_ != nullptr && other.data_ != nullptr)
    {
        // Hluboká kopie hodnot
        for (int r = 0; r < rows_; ++r)
            for (int c = 0; c < cols_; ++c)
                data_[r][c] = other.data_[r][c];
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
    if (row < 0 || row >= getRows() || col < 0 || col >= getCols() || data_ == nullptr)
    {
        throw std::out_of_range("Index mimo rozsah matice");
    }

    return data_[row][col];
}

void Matrix::setValue(int row, int col, int value)
{
    if (row < 0 || row >= getRows() || col < 0 || col >= getCols() || data_ == nullptr)
    {
        throw std::out_of_range("Index mimo rozsah matice");
    }

    data_[row][col] = value;
}

Matrix Matrix::subtract(const Matrix &other)
{
    if (getRows() != other.getRows() || getCols() != other.getCols())
    {
        return Matrix(0, 0);
    }

    Matrix result(rows_, cols_);

    for (int r = 0; r < getRows(); r++)
    {
        for (int c = 0; c < getCols(); c++)
        {
            int elementA = getValue(r, c);
            int elementB = other.getValue(r, c);

            result.setValue(r, c, elementA - elementB);
        }
    }

    return result;
}

Matrix Matrix::T()
{
    Matrix result(cols_, rows_);

    for (int r = 0; r < getRows(); r++)
    {
        for (int c = 0; c < getCols(); c++)
        {
            result.setValue(c, r, getValue(r, c));
        }
    }

    return result;
}

Matrix Matrix::operator+(const Matrix &other) const
{
    if (rows_ != other.getRows() || cols_ != other.getCols())
    {
        return Matrix(0, 0);
    }

    Matrix result(rows_, cols_);

    for (int r = 0; r < getRows(); r++)
    {
        for (int c = 0; c < getCols(); c++)
        {
            int elementA = getValue(r, c);
            int elementB = other.getValue(r, c);

            result.setValue(r, c, elementA + elementB);
        }
    }

    return result;
}

Matrix Matrix::operator*(const Matrix &other) const
{
    if (getCols() != other.getRows())
    {
        return Matrix(0, 0);
    }

    Matrix result(rows_, other.cols_);

    for (int r = 0; r < getRows(); r++)
    {
        for (int cB = 0; cB < other.getCols(); cB++)
        {
            int suma = 0;
            for (int k = 0; k < getCols(); k++) // k is not only columns A but also rows B
            {
                suma += getValue(r, k) * other.getValue(k, cB);
            }

            result.setValue(r, cB, suma);
        }
    }

    return result;
}

Matrix Matrix::operator*(int scalar)
{
    Matrix result(getRows(), getCols());

    for (int r = 0; r < getRows(); r++)
    {
        for (int c = 0; c < getCols(); c++)
        {
            result.setValue(r, c, getValue(r, c) * scalar);
        }
    }

    return result;
}

std::ostream &operator<<(std::ostream &os, const Matrix &mat)
{
    for (int r = 0; r < mat.getRows(); r++)
        {
            for (int c = 0; c < mat.getCols(); c++)
            {
                os << std::setw(4) << mat.getValue(r, c);
            }
            os << "\n";
        }

    return os;
}
