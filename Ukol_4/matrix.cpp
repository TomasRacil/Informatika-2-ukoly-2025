#include "matrix.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>

// ========== Private helpers ==========

void Matrix::allocateMatrix() {
    if (rows_ <= 0 || cols_ <= 0) {
        throw std::out_of_range("Cannot allocate matrix with non-positive dimensions");
    }
    data_ = new int*[rows_];
    for (int i = 0; i < rows_; ++i) {
        data_[i] = new int[cols_];
        for (int j = 0; j < cols_; ++j)
            data_[i][j] = 0;
    }
}

void Matrix::deallocateMatrix() {
    if (!data_) return;
    for (int i = 0; i < rows_; ++i)
        delete[] data_[i];
    delete[] data_;
    data_ = nullptr;
}

// ========== Constructors / destructors ==========

Matrix::Matrix() : rows_(0), cols_(0), data_(nullptr) {}

Matrix::Matrix(int rows, int cols) : rows_(0), cols_(0), data_(nullptr) {
    if (rows <= 0 || cols <= 0) {
        return; // Create 0x0 matrix for negative dimensions
    }
    rows_ = rows;
    cols_ = cols;
    allocateMatrix();
}

Matrix::~Matrix() {
    deallocateMatrix();
}

Matrix::Matrix(const Matrix& other) {
    rows_ = other.rows_;
    cols_ = other.cols_;
    allocateMatrix();
    for (int i = 0; i < rows_; ++i)
        for (int j = 0; j < cols_; ++j)
            data_[i][j] = other.data_[i][j];
}

// ========== Getters / setters ==========

int Matrix::getRows() const { return rows_; }
int Matrix::getCols() const { return cols_; }

int Matrix::getValue(int row, int col) const {
    if (!data_ || row < 0 || col < 0 || row >= rows_ || col >= cols_)
        throw std::out_of_range("Invalid index");
    return data_[row][col];
}

void Matrix::setValue(int row, int col, int value) {
    if (row < 0 || col < 0 || row >= rows_ || col >= cols_)
        throw std::out_of_range("Invalid index");
    data_[row][col] = value;
}

// ========== Matrix operations ==========

Matrix Matrix::subtract(const Matrix& other) {
    if (rows_ != other.rows_ || cols_ != other.cols_)
        throw std::invalid_argument("Matrix dimensions must match for subtraction");
    Matrix result(rows_, cols_);
    for (int i = 0; i < rows_; ++i)
        for (int j = 0; j < cols_; ++j)
            result.data_[i][j] = data_[i][j] - other.data_[i][j];
    return result;
}

Matrix Matrix::T() {
    Matrix result(cols_, rows_);
    for (int i = 0; i < rows_; ++i)
        for (int j = 0; j < cols_; ++j)
            result.data_[j][i] = data_[i][j];
    return result;
}

// ========== Operators ==========

Matrix Matrix::operator+(const Matrix& other) {
    if (rows_ != other.rows_ || cols_ != other.cols_)
        return Matrix(); // Return 0x0 matrix if dimensions don't match
    Matrix result(rows_, cols_);
    for (int i = 0; i < rows_; ++i)
        for (int j = 0; j < cols_; ++j)
            result.data_[i][j] = data_[i][j] + other.data_[i][j];
    return result;
}

Matrix Matrix::operator*(const Matrix& other) {
    if (cols_ != other.rows_)
        return Matrix(); // Return 0x0 matrix if dimensions aren't compatible
    Matrix result(rows_, other.cols_);
    for (int i = 0; i < rows_; ++i)
        for (int j = 0; j < other.cols_; ++j) {
            int sum = 0;
            for (int k = 0; k < cols_; ++k)
                sum += data_[i][k] * other.data_[k][j];
            result.data_[i][j] = sum;
        }
    return result;
}

Matrix Matrix::operator*(int scalar) {
    Matrix result(rows_, cols_);
    for (int i = 0; i < rows_; ++i)
        for (int j = 0; j < cols_; ++j)
            result.data_[i][j] = data_[i][j] * scalar;
    return result;
}

std::ostream& operator<<(std::ostream& os, const Matrix& mat) {
    for (int i = 0; i < mat.rows_; ++i) {
        for (int j = 0; j < mat.cols_; ++j)
            os << std::setw(4) << mat.data_[i][j];
        os << '\n';
    }
    return os;
}
