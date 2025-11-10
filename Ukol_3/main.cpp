#include <iostream>
#include <iomanip> // Pro std::setw
#include <stdexcept> // Pro případné výjimky

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
        // Pokud je některý rozměr 0, nemáme co alokovat
        if (rows_ <= 0 || cols_ <= 0) {
            data_ = nullptr;
            return;
        }

        // 1) alokace pole ukazatelů (řádky)
        data_ = new int*[rows_];

        // 2) pro každý řádek alokace pole intů (sloupce)
        for (int r = 0; r < rows_; ++r) {
            data_[r] = new int[cols_];
        }

        // 3) inicializace všech prvků na 0
        for (int r = 0; r < rows_; ++r) {
            for (int c = 0; c < cols_; ++c) {
                data_[r][c] = 0;
            }
        }
    }

    /**
     * @brief Soukromá pomocná funkce pro uvolnění alokované paměti.
     * Volá se v destruktoru a operátoru přiřazení.
     */
    void deallocateMatrix() {
        if (data_ != nullptr) {
            // uvolnění jednotlivých řádků
            for (int r = 0; r < rows_; ++r) {
                delete[] data_[r];
            }
            // uvolnění pole ukazatelů
            delete[] data_;
            data_ = nullptr;
        }
    }

public:
    /**
     * @brief Konstruktor: Vytvoří matici daných rozměrů.
     * @param rows Počet řádků.
     * @param cols Počet sloupců.
     */
    Matrix(int rows, int cols) : rows_(rows), cols_(cols), data_(nullptr) {
        // Oprava podle testu: při záporných rozměrech nevhazujeme výjimku
        // ale vytvoříme prázdnou matici 0x0
        if (rows_ < 0) rows_ = 0;
        if (cols_ < 0) cols_ = 0;
    
        allocateMatrix(); // pokud jsou 0x0, nastaví data_ = nullptr
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
        : rows_(other.rows_), cols_(other.cols_), data_(nullptr) {
        // 2. Alokujte vlastní paměť
        allocateMatrix();

        // 3. Zkopírujte hodnoty (pokud je co kopírovat)
        if (data_ != nullptr && other.data_ != nullptr) {
            for (int r = 0; r < rows_; ++r) {
                for (int c = 0; c < cols_; ++c) {
                    data_[r][c] = other.data_[r][c];
                }
            }
        }
    }

    // TODO: (Bonus) Operátor přiřazení (=)
    // Matrix& operator=(const Matrix& other);

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
            throw std::out_of_range("Matice je prazdna (0x0).");
        }
        if (row < 0 || row >= rows_ || col < 0 || col >= cols_) {
            throw std::out_of_range("Index mimo rozsah v getValue().");
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
            throw std::out_of_range("Matice je prazdna (0x0).");
        }
        if (row < 0 || row >= rows_ || col < 0 || col >= cols_) {
            throw std::out_of_range("Index mimo rozsah v setValue().");
        }
        data_[row][col] = value;
    }

    /**
     * @brief Vytiskne matici do konzole.
     */
    void print() const {
        std::cout << "Matrix (" << rows_ << "x" << cols_ << ")" << std::endl;
        if (rows_ <= 0 || cols_ <= 0 || data_ == nullptr) {
            std::cout << "(prazdna)" << std::endl;
            return;
        }
        for (int r = 0; r < rows_; ++r) {
            for (int c = 0; c < cols_; ++c) {
                std::cout << std::setw(4) << data_[r][c];
            }
            std::cout << std::endl;
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
        if (data_ == nullptr || other.data_ == nullptr) {
            return Matrix(0, 0);
        }
        for (int r = 0; r < rows_; ++r) {
            for (int c = 0; c < cols_; ++c) {
                result.data_[r][c] = data_[r][c] + other.data_[r][c];
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
        if (data_ == nullptr || other.data_ == nullptr) {
            return Matrix(0, 0);
        }
        for (int r = 0; r < rows_; ++r) {
            for (int c = 0; c < cols_; ++c) {
                result.data_[r][c] = data_[r][c] - other.data_[r][c];
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
        if (data_ == nullptr || other.data_ == nullptr) {
            return Matrix(0, 0);
        }

        Matrix result(rows_, other.cols_);
        // výpočet: result[i][j] = sum_k (this[i][k] * other[k][j])
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < other.cols_; ++j) {
                long long sum = 0; // aby se v mezikrocích nepřeteklo u větších čísel
                for (int k = 0; k < cols_; ++k) {
                    sum += static_cast<long long>(data_[i][k]) * other.data_[k][j];
                }
                // do výsledku uložíme zpět jako int (zadání pracuje s int)
                result.data_[i][j] = static_cast<int>(sum);
            }
        }
        return result;
    }

    /**
     * @brief Vytvoří transponovanou matici k této matici.
     * @return Nový objekt Matrix, který je transpozicí.
     */
    Matrix transpose() const {
        if (data_ == nullptr) {
            return Matrix(0, 0);
        }
        Matrix result(cols_, rows_);
        for (int r = 0; r < rows_; ++r) {
            for (int c = 0; c < cols_; ++c) {
                result.data_[c][r] = data_[r][c];
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


