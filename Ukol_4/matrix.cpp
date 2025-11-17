#include "matrix.h"
#include <iostream>
#include <iomanip>
#include <stdexcept> // pro std::out_of_range

// ===================================================================
// KROK 1: IMPLEMENTACE Z ÚKOLU 3
// ===================================================================

void Matrix::allocateMatrix() {
    if (rows_ <= 0 || cols_ <= 0) {
        data_ = nullptr;
        return;
    }

    data_ = new int *[rows_];
    for (int i = 0; i < rows_; i++) {
        data_[i] = new int[cols_]();
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

// ===================================================================
// KROK 2: IMPLEMENTACE OPERÁTORŮ PRO ÚKOL 4
// ===================================================================

Matrix::Matrix()
    : rows_(0), cols_(0), data_(nullptr) // DŮLEŽITÉ: inicializace!
{
}

Matrix::Matrix(int rows, int cols)
{
    if (rows <= 0 || cols <= 0)
    {
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
    data_ = nullptr;
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
    if (row < 0 || row >= rows_ || col < 0 || col >= cols_ || data_ == nullptr)
    {
        throw std::out_of_range("Nejede to");
    }
    return data_[row][col];    
}

void Matrix::setValue(int row, int col, int value)
{
    if (row < 0 || row >= rows_ || col < 0 || col >= cols_ || data_ == nullptr)
    {
        throw std::out_of_range("Nejede to");
    }
    data_[row][col] = value;
}

Matrix Matrix::subtract(const Matrix &other)
{
    if (rows_ != other.rows_ || cols_ != other.cols_)
    {
        return Matrix(0, 0);
    }

    Matrix result(rows_, cols_);
    for (int i = 0; i < rows_; i++)
    {
        for (int j = 0; j < cols_; j++)
        {
            result.setValue(i, j, getValue(i, j) - other.getValue(i, j));
        }
    }
    return result;
}

Matrix Matrix::T()
{
    Matrix result(this->cols_, this->rows_);

    for (int i = 0; i < this->rows_; ++i) {
        for (int j = 0; j < this->cols_; ++j) {
            result.setValue(j, i, this->getValue(i, j));
        }
    }

    return result;
}

Matrix Matrix::operator+(const Matrix &other)
{
    // pokud nesouhlasí rozměry, vrať prázdnou 0x0 matici
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        return Matrix(0, 0);
    }

    Matrix result(rows_, cols_);
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

    Matrix result(this->rows_, other.cols_);

    for (int i = 0; i < this->rows_; ++i) {
        for (int j = 0; j < other.cols_; ++j) {
            int sum = 0;
            for (int k = 0; k < this->cols_; ++k) {
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
    if (!data_) return result;

    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            result.data_[i][j] = data_[i][j] * scalar;
        }
    }
    return result;
}

std::ostream &operator<<(std::ostream &os, const Matrix &mat)
{
    os << "Matrix (" << mat.rows_ << "x" << mat.cols_ << ")" << std::endl;

    for (int i = 0; i < mat.rows_; ++i) {
        for (int j = 0; j < mat.cols_; ++j) {
            os << std::setw(4) << mat.data_[i][j];
        }
        os << std::endl;
    }
    return os;
}
