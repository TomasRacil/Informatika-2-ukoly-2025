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

Matrix::Matrix()
{
}

Matrix::Matrix(int rows, int cols)
{
}

Matrix::~Matrix()
{
}

Matrix::Matrix(const Matrix &other)
{
}

int Matrix::getRows() const
{
    return 0;
}

int Matrix::getCols() const
{
    return 0;
}

int Matrix::getValue(int row, int col) const
{
    return 0;
}

void Matrix::setValue(int row, int col, int value)
{
}

Matrix Matrix::subtract(const Matrix &other)
{
    return Matrix();
}

Matrix Matrix::T()
{
    return Matrix();
}

Matrix Matrix::operator+(const Matrix &other)
{
    return Matrix();
}

Matrix Matrix::operator*(const Matrix &other)
{
    return Matrix();
}

Matrix Matrix::operator*(int scalar)
{
    return Matrix();
}

std::ostream &operator<<(std::ostream &os, const Matrix &mat)
{
    return os;
}