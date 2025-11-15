#include "matrix.h"

// TODO: Vložte sem potřebné #include (např. <iostream>, <iomanip>)
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
    data_ = new int*[rows_];
    for (int i = 0; i < rows_; ++i) {
        data_[i] = new int[cols_];
        for (int j = 0; j < cols_; ++j) {
            data_[i][j] = 0;
        }
    }
}

void Matrix::deallocateMatrix() {
    if (!data_) return;
    for (int i = 0; i < rows_; ++i) {
        delete[] data_[i];
    }
    delete[] data_;
    data_ = nullptr;
}

Matrix::Matrix() : rows_(0), cols_(0), data_(nullptr) {}

Matrix::Matrix(int rows, int cols) {
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

Matrix::~Matrix() {
    deallocateMatrix();
}

Matrix::Matrix(const Matrix& other) {
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

int Matrix::getRows() const {
    return rows_;
}

int Matrix::getCols() const {
    return cols_;
}

int Matrix::getValue(int row, int col) const {
    if (!data_ || row < 0 || col < 0 || row >= rows_ || col >= cols_) {
        throw std::out_of_range("Index mimo rozsah");
    }
    return data_[row][col];
}

void Matrix::setValue(int row, int col, int value) {
    if (!data_ || row < 0 || col < 0 || row >= rows_ || col >= cols_) {
        throw std::out_of_range("Index mimo rozsah");
    }
    data_[row][col] = value;
}

Matrix Matrix::subtract(const Matrix& other) const {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        return Matrix(0, 0);
    }
    Matrix r(rows_, cols_);
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            r.data_[i][j] = data_[i][j] - other.data_[i][j];
        }
    }
    return r;
}

Matrix Matrix::transpose() const {
    Matrix r(cols_, rows_);
    if (!data_) return r;
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            r.data_[j][i] = data_[i][j];
        }
    }
    return r;
}

Matrix Matrix::T() const {
    return transpose();
}

// ===================================================================
// KROK 2: IMPLEMENTACE OPERÁTORŮ PRO ÚKOL 4
// ===================================================================

Matrix Matrix::operator+(const Matrix& other) const {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        return Matrix(0, 0);
    }
    Matrix r(rows_, cols_);
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            r.data_[i][j] = data_[i][j] + other.data_[i][j];
        }
    }
    return r;
}

Matrix Matrix::operator*(const Matrix& other) const {
    if (cols_ != other.rows_) {
        return Matrix(0, 0);
    }
    Matrix r(rows_, other.cols_);
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < other.cols_; ++j) {
            int sum = 0;
            for (int k = 0; k < cols_; ++k) {
                sum += data_[i][k] * other.data_[k][j];
            }
            r.data_[i][j] = sum;
        }
    }
    return r;
}

Matrix Matrix::operator*(int scalar) const {
    Matrix r(rows_, cols_);
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            r.data_[i][j] = data_[i][j] * scalar;
        }
    }
    return r;
}

std::ostream& operator<<(std::ostream& os, const Matrix& mat) {
    os << "Matrix (" << mat.rows_ << "x" << mat.cols_ << ")\n";
    if (!mat.data_) {
        os << "[prázdná matice]\n";
        return os;
    }
    for (int i = 0; i < mat.rows_; ++i) {
        for (int j = 0; j < mat.cols_; ++j) {
            os << std::setw(4) << mat.data_[i][j];
        }
        os << "\n";
    }
    return os;
}
