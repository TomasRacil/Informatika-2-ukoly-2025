#pragma once

#include <stdexcept> // Pro std::out_of_range
#include <ostream>   // Pro std::ostream

class Matrix
{
private:
    int rows_;
    int cols_;
    int **data_;

    void allocateMatrix();
    void deallocateMatrix();

public:
    // Konstruktory a destruktor
    Matrix(); // default konstruktor pro 0x0 matici
    Matrix(int rows, int cols);
    Matrix(const Matrix &other); // kopírovací konstruktor
    ~Matrix();

    // Gettery a settery
    int getRows() const;
    int getCols() const;
    int getValue(int row, int col) const;
    void setValue(int row, int col, int value);

    // Metody
    Matrix subtract(const Matrix &other) const;
    Matrix T() const; // transpozice (dříve transpose)

    // Operátory
    Matrix operator+(const Matrix &other) const;
    Matrix operator*(const Matrix &other) const;
    Matrix operator*(int scalar) const;
    Matrix &operator=(const Matrix &other);
    friend std::ostream &operator<<(std::ostream &os, const Matrix &mat);
};