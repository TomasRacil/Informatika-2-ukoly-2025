#include <iostream>
#include "matrix.h" // Pouze hlavičkový soubor!

// Tento soubor se nespustí, pokud jsou spuštěny testy (díky __TEST__ definici)
#ifndef __TEST__
int main() {
    std::cout << "--- Testovani tridy Matrix (z main.cpp) ---" << std::endl;

    // Vytvoření matice A
    Matrix matA(2, 3);
    matA.setValue(0, 0, 1);
    matA.setValue(0, 1, 2);
    matA.setValue(0, 2, 3);
    matA.setValue(1, 0, 4);
    matA.setValue(1, 1, 5);
    matA.setValue(1, 2, 6);

    std::cout << "Matice A (2x3):" << std::endl;
    // Původní: matA.print();
    std::cout << matA; // Nově pomocí operátoru <<

    // Vytvoření matice B
    Matrix matB(3, 2);
    matB.setValue(0, 0, 7);
    matB.setValue(0, 1, 8);
    matB.setValue(1, 0, 9);
    matB.setValue(1, 1, 10);
    matB.setValue(2, 0, 11);
    matB.setValue(2, 1, 12);

    std::cout << "\nMatice B (3x2):" << std::endl;
    // Původní: matB.print();
    std::cout << matB; // Nově pomocí operátoru <<

    // Test násobení
    // Původní: Matrix matC = matA.multiply(matB);
    Matrix matC = matA * matB; // Nově pomocí operátoru *
    std::cout << "\nVysledek A * B (2x2):" << std::endl;
    std::cout << matC;

    // Test transpozice (zůstává jako metoda)
    Matrix matT = matA.T();
    std::cout << "\nTransponovana matice A (3x2):" << std::endl;
    std::cout << matT;

    // Test sčítání
    Matrix matA2(2, 3);
    matA2.setValue(0, 0, 10);
    matA2.setValue(1, 1, 10);

    std::cout << "\nMatice A2 (2x3):" << std::endl;
    std::cout << matA2;

    // Původní: Matrix matSum = matA.add(matA2);
    Matrix matSum = matA + matA2; // Nově pomocí operátoru +
    std::cout << "\nVysledek A + A2 (2x3):" << std::endl;
    std::cout << matSum;

    // Test kopírovacího konstruktoru
    std::cout << "\nTest kopie matice A:" << std::endl;
    Matrix matA_copy = matA;
    std::cout << matA_copy;

    // Ověření hluboké kopie
    matA.setValue(0, 0, 99);
    std::cout << "\nMatice A po zmene (0,0) na 99:" << std::endl;
    std::cout << matA;
    std::cout << "\nKopie matice A (mela by zustat nezmenena):" << std::endl;
    std::cout << matA_copy;


    std::cout << "\n--- Testovani dokonceno ---" << std::endl;

    return 0;
}
#endif // __TEST__