#pragma once

#include <stdexcept> // Pro std::out_of_range
#include <ostream>   // Pro std::ostream

/**
 * @brief Třída reprezentující matici a operace nad ní.
 * Finální hlavičkový soubor pro Úkol 4.
 */
class Matrix {
private:
    int rows_;
    int cols_;
    int** data_;

    // Deklarace soukromých pomocných metod
    // (Implementace je skryta v .cpp souboru)
    void allocateMatrix();
    void deallocateMatrix();

public:
    // --- Konstruktory a destruktor ---
    Matrix(); // Výchozí konstruktor
    Matrix(int rows, int cols); // Hlavní konstruktor
    ~Matrix(); // Destruktor
    Matrix(const Matrix& other); // Kopírovací konstruktor
    
    // --- Gettery (jsou 'const', protože jen čtou) ---
    int getRows() const;
    int getCols() const;
    int getValue(int row, int col) const;
    
    // --- Setter (není 'const', protože mění data) ---
    void setValue(int row, int col, int value);
    
    // --- Operace (jsou 'const', protože nemění 'this' matici) ---
    Matrix subtract(const Matrix& other) const;
    Matrix T() const; // Transpozice

    // --- Přetížené operátory (také 'const') ---

    /**
     * @brief Přetížení operátoru + pro sčítání matic.
     */
    Matrix operator+(const Matrix& other) const;

    /**
     * @brief Přetížení operátoru * pro násobení matic.
     */
    Matrix operator*(const Matrix& other) const;

    /**
     * @brief Přetížení operátoru * pro násobení skalárem (Matrix * scalar).
     */
    Matrix operator*(int scalar) const;

    /**
     * @brief Přetížení operátoru << pro výpis matice do std::ostream.
     * Toto je 'friend' funkce, není přímou součástí třídy.
     */
    friend std::ostream& operator<<(std::ostream& os, const Matrix& mat);
};