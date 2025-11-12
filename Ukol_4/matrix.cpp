#include "matrix.h"

// Potřebné #include pro implementaci
#include <iostream>
#include <iomanip>
#include <stdexcept> // pro std::out_of_range

// ===================================================================
// KROK 1: IMPLEMENTACE Z ÚKOLU 3
// ===================================================================

// --- Implementace privátních pomocných metod ---

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
    if (data_ != nullptr) {
        
        for (int i = 0; i < rows_; ++i) {
            delete[] data_[i];
        }
       
        delete[] data_;
        data_ = nullptr; 
    }
}

// --- Implementace konstruktorů a destruktoru ---


Matrix::Matrix() {
    rows_ = 0;
    cols_ = 0;
    data_ = nullptr;
}


Matrix::Matrix(int rows, int cols) {
    
    rows_ = (rows < 0) ? 0 : rows;
    cols_ = (cols < 0) ? 0 : cols;
    allocateMatrix(); 
}


Matrix::~Matrix() {
    deallocateMatrix(); 
}


Matrix::Matrix(const Matrix &other) {
    
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

// --- Implementace getterů a setterů ---

int Matrix::getRows() const {
    return rows_;
}

int Matrix::getCols() const {
    return cols_;
}

int Matrix::getValue(int row, int col) const {
    if (data_ == nullptr) {
        throw std::out_of_range("Matrix data is null");
    }
    if (row < 0 || row >= rows_ || col < 0 || col >= cols_) {
        throw std::out_of_range("Index out of range");
    }
    return data_[row][col];
}

void Matrix::setValue(int row, int col, int value) {
    if (data_ == nullptr) {
        throw std::out_of_range("Matrix data is null");
    }
    if (row < 0 || row >= rows_ || col < 0 || col >= cols_) {
        throw std::out_of_range("Index out of range");
    }
    data_[row][col] = value;
}

// --- Implementace ostatních metod ---


Matrix Matrix::subtract(const Matrix &other) const {
    
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        return Matrix(0, 0); 
    }

    Matrix result(rows_, cols_);
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            
            result.setValue(i, j, this->getValue(i, j) - other.getValue(i, j));
        }
    }
    return result;
}


Matrix Matrix::T() const {
    Matrix result(cols_, rows_); 
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            result.setValue(j, i, this->getValue(i, j)); 
        }
    }
    return result;
}


// ===================================================================
// KROK 2: IMPLEMENTACE OPERÁTORŮ PRO ÚKOL 4
// ===================================================================

/**
 * @brief Operátor sčítání (+). Logika z tvé metody add().
 */
Matrix Matrix::operator+(const Matrix &other) const {
    // Tvoje logika z add()
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        return Matrix(0, 0); 
    }

    Matrix result(rows_, cols_);
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            result.setValue(i, j, this->getValue(i, j) + other.getValue(i, j));
        }
    }
    return result;
}

/**
 * @brief Operátor násobení matic (*). Logika z tvé metody multiply().
 */
Matrix Matrix::operator*(const Matrix &other) const {
    // Tvoje logika z multiply()
    if (cols_ != other.rows_) {
        return Matrix(0, 0); 
    }
    
    Matrix result(rows_, other.cols_); 
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

/**
 * @brief Operátor násobení skalárem (Matrix * int).
 */
Matrix Matrix::operator*(int scalar) const {
    Matrix result(rows_, cols_); 
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            result.setValue(i, j, this->getValue(i, j) * scalar);
        }
    }
    return result;
}

/**
 * @brief Operátor výstupu (<<). Logika z tvé metody print().
 * Toto NENÍ členská metoda, proto nemá 'Matrix::'.
 */
std::ostream &operator<<(std::ostream &os, const Matrix &mat) {
    // Tvoje logika z print(), jen 'std::cout' je nahrazeno 'os'
    os << "Matrix (" << mat.getRows() << "x" << mat.getCols() << ")" << std::endl;
    for (int i = 0; i < mat.getRows(); ++i) {
        for (int j = 0; j < mat.getCols(); ++j) {
            os << std::setw(4) << mat.getValue(i, j);
        }
        os << std::endl;
    }
    return os; // Musí vrátit stream pro řetězení (cout << A << B;)
}