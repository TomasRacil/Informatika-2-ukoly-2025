#include "matrix.h"

// TODO: Vložte sem potřebné #include (např. <iostream>, <iomanip>)
#include <iostream>
#include <iomanip>
#include <stdexcept> // pro std::out_of_range

// ===================================================================
// KROK 1: IMPLEMENTACE Z ÚKOLU 3
// ===================================================================

// Implementace private helperů
void Matrix::allocateMatrix()
{
    // pokud jsou rozměry nulové nebo záporné, necháme data_ jako nullptr
    if (rows_ <= 0 || cols_ <= 0) {
        data_ = nullptr;
        return;
    }

    data_ = new int*[rows_];
    for (int i = 0; i < rows_; ++i) {
        data_[i] = new int[cols_];
        for (int j = 0; j < cols_; ++j) {
            data_[i][j] = 0; // inicializace na 0
        }
    }
}

void Matrix::deallocateMatrix()
{
    if (!data_) return;
    for (int i = 0; i < rows_; ++i) {
        delete[] data_[i];
    }
    delete[] data_;
    data_ = nullptr;
}

// ===================================================================
// KROK 2: IMPLEMENTACE OPERÁTORŮ PRO ÚKOL 4
// ===================================================================

Matrix::Matrix()
    : rows_(0), cols_(0), data_(nullptr)
{
}

Matrix::Matrix(int rows, int cols)
    : rows_(rows > 0 ? rows : 0), cols_(cols > 0 ? cols : 0), data_(nullptr)
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
    if (rows_ > 0 && cols_ > 0) {
        allocateMatrix();
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                data_[i][j] = other.data_[i][j];
            }
        }
    } else {
        data_ = nullptr;
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
    if (row < 0 || col < 0 || row >= rows_ || col >= cols_ || !data_) {
        throw std::out_of_range("Index out of range");
    }
    return data_[row][col];
}

void Matrix::setValue(int row, int col, int value)
{
    if (row < 0 || col < 0 || row >= rows_ || col >= cols_ || !data_) {
        throw std::out_of_range("Index out of range");
    }
    data_[row][col] = value;
}

Matrix Matrix::subtract(const Matrix &other)
{
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

Matrix Matrix::T()
{
    if (rows_ <= 0 || cols_ <= 0) return Matrix(0, 0);
    Matrix result(cols_, rows_);
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            result.data_[j][i] = data_[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator+(const Matrix &other)
{
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

Matrix Matrix::operator*(const Matrix &other)
{
    // (m x n) * (p x q) kde n must == p
    if (cols_ != other.rows_ || rows_ <= 0 || cols_ <= 0 || other.cols_ <= 0) {
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

Matrix Matrix::operator*(int scalar)
{
    if (rows_ <= 0 || cols_ <= 0) return Matrix(0, 0);
    Matrix result(rows_, cols_);
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            result.data_[i][j] = data_[i][j] * scalar;
        }
    }
    return result;
}

std::ostream &operator<<(std::ostream &os, const Matrix &mat)
{
    if (mat.rows_ <= 0 || mat.cols_ <= 0 || !mat.data_) {
        return os;
    }
    for (int i = 0; i < mat.rows_; ++i) {
        for (int j = 0; j < mat.cols_; ++j) {
            os << mat.data_[i][j];
            if (j + 1 < mat.cols_) os << " ";
        }
        os << "\n";
    }
    return os;
}
