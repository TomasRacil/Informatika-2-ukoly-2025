# **Úkol 4: Rozdělení třídy a přetížení operátorů**

Cílem tohoto úkolu je vzít hotovou třídu `Matrix` z Úkolu 3, provést refaktoring (rozdělit kód do `.h` a `.cpp` souborů) a nahradit klíčové metody přetíženými operátory pro intuitivnější použití.

## **Zadání**

V tomto úkolu budete pracovat se svým kódem z **Úkolu 3**.

### **Krok 1: Rozdělení kódu (Refaktoring)**

Vezměte svůj funkční soubor `main.cpp` z Úkolu 3 a rozdělte `Matrix` třídu do dvou nových souborů:

1. **`Ukol_4/matrix.h` (Hlavičkový soubor)**  
   * Zkopírujte sem pouze definici (deklaraci) vaší třídy `Matrix`.  
   * Na úplný začátek souboru přidejte direktivu `#pragma once`. Tím zajistíte, že kompilátor vloží tento soubor pouze jednou, i kdyby byl includován vícekrát. 
   * Vložte sem `#include` direktivy nutné pro *deklaraci* (např. `<stdexcept>`, `<ostream>`).  
   * Z deklarace třídy odeberte metody add(const Matrix&), multiply(const Matrix&) a print(). Budou plně nahrazeny.
2. **`Ukol_4/matrix.cpp` (Implementační soubor)**  
   * Na začátek souboru vložte `#include "matrix.h"`.  
   * Zkopírujte sem *těla (implementace)* všech metod z vaší třídy `Matrix`. KROMĚ metod `add`, `multiply` a `print`.
   * U každé metody musíte uvést název třídy (např. `Matrix::Matrix(int rows, int cols) { ... }`).  
   * Přesuňte sem `#include` direktivy nutné pouze pro *implementaci* (např. `<iostream>`, `<iomanip>`).

### **Krok 2: Přidání operátorů**

Nyní implementujte operátory, které nahradí odebrané metody. Logiku pro ně vezměte ze svých starých metod z Úkolu 3.

1. **Operátor sčítání (`+`)**  
   * Přidejte deklaraci `Matrix operator+(const Matrix& other) const;` do `matrix.h`.  
   * Přidejte implementaci `Matrix Matrix::operator+(...)` do `matrix.cpp`. Logiku můžete použí z vaší staré metody `add()`.  
2. **Operátor násobení (`*`)**  
   * Přidejte deklaraci `Matrix operator*(const Matrix& other) const;` do `matrix.h`.  
   * Přidejte implementaci `Matrix Matrix::operator*(...)` do `matrix.cpp`. Logiku můžete použí z vaší staré metody `multiply()`.  
3. **Operátor výstupu (`<<`)**  
   * Přidejte deklaraci `friend std::ostream& operator<<(std::ostream& os, const Matrix& mat);` do `matrix.h`.  
   * Přidejte implementaci `std::ostream& operator<<(...)` do `matrix.cpp`. Můžete zkopírovat logiku z vaší metody `print()` (jen nahraďte `std::cout` za `os`).

### **Soubory k úpravě:**

* **`Ukol_4/matrix.h`** (Sem přijde definice třídy `Matrix` + deklarace operátorů)  
* **`Ukol_4/matrix.cpp`** (Sem přijdou implementace metod `Matrix::...` + implementace operátorů)

Soubory `main.cpp`, `test.cpp` a `CMakeLists.txt` jsou již připraveny. `main.cpp` a `test.cpp` již používají nové operátory – váš kód se nepřeloží a testy neprojdou, dokud vše správně nedoplníte.

Prostudujte si `CMakeLists.txt`, abyste viděli, jak se nyní kompilují a linkují soubory `matrix.cpp`, `main.cpp` a `test.cpp` dohromady.

## **Testování**

* **Spuštění C++ testů:**  
  ```bash
  cd Ukol_4 && mkdir -p build && cd build && cmake .. && make && ./mytests
  ```

## **Odevzdání**

Postupujte podle pokynů v hlavním `README.md` souboru repozitáře.