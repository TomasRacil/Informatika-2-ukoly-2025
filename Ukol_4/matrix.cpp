#include "matrix.h"

// Potřebné include pro implementaci
#include <iostream>
#include <iomanip>

// ===================================================================
// POMOCNÉ METODY
// ===================================================================

void Matrix::allocateMatrix() {
    // Pokud je některý rozměr 0, nemáme co alokovat
    if (rows_ <= 0 || cols_ <= 0) {
        data_ = nullptr;
        return;
    }

    // 1) alokace pole ukazatelů (řádky)
    data_ = new int*[rows_];

    // 2) pro každý řádek alokace pole intů (sloupce)
    for (int r = 0; r < rows_; ++r) {
        data_[r] = new int[cols_];
    }

    // 3) inicializace všech prvků na 0
    for (int r = 0; r < rows_; ++r) {
        for (int c = 0; c < cols_; ++c) {
            data_[r][c] = 0;
        }
    }
}

void Matrix::deallocateMatrix() {
    if (data_ != nullptr) {
        // uvolnění jednotlivých řádků
        for (int r = 0; r < rows_; ++r) {
            delete[] data_[r];
        }
        // uvolnění pole ukazatelů
        delete[] data_;
        data_ = nullptr;
    }
}

// ===================================================================
// KROK 1: IMPLEMENTACE Z ÚKOLU 3
// ===================================================================

Matrix::Matrix()
    : rows_(0), cols_(0), data_(nullptr)
{
}

Matrix::Matrix(int rows, int cols)
    : rows_(rows), cols_(cols), data_(nullptr)
{
    // při záporných rozměrech vytvoříme prázdnou matici 0x0
    if (rows_ < 0) rows_ = 0;
    if (cols_ < 0) cols_ = 0;

    allocateMatrix(); // pokud jsou 0x0, nastaví data_ = nullptr
}

Matrix::~Matrix() {
    deallocateMatrix();
}

Matrix::Matrix(const Matrix& other)
    : rows_(other.rows_), cols_(other.cols_), data_(nullptr)
{
    allocateMatrix();

    if (data_ != nullptr && other.data_ != nullptr) {
        for (int r = 0; r < rows_; ++r) {
            for (int c = 0; c < cols_; ++c) {
                data_[r][c] = other.data_[r][c];
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
    if (data_ == nullptr) {
        throw std::out_of_range("Matice je prazdna (0x0).");
    }
    if (row < 0 || row >= rows_ || col < 0 || col >= cols_) {
        throw std::out_of_range("Index mimo rozsah v getValue().");
    }
    return data_[row][col];
}

void Matrix::setValue(int row, int col, int value) {
    if (data_ == nullptr) {
        throw std::out_of_range("Matice je prazdna (0x0).");
    }
    if (row < 0 || row >= rows_ || col < 0 || col >= cols_) {
        throw std::out_of_range("Index mimo rozsah v setValue().");
    }
    data_[row][col] = value;
}

Matrix Matrix::subtract(const Matrix& other) const {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        return Matrix(0, 0);
    }
    if (data_ == nullptr || other.data_ == nullptr) {
        return Matrix(0, 0);
    }

    Matrix result(rows_, cols_);
    for (int r = 0; r < rows_; ++r) {
        for (int c = 0; c < cols_; ++c) {
            result.data_[r][c] = data_[r][c] - other.data_[r][c];
        }
    }
    return result;
}

Matrix Matrix::T() const {
    if (data_ == nullptr) {
        return Matrix(0, 0);
    }

    Matrix result(cols_, rows_);
    for (int r = 0; r < rows_; ++r) {
        for (int c = 0; c < cols_; ++c) {
            result.data_[c][r] = data_[r][c];
        }
    }
    return result;
}

// ===================================================================
// KROK 2: IMPLEMENTACE OPERÁTORŮ PRO ÚKOL 4
// ===================================================================

Matrix Matrix::operator+(const Matrix& other) const {
    // stejné chování jako původní add()
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        return Matrix(0, 0);
    }
    if (data_ == nullptr || other.data_ == nullptr) {
        return Matrix(0, 0);
    }

    Matrix result(rows_, cols_);
    for (int r = 0; r < rows_; ++r) {
        for (int c = 0; c < cols_; ++c) {
            result.data_[r][c] = data_[r][c] + other.data_[r][c];
        }
    }
    return result;
}

Matrix Matrix::operator*(const Matrix& other) const {
    // stejné chování jako původní multiply()
    if (cols_ != other.rows_) {
        return Matrix(0, 0);
    }
    if (data_ == nullptr || other.data_ == nullptr) {
        return Matrix(0, 0);
    }

    Matrix result(rows_, other.cols_);
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < other.cols_; ++j) {
            long long sum = 0;
            for (int k = 0; k < cols_; ++k) {
                sum += static_cast<long long>(data_[i][k]) * other.data_[k][j];
            }
            result.data_[i][j] = static_cast<int>(sum);
        }
    }
    return result;
}

Matrix Matrix::operator*(int scalar) const {
    if (rows_ <= 0 || cols_ <= 0 || data_ == nullptr) {
        return Matrix(0, 0);
    }

    Matrix result(rows_, cols_);
    for (int r = 0; r < rows_; ++r) {
        for (int c = 0; c < cols_; ++c) {
            result.data_[r][c] = data_[r][c] * scalar;
        }
    }
    return result;
}

std::ostream& operator<<(std::ostream& os, const Matrix& mat) {
    os << "Matrix (" << mat.rows_ << "x" << mat.cols_ << ")\n";
    if (mat.rows_ <= 0 || mat.cols_ <= 0 || mat.data_ == nullptr) {
        os << "(prazdna)\n";
        return os;
    }

    for (int r = 0; r < mat.rows_; ++r) {
        for (int c = 0; c < mat.cols_; ++c) {
            os << std::setw(4) << mat.data_[r][c];
        }
        os << '\n';
    }
    return os;
}

