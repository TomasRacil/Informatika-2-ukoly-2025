#pragma once

<<<<<<< HEAD
#include <stdexcept> // std::out_of_range
#include <ostream>   // std::ostream

/**
 * @brief Třída reprezentující matici a operace nad ní.
=======
#include <stdexcept> // Pro std::out_of_range
#include <ostream>   // Pro std::ostream

/**
 * @brief Třída reprezentující matici a operace nad ní.
 * * TODO: Zkopírujte sem definici (deklaraci) vaší třídy Matrix z Ukolu 3.
 * Níže jsou uvedeny metody, které by třída měla obsahovat,
 * plus nové operátory pro Ukol 4.
>>>>>>> b53231f (Ukol_4)
 */
class Matrix {
private:
    int rows_;
    int cols_;
    int** data_;

<<<<<<< HEAD
    // Soukromé pomocné metody
=======
    // TODO: Zkopírujte sem deklarace soukromých metod (allocateMatrix, deallocateMatrix)
>>>>>>> b53231f (Ukol_4)
    void allocateMatrix();
    void deallocateMatrix();

public:
<<<<<<< HEAD
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
=======
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
    
    Matrix subtract(const Matrix& other);
    Matrix T();

    // Deklarace pro operátory +, *, <<
>>>>>>> b53231f (Ukol_4)

    /**
     * @brief Přetížení operátoru + pro sčítání matic.
     * Nahrazuje metodu 'add'.
     */
<<<<<<< HEAD
    Matrix operator+(const Matrix& other) const;
=======
    Matrix operator+(const Matrix& other);
>>>>>>> b53231f (Ukol_4)

    /**
     * @brief Přetížení operátoru * pro násobení matic.
     * Nahrazuje metodu 'multiply'.
     */
<<<<<<< HEAD
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
=======
    Matrix operator*(const Matrix& other);

    /**
     * @brief Přetížení operátoru * pro násobení skalárem  (Matrix*scalar).
     */
    Matrix operator*(int scalar);

    /**
     * @brief Přetížení operátoru << pro výpis matice do std::ostream.
     */
    friend std::ostream& operator<<(std::ostream& os, const Matrix& mat);


};
>>>>>>> b53231f (Ukol_4)
