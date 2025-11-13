#include "matrix.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>

// ===============================================================
// Pomocné metody
// ===============================================================
void Matrix::allocateMatrix() {
    if (rows_ <= 0 || cols_ <= 0) {
        rows_ = 0;
        cols_ = 0;
        data_ = nullptr;
        return;
    }

    data_ = new int*[rows_];
    for (int i = 0; i < rows_; ++i) {
        data_[i] = new int[cols_];
        for (int j = 0; j < cols_; ++j)
            data_[i][j] = 0;
    }
}

void Matrix::deallocateMatrix() {
    if (data_ != nullptr) {
        for (int i = 0; i < rows_; ++i)
            delete[] data_[i];
        delete[] data_;
        data_ = nullptr;
    }
}

// ===============================================================
// Konstrukce a destrukce
// ===============================================================
Matrix::Matrix() : rows_(0), cols_(0), data_(nullptr) {}

Matrix::Matrix(int rows, int cols) : rows_(0), cols_(0), data_(nullptr) {
    // Pokud jsou rozměry neplatné, zůstaň prázdný (0x0)
    if (rows > 0 && cols > 0) {
        rows_ = rows;
        cols_ = cols;
        allocateMatrix();
    }
}

Matrix::~Matrix() {
    deallocateMatrix();
}

Matrix::Matrix(const Matrix& other) : rows_(other.rows_), cols_(other.cols_), data_(nullptr) {
    allocateMatrix();
    if (data_ && other.data_) {
        for (int i = 0; i < rows_; ++i)
            for (int j = 0; j < cols_; ++j)
                data_[i][j] = other.data_[i][j];
    }
}

// ===============================================================
// Gettery / Settery
// ===============================================================
int Matrix::getRows() const { return rows_; }
int Matrix::getCols() const { return cols_; }

int Matrix::getValue(int row, int col) const {
    if (data_ == nullptr)
        throw std::out_of_range("Matrix is not initialized");
    if (row < 0 || row >= rows_ || col < 0 || col >= cols_)
        throw std::out_of_range("Invalid matrix indices");
    return data_[row][col];
}

void Matrix::setValue(int row, int col, int value) {
    if (data_ == nullptr)
        throw std::out_of_range("Matrix is not initialized");
    if (row < 0 || row >= rows_ || col < 0 || col >= cols_)
        throw std::out_of_range("Invalid matrix indices");
    data_[row][col] = value;
}

// ===============================================================
// Operace
// ===============================================================
Matrix Matrix::subtract(const Matrix& other) {
    if (rows_ != other.rows_ || cols_ != other.cols_)
        return Matrix(); // 0x0

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

// ===============================================================
// Operátory
// ===============================================================
Matrix Matrix::operator+(const Matrix& other) {
    // nesmí házet výjimku – místo toho prázdná matice
    if (rows_ != other.rows_ || cols_ != other.cols_)
        return Matrix(); // 0x0

    Matrix result(rows_, cols_);
    for (int i = 0; i < rows_; ++i)
        for (int j = 0; j < cols_; ++j)
            result.data_[i][j] = data_[i][j] + other.data_[i][j];
    return result;
}

Matrix Matrix::operator*(const Matrix& other) {
    // nesmí házet výjimku – místo toho prázdná matice
    if (cols_ != other.rows_)
        return Matrix(); // 0x0

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

// ===============================================================
// Výpis
// ===============================================================
std::ostream& operator<<(std::ostream& os, const Matrix& mat) {
    for (int i = 0; i < mat.rows_; ++i) {
        for (int j = 0; j < mat.cols_; ++j)
            os << std::setw(5) << mat.data_[i][j];
        os << '\n';
    }
    return os;
}