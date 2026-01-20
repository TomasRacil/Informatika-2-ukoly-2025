# **Úkol 9: Systém Správy Skladu (Capstone Project)**

Toto je závěrečný úkol, který kombinuje většinu probraných témat: OOP, Dědičnost, Práce se soubory (JSON), Argumenty příkazové řádky (CLI), Dekorátory a Logování.

Vaším úkolem je vytvořit robustní konzolovou aplikaci pro správu skladu produktů.

## **Struktura projektu**

Projekt je rozdělen do několika modulů pro lepší přehlednost:

*   `models.py` - Obsahuje definice tříd (Product, Electronics, atd.).
*   `storage.py` - Stará se o ukládání a načítání dat (Persistence).
*   `main.py` - Hlavní spouštěcí soubor, CLI rozhraní a logika aplikace.

## **Zadání**

### **1. Datové modely (`models.py`)**

Implementujte třídu `Product` a případně dědící třídy (např. `PerishableProduct`, `Electronics`).

*   **Vlastnosti**: `name`, `price`, `quantity`, `category`.
*   Použijte **Properties** (`@property`) pro validaci: 
    *   Cena nesmí být záporná.
    *   Množství nesmí být záporné.
*   Implementujte magickou metodu `__str__` pro hezký výpis.

### **2. Ukládání dat (`storage.py`)**

Implementujte třídu `Storage` (nebo funkce), která:
*   Umožní uložit seznam produktů do souboru JSON.
*   Umožní načíst data ze souboru JSON.
*   Ošetřete situace, kdy soubor neexistuje nebo je poškozený (`json.JSONDecodeError`).

### **3. Logování a Dekorátory (`main.py` nebo utils)**

*   Vytvořte vlastní dekorátor `@log_action`, který zaznamená každou operaci (přidání, odebrání zboží) do souboru `history.log` spolu s časovým razítkem.
*   Aplikujte tento dekorátor na metody, které mění stav skladu.

### **4. CLI Aplikace (`main.py`)**

Použijte knihovnu `argparse` pro vytvoření rozhraní příkazové řádky. Aplikace by měla umět:

*   **add**: Přidat nový produkt. 
    *   `python main.py add --name "Laptop" --price 20000 --qty 5`
*   **list**: Vypsat všechny produkty.
    *   `python main.py list`
*   **search**: Vyhledat produkty podle jména (i částečná shoda).
    *   `python main.py search --query "Lap"`
*   **total**: Vypsat celkovou hodnotu skladu (suma `price * quantity`).

## **Požadavky na hodnocení**

*   Kód musí být rozdělen do souborů dle zadání.
*   Musí být použity **Type Hinty**.
*   Musí fungovat validace dat (nelze zadat zápornou cenu).
*   Musí fungovat logování do souboru.

## **Testování**

Spusťte připravené testy:
```bash
python3 -m unittest test_ukol.py
```
