#pragma once

#include <stdexcept> // std::out_of_range
#include <ostream>   // std::ostream

/**
 * @brief Třída reprezentující matici a operace nad ní.
 */
class Matrix {
private:
    int rows_;
    int cols_;
    int** data_;

    // Soukromé pomocné metody
    void allocateMatrix();
    void deallocateMatrix();

public:
    // Konstruktor prázdné matice 0x0
    Matrix();

    // Konstruktor s rozměry
    Matrix(int rows, int cols);

    // Destruktor
    ~Matrix();

    // Kopírovací konstruktor (hluboká kopie)
    Matrix(const Matrix& other);

    // Gettery
    int getRows() const;
    int getCols() const;

    // Přístup k prvkům
    int getValue(int row, int col) const;
    void setValue(int row, int col, int value);

    // Odečítání matic (this - other)
    Matrix subtract(const Matrix& other) const;

    // Transpozice (náhrada za transpose())
    Matrix T() const;

    // ================== OPERÁTORY ==================

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
     * @brief Přetížení operátoru * pro násobení skalárem  (Matrix * scalar).
     */
    Matrix operator*(int scalar) const;

    /**
     * @brief Přetížení operátoru << pro výpis matice do std::ostream.
     * Nahrazuje metodu print().
     */
    friend std::ostream& operator<<(std::ostream& os, const Matrix& mat);
};
