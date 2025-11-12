#pragma once

#include <stdexcept> 
#include <ostream>   
class Matrix {
private:
    int rows_;
    int cols_;
    int** data_;

    void allocateMatrix();
    void deallocateMatrix();

public:

    Matrix();
    ~Matrix();
    Matrix(int rows, int cols);
    Matrix(const Matrix& other);
    Matrix& operator=(const Matrix& other);

    int getRows() const;
    int getCols() const;
    int getValue(int row, int col) const;
    void setValue(int row, int col, int value);
    
    Matrix subtract(const Matrix& other) const;
    Matrix T();

    // Deklarace pro operátory +, *, <<

    Matrix operator+(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;
    Matrix operator*(int scalar) const;
    friend std::ostream& operator<<(std::ostream &os, const Matrix &mat);


};