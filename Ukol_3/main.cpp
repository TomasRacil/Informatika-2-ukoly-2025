#include <iostream>
#include <iomanip>   // Pro std::setw
#include <stdexcept> // Pro případné výjimky

// ===================================================================
// 1. ČÁST: DEFINICE A IMPLEMENTACE TŘÍDY MATRIX
// ===================================================================

class Matrix
{
private:
    int rows_;
    int cols_;
    int **data_;

    void allocateMatrix()
    {
        // Pokud jsou rozměry 0 nebo záporné, nastavíme data_ na nullptr
        if (rows_ <= 0 || cols_ <= 0)
        {
            data_ = nullptr;
            return;
        }

        data_ = new int *[rows_];

        for (int i = 0; i < rows_; i++)
        {
            data_[i] = new int[cols_]();
        }
    }

    void deallocateMatrix()
    {
        if (data_ != nullptr)
        {
            for (int i = 0; i < rows_; i++)
            {
                delete[] data_[i];
            }
            delete[] data_;
            data_ = nullptr;
        }
    }

public:
    // Konstruktor
    Matrix(int rows, int cols)
    {
        if (rows <= 0 || cols <= 0)
        {
            rows_ = 0;
            cols_ = 0;
            data_ = nullptr;
            return;
        }
        rows_ = rows;
        cols_ = cols;
        allocateMatrix();
    }

    // Destruktor
    ~Matrix()
    {
        deallocateMatrix();
    }

    // Kopírovací konstruktor
    Matrix(const Matrix &other)
    {
        rows_ = other.rows_;
        cols_ = other.cols_;

        data_ = nullptr;
        allocateMatrix();

        if (data_ != nullptr && other.data_ != nullptr)
        {
            for (int i = 0; i < rows_; i++)
            {
                for (int j = 0; j < cols_; j++)
                {
                    data_[i][j] = other.data_[i][j];
                }
            }
        }
    }

    int getRows() const
    {
        // TODO: Vraťte rows_
        return rows_; // Nahraďte
    }

    int getCols() const
    {
        // TODO: Vraťte cols_
        return cols_; // Nahraďte
    }

    // Getter pro hodnotu
    int getValue(int row, int col) const
    {
        if (row < 0 || row >= rows_ || col < 0 || col >= cols_ || data_ == nullptr)
        {
            throw std::out_of_range("Index mimo rozsah nebo prázdná matice");
        }
        return data_[row][col];
    }

    // Setter pro hodnotu
    void setValue(int row, int col, int value)
    {
        if (row < 0 || row >= rows_ || col < 0 || col >= cols_ || data_ == nullptr)
        {
            throw std::out_of_range("Index mimo rozsah nebo prázdná matice");
        }
        data_[row][col] = value;
    }

    // Výpis matice
    void print() const
    {
        std::cout << "Matice (" << rows_ << "x" << cols_ << ")" << std::endl;
        if (data_ == nullptr)
        {
            std::cout << "Prázná matice" << std::endl;
            return;
        }

        for (int i = 0; i < rows_; i++)
        {
            for (int j = 0; j < cols_; j++)
            {
                std::cout << std::setw(4) << data_[i][j];
            }
            std::cout << std::endl;
        }
    }

    Matrix add(const Matrix &other) const
    {
        // Sčítání matic
        if (rows_ != other.rows_ || cols_ != other.cols_)
        {
            return Matrix(0, 0);
        }

        Matrix result(rows_, cols_);
        for (int i = 0; i < rows_; i++)
        {
            for (int j = 0; j < cols_; j++)
            {
                result.setValue(i, j, getValue(i, j) + other.getValue(i, j));
            }
        }
        return result;
    }

    Matrix subtract(const Matrix &other) const
    {
        // Odčítání matic
        if (rows_ != other.rows_ || cols_ != other.cols_)
        {
            return Matrix(0, 0);
        }

        Matrix result(rows_, cols_);
        for (int i = 0; i < rows_; i++)
        {
            for (int j = 0; j < cols_; j++)
            {
                result.setValue(i, j, getValue(i, j) - other.getValue(i, j));
            }
        }
        return result;
    }

    Matrix multiply(const Matrix &other) const
    {
        // Násobení matic
        if (cols_ != other.rows_)
        {
            return Matrix(0, 0);
        }

        Matrix result(rows_, other.cols_);
        for (int i = 0; i < rows_; i++)
        {
            for (int j = 0; j < other.cols_; j++)
            {
                int suma = 0;
                for (int k = 0; k < cols_; k++)
                {
                    suma += getValue(i, k) * other.getValue(k, j);
                }
                result.setValue(i, j, suma);
            }
        }
        return result;
    }

    Matrix transpose() const
    {
        // Transpozice matice
        Matrix result(cols_, rows_);

        if (data_ != nullptr)
        {
            for (int i = 0; i < rows_; i++)
            {
                for (int j = 0; j < cols_; j++)
                {
                    result.setValue(j, i, getValue(i, j));
                }
            }
        }
        return result;
    }
};

// ===================================================================
// 2. ČÁST: HLAVNÍ FUNKCE (PRO VAŠE TESTOVÁNÍ)
// ===================================================================

// Tento soubor se nespustí, pokud jsou spuštěny testy (díky __TEST__ definici)
#ifndef __TEST__
int main()
{
    std::cout << "--- Testovani tridy Matrix ---" << std::endl;

    // Vytvoření matice A
    Matrix matA(2, 3);
    matA.setValue(0, 0, 1);
    matA.setValue(0, 1, 2);
    matA.setValue(0, 2, 3);
    matA.setValue(1, 0, 4);
    matA.setValue(1, 1, 5);
    matA.setValue(1, 2, 6);

    std::cout << "Matice A (2x3):" << std::endl;
    matA.print();

    // Vytvoření matice B
    Matrix matB(3, 2);
    matB.setValue(0, 0, 7);
    matB.setValue(0, 1, 8);
    matB.setValue(1, 0, 9);
    matB.setValue(1, 1, 10);
    matB.setValue(2, 0, 11);
    matB.setValue(2, 1, 12);

    std::cout << "\nMatice B (3x2):" << std::endl;
    matB.print();

    // Test násobení
    Matrix matC = matA.multiply(matB);
    std::cout << "\nVysledek A * B (2x2):" << std::endl;
    matC.print();

    // Test transpozice
    Matrix matT = matA.transpose();
    std::cout << "\nTransponovana matice A (3x2):" << std::endl;
    matT.print();

    // Test sčítání
    Matrix matA2(2, 3);
    matA2.setValue(0, 0, 10);
    matA2.setValue(1, 1, 10);

    std::cout << "\nMatice A2 (2x3):" << std::endl;
    matA2.print();

    Matrix matSum = matA.add(matA2);
    std::cout << "\nVysledek A + A2 (2x3):" << std::endl;
    matSum.print();

    // Test kopírovacího konstruktoru
    std::cout << "\nTest kopie matice A:" << std::endl;
    Matrix matA_copy = matA;
    matA_copy.print();

    // Ověření hluboké kopie
    matA.setValue(0, 0, 99);
    std::cout << "\nMatice A po zmene (0,0) na 99:" << std::endl;
    matA.print();
    std::cout << "\nKopie matice A (mela by zustat nezmenena):" << std::endl;
    matA_copy.print();

    std::cout << "\n--- Testovani dokonceno ---" << std::endl;

    return 0;
}
#endif // __TEST__