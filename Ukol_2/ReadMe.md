# **Úkol 2: Maticová kalkulačka**

Cílem tohoto úkolu je procvičit si práci s pointery a dynamickou alokací a dealokací paměti v C++. Vytvoříte sadu funkcí, které budou společně tvořit jednoduchou maticovou kalkulačku.

## **Zadání**

V souboru `main.cpp` implementujte funkce pro základní maticové operace. Matice budou reprezentovány jako dynamicky alokované 2D pole (tj. pomocí `int**`).

### **Funkce k implementaci v `main.cpp`:**

1.  `allocateMatrix(rows, cols)`: Dynamicky alokuje paměť pro 2D pole (matici) o daném počtu řádků (`rows`) a sloupců (`cols`) a vrátí na ni pointer (`int**`). Všechny prvky inicializujte na 0.
2.  `deallocateMatrix(matrix, rows)`: Uvolní veškerou paměť alokovanou pro danou matici. Je potřeba uvolnit paměť pro každý řádek a následně pro pole pointerů na řádky.
3.  `printMatrix(matrix, rows, cols)`: Vypíše matici do konzole ve formátu, kde jsou jednotlivé prvky v řádku odděleny mezerou a řádky jsou na nových řádcích.
4.  `addMatrices(matrixA, matrixB, rows, cols)`: Sečte dvě matice (`matrixA` + `matrixB`) stejných rozměrů. Funkce alokuje novou matici pro výsledek, provede součet a vrátí pointer na výslednou matici.
5.  `subtractMatrices(matrixA, matrixB, rows, cols)`: Odečte druhou matici od první (`matrixA` - `matrixB`). Funkce alokuje novou matici pro výsledek, provede rozdíl a vrátí pointer na výslednou matici.
6.  `multiplyMatrices(matrixA, matrixB, rowsA, colsA, colsB)`: Vynásobí dvě matice (`matrixA` * `matrixB`). Počet sloupců první matice (`colsA`) se musí rovnat počtu řádků druhé matice. Funkce alokuje novou matici pro výsledek (o rozměrech `rowsA` x `colsB`), provede násobení a vrátí pointer na výslednou matici.
7.  `transposeMatrix(matrix, rows, cols)`: Vytvoří transponovanou matici. Funkce alokuje novou matici (o rozměrech `cols` x `rows`), provede transpozici a vrátí pointer na výslednou matici.

### **Soubory k úpravě:**

* **C++:** `Ukol_2/main.cpp`

V tomto souboru naleznete připravené hlavičky funkcí. Vaším úkolem je doplnit jejich těla tak, aby správně fungovaly. Část souboru s funkcí `main()` můžete použít pro vlastní manuální testování.

## **Testování**

Pro ověření funkčnosti vašeho řešení spusťte lokální testy. Testy jsou navrženy tak, aby kontrolovaly každou funkci zvlášť.

* **Spuštění C++ testů:**
    ```shell
    cd Ukol_2 && mkdir -p build && cd build && cmake .. && make && ./mytests
    ```

## **Odevzdání**

Postupujte podle pokynů v hlavním `README.md` souboru repozitáře pro vytvoření commmitu a následného pull requestu.