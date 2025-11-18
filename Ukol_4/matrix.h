#pragma once

#include <stdexcept> // Pro std::out_of_range
#include <ostream>   // Pro std::ostream

/**
 * @brief Třída reprezentující matici a operace nad ní.
 * * TODO: Zkopírujte sem definici (deklaraci) vaší třídy Matrix z Ukolu 3.
 * Níže jsou uvedeny metody, které by třída měla obsahovat,
 * plus nové operátory pro Ukol 4.
 */
class Matrix {
private:
    int rows_;
    int cols_;
    int** data_;

    // TODO: Zkopírujte sem deklarace soukromých metod (allocateMatrix, deallocateMatrix)
    void allocateMatrix();
    void deallocateMatrix();

public:
    // TODO: Zkopírujte sem deklarace veřejných metod z Ukolu 3
    // (Konstruktor, Destruktor, Kopírovací konstruktor, gettery, settery,
    // subtract, transpose)

    // Příklad (doplňte zbytek):
    Matrix();
    Matrix(int rows, int cols);
    ~Matrix();
    Matrix(const Matrix& other);

    int getRows() const;
    int getCols() const;
    int getValue(int row, int col) const;
    void setValue(int row, int col, int value);

    Matrix subtract(const Matrix& other) const;
    Matrix T() const;

    // Deklarace pro operátory +, *, <<

    /**
     * @brief Přetížení operátoru + pro sčítání matic.
     * Nahrazuje metodu 'add'.
     */
    Matrix operator+(const Matrix& other) const;

    /**
     * @brief Přetížení operátoru * pro násobení matic.
     * Nahrazuje metodu 'multiply'.
     */
    Matrix operator*(const Matrix& other) const;

    /**
     * @brief Přetížení operátoru * pro násobení skalárem  (Matrix*scalar).
     */
    Matrix operator*(int scalar) const;

    /**
     * @brief Přetížení operátoru << pro výpis matice do std::ostream.
     */
    friend std::ostream& operator<<(std::ostream& os, const Matrix& mat);
};