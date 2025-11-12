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


// ===================================================================
// KROK 2: IMPLEMENTACE OPERÁTORŮ PRO ÚKOL 4
// ===================================================================
void Matrix::allocateMatrix()
{
    if (rows_ <= 0 || cols_ <= 0) 
        {
        data_ = nullptr;
        return;
        }

        data_ = new int*[rows_];
        for (int i = 0; i < rows_; ++i) 
        {
            data_[i] = new int[cols_];
            for (int j = 0; j < cols_; ++j) 
            {
            data_[i][j] = 0;
            }
        }
}

void Matrix::deallocateMatrix()
{
     if(data_ != nullptr && rows_ > 0)
        {
        for(int i = 0; i<rows_; i++)
        {
            delete[] data_[i];

        }
        delete[] data_; 
        data_ = nullptr;
        }
}

Matrix::Matrix()
{
    allocateMatrix();
}

Matrix::Matrix(int rows, int cols)
{
        this->cols_ = cols;
        this->rows_ = rows;
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
        
        // 2. Alokujte vlastní paměť (volejte allocateMatrix)
        // ...
        data_ = nullptr; // Nahraďte

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

int Matrix::getRows() const
{
    // TODO: Vraťte rows_
        if(this->rows_>0)
        {
        return this->rows_;
        }
        else{
            return 0;
        }
}

int Matrix::getCols() const
{
    if(this->cols_>0)
        {
        return this->cols_; // Nahraďte
        }
        else
        {
            return 0;
        }
}

int Matrix::getValue(int row, int col) const
{
    if (data_ == nullptr || row < 0 || col < 0 || row >= rows_ || col >= cols_) {
        throw std::out_of_range("Index mimo rozsah");
    }
    return data_[row][col];
}

void Matrix::setValue(int row, int col, int value)
{
     if (data_ == nullptr || row < 0 || col < 0 || row >= rows_ || col >= cols_) {
        throw std::out_of_range("Index mimo rozsah");
    }
    data_[row][col] = value;
}

Matrix Matrix::subtract(const Matrix &other)
{
    if(other.rows_ == rows_ && other.cols_ == cols_)
        {
            Matrix result(rows_, cols_);

            for(int i = 0; i<rows_;i++)
            {
                for(int j=0; j<cols_; j++)
                {
                    result.data_[i][j] = data_[i][j]- other.data_[i][j];
                }
            }
            return result;
        }
        else
        {
            return Matrix(0,0);
        }
}

Matrix Matrix::T()
{
        Matrix result(cols_, rows_);

        for (int i = 0; i < rows_; i++)
        {
        for (int j = 0; j < cols_; j++) {
            result.data_[j][i] = data_[i][j];
        }
        }

        return result;
}

Matrix Matrix::operator+(const Matrix &other)
{
    if(other.rows_ == rows_ && other.cols_ == cols_)
        {
            Matrix result(rows_, cols_);

            for(int i = 0; i<rows_;i++)
            {
                for(int j=0; j<cols_; j++)
                {
                    result.data_[i][j] = other.data_[i][j] + data_[i][j];
                }
            }
            return result;
        }
        else
        {
            return Matrix(0,0);
        }
}

Matrix Matrix::operator*(const Matrix &other)
{
    Matrix result(rows_, other.cols_);
        if(other.rows_ == cols_ && other.cols_ == rows_)
        {
            for(int i=0; i<rows_; i++)
            {
            for(int j =0; j<other.cols_; j++)
            {
                for(int k = 0; k < cols_; k++)
                {
                    result.data_[i][j] += data_[i][k] * other.data_[k][j];
                }
            }
            }
            return result;
        }
        else
        {
            return Matrix(0,0);
        }
}

Matrix Matrix::operator*(int scalar)
{
    Matrix result(this->rows_, this->cols_);

    for (int i = 0; i < this->rows_; i++)
    {
        for (int j = 0; j < this->cols_; j++)
        {
            result.data_[i][j] = this->data_[i][j] * scalar;
        }
    }
    return result;
}

std::ostream &operator<<(std::ostream &os, const Matrix &mat)
{
    os  << "Matrix (" << mat.rows_ << "x" << mat.cols_ << ")" << std::endl;
        for(int i =0; i<mat.rows_; i++)
        {
            for(int j = 0; j<mat.cols_;j++)
            {
                os << mat.data_[i][j] << std::setw(4);
            }
            os << '\n';
        }
    return os;
}
