# **Úkol 3: Maticová kalkulačka (třídy)**

Cílem tohoto úkolu je procvičit si základy objektově orientovaného programování v C++, zejména definici tříd, správu paměti pomocí konstruktorů a destruktorů a implementaci metod.

## **Zadání**

V tomto úkolu přepracujete maticovou kalkulačku z Úkolu 2. Místo sady volných funkcí a `int**` ukazatelů vytvoříte třídu `Matrix`, která zapouzdří data (rozměry a samotné prvky matice) a bude poskytovat metody pro maticové operace.

Veškerá správa paměti (alokace a dealokace) bude nyní probíhat uvnitř třídy, primárně v konstruktorech a destruktoru.

### **Soubory k úpravě:**

* **Ukol_3/main.cpp**

V souboru `main.cpp` naleznete definici třídy `Matrix`. Vaším úkolem je doplnit implementaci všech jejích metod.

### **Metody k implementaci v `main.cpp`:**

1. `Matrix(int rows, int cols)` (Konstruktor): Inicializuje matici daných rozměrů. Alokuje paměť a nastaví všechny prvky na 0.  
2. `~Matrix()` (Destruktor): Uvolní veškerou paměť alokovanou pro data matice.  
3. `Matrix(const Matrix& other)` (Kopírovací konstruktor): Vytvoří *hlubokou kopii* (deep copy) existující matice.  
4. `getRows()`, `getCols()`: Vrátí rozměry matice.  
5. `getValue(int row, int col)`: Vrátí hodnotu na dané pozici. Pokud jsou indexy mimo rozsah, vyvolá výjimku `std::out_of_range`.
6. `setValue(int row, int col, int value)`: Nastaví hodnotu na dané pozici. Pokud jsou indexy mimo rozsah, vyvolá výjimku `std::out_of_range`.
7. `print()`: Vytiskne matici do konzole.  
8. `add(const Matrix& other)`: Sečte matici s jinou maticí. Vrátí *nový* objekt `Matrix` s výsledkem.  
9. `subtract(const Matrix& other)`: Odečte jinou matici. Vrátí *nový* objekt `Matrix` s výsledkem.  
10. `multiply(const Matrix& other)`: Vynásobí matici s jinou maticí. Vrátí *nový* objekt `Matrix` s výsledkem.  
11. `transpose()`: Vrátí *nový* objekt `Matrix`, který je transpozicí původní matice.

**Důležité:** 
    * Pro vyhození výjimky budete potřebovat `#include <stdexcept>` (již je v souboru) a použít příkaz `throw std::out_of_range("Error message")`;.
    * Všechny operace (`add`, `subtract`, `multiply`, `transpose`) musí vracet nový objekt `Matrix` a nesmí měnit stav původních objektů. Pokud operace není možná (např. špatné rozměry), vraťte prázdnou matici `Matrix(0, 0)`.

## **Testování**

Pro ověření funkčnosti vašeho řešení spusťte lokální testy. Testy ověřují správnou alokaci, dealokaci (implicitně přes kopírovací konstruktor a testy paměti), přístup k prvkům i všechny matematické operace.

* **Spuštění C++ testů:**  
    ```shell
    cd Ukol_3 && mkdir -p build && cd build && cmake .. && make && ./mytests
    ```

## **Odevzdání**

Postupujte podle pokynů v hlavním `README.md` souboru repozitáře pro vytvoření commmitu a následného pull requestu.