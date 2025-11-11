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

void Matrix::allocateMatrix() {
        // Pokud je některý rozměr 0 nebo záporný, považujeme matici za prázdnou.
        if (rows_ <= 0 || cols_ <= 0) {
            data_ = nullptr;
            return;
        }

        // Alokace pole pointerů na řádky
        data_ = new int*[rows_];

        // Pro každý řádek alokujeme pole intů a inicializujeme na 0
        for (int i = 0; i < rows_; ++i) {
            data_[i] = new int[cols_];
            for (int j = 0; j < cols_; ++j) {
                data_[i][j] = 0;
            }
        }
    }

    void Matrix::deallocateMatrix() {
         // TODO: Uvolněte paměť alokovanou pro data_.
        if (data_ == nullptr) {
            return;
        }
        // 1. V cyklu uvolněte paměť pro každý řádek (pokud data_ není nullptr a rows_ > 0)
        // 2. Uvolněte paměť pro pole pointerů (pokud data_ není nullptr)
        for (int i = 0; i < rows_; ++i) {
            delete[] data_[i];
        }

        delete[] data_;
        data_ = nullptr;
    }

    Matrix::Matrix() {
    rows_ = 0;
    cols_ = 0;
    data_ = nullptr;
    }

    Matrix::Matrix(int rows, int cols) {
        // TODO: Nastavte rows_ a cols_
        // TODO: Zavolejte allocateMatrix()
        rows_ = rows;
        cols_ = cols;
        if( rows_ <=0 || cols_ <=0){
            rows_=0;
            cols_=0;
            
        }
        allocateMatrix();   
    }

    Matrix::~Matrix() {
        // TODO: Zavolejte deallocateMatrix()
        deallocateMatrix();
    }

    Matrix::Matrix(const Matrix& other) {
        // TODO: Implementujte kopírovací konstruktor (hluboká kopie)
        // 1. Zkopírujte rows_ a cols_ z 'other'
        rows_ = other.rows_;
        cols_ = other.cols_;
        
        // 2. Alokujte vlastní paměť (volejte allocateMatrix)
        // ...
        allocateMatrix();
        
        // 3. Zkopírujte hodnoty z other.data_ do this->data_
        // (Pouze pokud data_ a other.data_ nejsou nullptr)
        if (data_ != nullptr && other.data_ != nullptr) {
            for (int i = 0; i < rows_; ++i) {
                for (int j = 0; j < cols_; ++j) {
                    data_[i][j] = other.data_[i][j];
                }
            }
        }
    }

    int Matrix::getRows() const {
        // TODO: Vraťte rows_
        return rows_; // Nahraďte
    }

    int Matrix::getCols() const {
        // TODO: Vraťte cols_
        return cols_; // Nahraďte
    }

    int Matrix::getValue(int row, int col) const {
        // TODO: Vraťte hodnotu na pozici [row][col]
        // Nezapomeňte ošetřit neplatné indexy (vyhodit std::out_of_range)
        // a ošetřit případ, kdy data_ == nullptr.
        if (data_ == nullptr) {
            throw std::out_of_range("Matrix is empty");
        }
        if (row < 0 || row >= rows_ || col < 0 || col >= cols_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[row][col];
    }

    void Matrix::setValue(int row, int col, int value) {
        // TODO: Nastavte hodnotu na pozici [row][col]
        // Nezapomeňte ošetřit neplatné indexy (vyhodit std::out_of_range)
        // a ošetřit případ, kdy data_ == nullptr.
        // data_[row][col] = value;
        if (data_ == nullptr) {
            throw std::out_of_range("Matrix is empty");
        }
        if (row < 0 || row >= rows_ || col < 0 || col >= cols_) {
            throw std::out_of_range("Index out of range");
        }
        data_[row][col] = value;
    }

// ===================================================================
// KROK 2: IMPLEMENTACE OPERÁTORŮ PRO ÚKOL 4
// ===================================================================

Matrix Matrix::subtract(const Matrix &other)
{
     Matrix result(rows_, cols_);
        // ... doplňte výpočet
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                int diff = this->getValue(i, j) - other.getValue(i, j);
                result.setValue(i, j, diff);
            }
        }
        return result;
    
}

Matrix Matrix::T()
{
    Matrix result(this->cols_, this->rows_);

        // TODO: Proveďte transpozici
        // (Projděte původní matici a hodnoty ukládejte do 'result' na prohozené pozice)
        for (int i = 0; i < this->rows_; ++i) {
            for (int j = 0; j < this->cols_; ++j) {
                result.setValue(j, i, this->getValue(i, j));
            }
        }

        return result;
}

Matrix Matrix::operator+(const Matrix &other)
{
    if( rows_ != other.rows_ || cols_ != other.cols_){
            return Matrix(0,0);
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
    Matrix result (rows_, cols_);
    if(!data_) return result;
    for (int i=0; i<rows_; i++){
        for(int j = 0;j<cols_; j++){
            result.data_[i][j] = data_[i][j] * scalar;
        }
    }
    return result;
}

std::ostream &operator<<(std::ostream &os, const Matrix &mat)
{
    os << "Matrix (" << mat.rows_ << "x" << mat.cols_ << ")" << std::endl;
        // ... doplňte cykly pro výpis prvků
        for (int i = 0; i < mat.rows_; ++i) {
            for (int j = 0; j < mat.cols_; ++j) {
                os << std::setw(4) << mat.data_[i][j];
            }
            os << std::endl;
        }
    return os;
}