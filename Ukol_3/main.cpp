#include <iostream>
#include <iomanip> // Pro std::setw
#include <stdexcept> // Pro případné výjimky

using namespace std;
// ===================================================================
// 1. ČÁST: DEFINICE A IMPLEMENTACE TŘÍDY MATRIX
// ===================================================================

/**
 * @brief Třída reprezentující matici a operace nad ní.
 * Implementace metod je psána přímo v těle třídy.
 */
class Matrix {
private:
    int rows_;
    int cols_;
    int** data_;

    /**
     * @brief Soukromá pomocná funkce pro alokaci paměti a inicializaci na 0.
     * Volá se v konstruktorech.
     */
    void allocateMatrix() {
        if (rows_ <= 0 || cols_ <= 0) {
            data_ = nullptr;
            return;
        }
        
        data_ = new int*[rows_];
        for (int i =0; i < rows_; i++) {
            data_[i] = new int[cols_]; 
        }

        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < cols_; j++) {
                data_[i][j] = 0;
            }
        }
        
    }

    /**
     * @brief Soukromá pomocná funkce pro uvolnění alokované paměti.
     * Volá se v destruktoru a operátoru přiřazení.
     */
    void deallocateMatrix() {
        if (data_ == nullptr) return;

        if (rows_ > 0) {
            for (int i = 0; i < rows_; i++) {
                delete[] data_[i];
                data_[i] = nullptr;
            }
        }
        delete[] data_;
        data_ = nullptr;
    }

public:
    /**
     * @brief Konstruktor: Vytvoří matici daných rozměrů.
     * @param rows Počet řádků.
     * @param cols Počet sloupců.
     */
    Matrix(int rows, int cols)
        : rows_(rows), cols_(cols), data_(nullptr)
    {
        allocateMatrix();
    }

    /**
     * @brief Destruktor: Uvolní alokovanou paměť.
     */
    ~Matrix() {
        deallocateMatrix();
    }

    /**
     * @brief Kopírovací konstruktor (Hluboká kopie).
     * @param other Matice, ze které se kopíruje.
     */
   Matrix(const Matrix& other)
        : rows_(other.rows_), cols_(other.cols_), data_(nullptr)
    {
        allocateMatrix();
        
        if (data_ != nullptr && other.data_ != nullptr) {
            for (int i = 0; i < rows_; ++i) {
                for (int j = 0; j < cols_; ++j) {
                    data_[i][j] = other.data_[i][j];
                }
            }
        }
    }

    /**
     * @brief Vrátí počet řádků matice.
     */
    int getRows() const {
        return rows_;
    }

    /**
     * @brief Vrátí počet sloupců matice.
     */
    int getCols() const {
        return cols_; 
    }

    /**
     * @brief Vrátí hodnotu na dané pozici.
     * Pokud jsou indexy mimo rozsah, vyhodí std::out_of_range.
     * @param row Index řádku.
     * @param col Index sloupce.
     */
    int getValue(int row, int col) const {
        if (data_ == nullptr) {
            throw out_of_range("Matice je prázdná");
        }
        if (row < 0 || row >= rows_ || col < 0 || col >= cols_) {
            throw out_of_range("Index je mimo rozsah");
        }
        return data_[row][col];
    }

    /**
     * @brief Nastaví hodnotu na dané pozici.
     * Pokud jsou indexy mimo rozsah, vyhodí std::out_of_range.
     * @param row Index řádku.
     * @param col Index sloupce.
     * @param value Nová hodnota.
     */
    void setValue(int row, int col, int value) {
        if (data_ == nullptr) {
            throw std::out_of_range("Matice je prázdná");
        }
        if (row < 0 || row >= rows_ || col < 0 || col >= cols_) {
            throw std::out_of_range("Index je mimo rozsah");
        }
        data_[row][col] = value;
    }

    /**
     * @brief Vytiskne matici do konzole.
     */
    void print() const {
        cout << "Matrix (" << rows_ << "x" << cols_ << ")" << endl;
        if (data_ == nullptr) {
            cout << "<empty matrix>" << endl;
            return;
        }
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                cout << setw(4) << data_[i][j] << " ";
            }
            cout << endl;
        }
    }

    /**
     * @brief Sečte tuto matici s jinou maticí.
     * @param other Matice, která se přičítá.
     * @return Nový objekt Matrix s výsledkem součtu.
     * Vrací Matrix(0, 0) pokud operace není možná.
     */
    Matrix add(const Matrix& other) const {
       if (rows_ != other.rows_ || cols_ != other.cols_) {
            return Matrix(0, 0);
        }
        Matrix result(rows_, cols_);
        if (data_ == nullptr || other.data_ == nullptr) return Matrix(0, 0);

        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                result.data_[i][j] = data_[i][j] + other.data_[i][j];
            }
        }
        return result;
    }

    /**
     * @brief Odečte jinou matici od této (this - other).
     * @param other Matice, která se odčítá.
     * @return Nový objekt Matrix s výsledkem rozdílu.
     * Vrací Matrix(0, 0) pokud operace není možná.
     */
    Matrix subtract(const Matrix& other) const {
         if (rows_ != other.rows_ || cols_ != other.cols_) {
            return Matrix(0, 0);
        }
        Matrix result(rows_, cols_);
        if (data_ == nullptr || other.data_ == nullptr) return Matrix(0, 0);

        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                result.data_[i][j] = data_[i][j] - other.data_[i][j];
            }
        }
        return result;
    }

    /**
     * @brief Vynásobí tuto matici jinou maticí (this * other).
     * @param other Matice, kterou se násobí.
     * @return Nový objekt Matrix s výsledkem násobení.
     * Vrací Matrix(0, 0) pokud operace není možná.
     */
    Matrix multiply(const Matrix& other) const {
        if (cols_ != other.rows_) {
            return Matrix(0, 0);
        }
        if (data_ == nullptr || other.data_ == nullptr) return Matrix(0, 0);

        Matrix result(rows_, other.cols_);

        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < other.cols_; ++j) {
                int sum = 0;
                for (int k = 0; k < cols_; ++k) {
                    sum += data_[i][k] * other.data_[k][j];
                }
                result.data_[i][j] = sum;
            }
        }
        return result;
    }

    /**
     * @brief Vytvoří transponovanou matici k této matici.
     * @return Nový objekt Matrix, který je transpozicí.
     */
    Matrix transpose() const {
       if (data_ == nullptr) return Matrix(0, 0);

        Matrix result(cols_, rows_);
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                result.data_[j][i] = data_[i][j];
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
int main() {
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

