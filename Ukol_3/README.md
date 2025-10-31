<<<<<<< HEAD
Úkol 3: Praktické programování - Fitness Kalkulačka
 
Vytvořte konzolovou aplikaci "Fitness Kalkulačka", která uživateli nabídne menu s různými výpočty a bude se opakovaně zobrazovat, dokud ji uživatel neukončí.
 
Zadání:
Aplikace bude mít následující funkce:
 
Výpočet BMI: Načte váhu a výšku, spočítá BMI a vypíše slovní hodnocení.
Výpočet BMR (Bazální metabolický výdej): Načte váhu, výšku, věk a pohlaví, a spočítá BMR podle Harris-Benedictova vzorce.
Konec: Ukončí program.
 
Prvně to zkuste samostatně pokud nebudete vědět jak, tak tady je návod k řešení (Algoritmus):
Doporučuji postupovat podle následujících kroků. Pro přehlednost je ideální rozdělit logiku do samostatných funkcí.
 
Vytvořte hlavní smyčku programu:
Použijte do-while cyklus, který poběží, dokud uživatel nezvolí možnost ukončení.
Uvnitř cyklu si vytvořte proměnnou pro volbu uživatele (např. int volba).
Zobrazte menu a načtěte vstup:
Uvnitř cyklu vypište uživateli menu:
1. Spocitat BMI
2. Spocitat BMR
3. Konec
Vase volba:
Načtěte číslo volby do připravené proměnné (std::cin >> volba;).
Zpracujte volbu uživatele:
Použijte příkaz switch (volba) pro zpracování zadané hodnoty.
Implementujte jednotlivé case bloky:
case 1: (BMI)
Vytvořte si proměnné pro váhu (double vaha) a výšku (double vyska).
Vypište výzvy a načtěte od uživatele obě hodnoty.
Spočítejte BMI: double bmi = vaha / (vyska * vyska);.
Vypište výsledek.
Použijte vnořenou if-else if-else strukturu pro slovní hodnocení na základě hodnoty bmi.
Nezapomeňte na break; na konci case.
case 2: (BMR)
Vytvořte si proměnné pro váhu, výšku, věk a pohlaví (char pohlavi).
Načtěte od uživatele všechny potřebné hodnoty.
Pomocí if (pohlavi == 'm') a else if (pohlavi == 'z') vyberte správný vzorec pro výpočet.
Spočítejte BMR a uložte jej do proměnné (double bmr).
Vypište výsledek.
Nezapomeňte na break;.
case 3: (Konec)
Vypište rozloučení (např. "Dekuji za pouziti a nashledanou.").
break;.
default:
Pro případ, že uživatel zadá neplatnou volbu, vypište chybovou hlášku (např. "Neplatna volba, zadejte prosim cislo 1-3.").
break;.
Podmínka do-while cyklu:
Cyklus se bude opakovat, dokud platí podmínka volba != 3.
=======
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
>>>>>>> upstream/master
