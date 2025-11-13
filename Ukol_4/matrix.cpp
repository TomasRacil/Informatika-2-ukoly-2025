#include "matrix.h"

// TODO: Vložte sem potřebné #include (např. <iostream>, <iomanip>)
#include <iostream>
#include <iomanip>
#include <stdexcept> // pro std::out_of_range

// ===================================================================
// KROK 1: IMPLEMENTACE Z ÚKOLU 3
// ===================================================================

// Konstruktor bez parametrů
Matrix::Matrix() : rows_(0), cols_(0), data_(nullptr) {}

// Konstruktor s rozměry
Matrix::Matrix(int rows, int cols) : rows_(rows), cols_(cols), data_(nullptr) {
    allocateMatrix();
}

// Kopírovací konstruktor
Matrix::Matrix(const Matrix& other) : rows_(other.rows_), cols_(other.cols_), data_(nullptr) {
    allocateMatrix();
    for (int i = 0; i < rows_; ++i)
        for (int j = 0; j < cols_; ++j)
            data_[i][j] = other.data_[i][j];
}

// Destruktor
Matrix::~Matrix() {
    deallocateMatrix();
}

// Alokace paměti pro matici
void Matrix::allocateMatrix() {
    if (rows_ <= 0 || cols_ <= 0) {
        data_ = nullptr;
        return;
    }

    data_ = new int*[rows_];
    for (int i = 0; i < rows_; ++i)
        data_[i] = new int[cols_]{};
}

// Uvolnění paměti
void Matrix::deallocateMatrix() {
    if (data_ != nullptr) {
        for (int i = 0; i < rows_; ++i)
            delete[] data_[i];
        delete[] data_;
        data_ = nullptr;
    }
}

// Gettery a settery
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

// Odečtení matic
Matrix Matrix::subtract(const Matrix& other) const {
    if (rows_ != other.rows_ || cols_ != other.cols_)
        throw std::invalid_argument("Matrix dimensions must match for subtraction");

    Matrix result(rows_, cols_);
    for (int i = 0; i < rows_; ++i)
        for (int j = 0; j < cols_; ++j)
            result.setValue(i, j, getValue(i, j) - other.getValue(i, j));
    return result;
}

// Transpozice matice
Matrix Matrix::T() const {
    Matrix result(cols_, rows_);
    for (int i = 0; i < rows_; ++i)
        for (int j = 0; j < cols_; ++j)
            result.setValue(j, i, getValue(i, j));
    return result;
}

// ===================================================================
// KROK 2: IMPLEMENTACE OPERÁTORŮ PRO ÚKOL 4
// ===================================================================

// Operátor +
Matrix Matrix::operator+(const Matrix& other) const {
    if (rows_ != other.rows_ || cols_ != other.cols_)
        throw std::invalid_argument("Matrix dimensions must match for addition");

    Matrix result(rows_, cols_);
    for (int i = 0; i < rows_; ++i)
        for (int j = 0; j < cols_; ++j)
            result.data_[i][j] = data_[i][j] + other.data_[i][j];
    return result;
}

// Operátor * (násobení matic)
Matrix Matrix::operator*(const Matrix& other) const {
    if (cols_ != other.rows_)
        throw std::invalid_argument("Invalid dimensions for multiplication");

    Matrix result(rows_, other.cols_);
    for (int i = 0; i < rows_; ++i)
        for (int j = 0; j < other.cols_; ++j)
            for (int k = 0; k < cols_; ++k)
                result.data_[i][j] += data_[i][k] * other.data_[k][j];
    return result;
}

// Operátor * (násobení skalárem)
Matrix Matrix::operator*(int scalar) const {
    Matrix result(rows_, cols_);
    for (int i = 0; i < rows_; ++i)
        for (int j = 0; j < cols_; ++j)
            result.data_[i][j] = data_[i][j] * scalar;
    return result;
}

// Operátor << (výpis matice)
std::ostream& operator<<(std::ostream& os, const Matrix& mat) {
    for (int i = 0; i < mat.rows_; ++i) {
        for (int j = 0; j < mat.cols_; ++j)
            os << std::setw(4) << mat.data_[i][j];
        os << '\n';
    }
    return os;
}