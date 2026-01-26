# **Úkol 8: Analýza Logů (Regex, Generátory a Výjimky)**

V tomto úkolu si procvičíte práci se soubory, regulárními výrazy, zpracování výjimek a tvorbu vlastních generátorů. Vaším cílem je napsat skript, který efektivně zpracuje velký (simulovaný) logovací soubor, vyfiltruje chyby a extrahuje z něj užitečné informace.

## **Zadání**

Vytvořte skript `main.py`, který bude obsahovat následující funkcionalitu:

### **1. Generátor pro načítání souboru (`read_logs`)**

Napište generátorovou funkci `read_logs(file_path)`, která:
*   Otevře soubor pro čistění.
*   Bude načítat soubor **řádek po řádku** (aby se celý soubor nemusel načítat do paměti).
*   Každý řádek vrátí (yieldne) pro další zpracování.
*   Pokud soubor neexistuje, odchyťte výjimku `FileNotFoundError` a vypište chybovou hlášku.

### **2. Funkce pro zpracování řádku (`process_line`)**

Napište funkci `process_line(line)`, která pomocí **regulárních výrazů (module `re`)** zanalyzuje řádek logu.
*   Logy jsou ve formátu: `[DATUM ČAS] LEVEL: Zpráva - User: email`
*   Příklad: `[2024-05-20 14:30:01] ERROR: Connection failed - User: admin@example.com`
*   Funkce by měla extrahovat:
    *   **Datum a Čas**
    *   **Level** (INFO, WARN, ERROR)
    *   **Email uživatele**
*   Funkce vrátí slovník (dict) s těmito údaji. Pokud řádek neodpovídá formátu, vrátí `None`.

### **3. Hlavní logika (`analyze_logs`)**

Vytvořte funkci `analyze_logs(input_file, output_file)`, která:
*   Použije váš generátor `read_logs` k průchodu vstupním souborem.
*   Pro každý řádek zavolá `process_line`.
*   Vyfiltruje pouze záznamy, které jsou typu **ERROR**.
*   Zapíše tyto filtrované záznamy do nového souboru (`output_file`), každý na nový řádek (např. ve formátu CSV: `datum,email,zpráva` nebo jen prostý text).

## **Data**

Využijte přiložený soubor `sample_data.txt`, který obsahuje směs validních a poškozených záznamů.

## **Ukázkový kód (Skeleton)**

```python
import re

def read_logs(file_path):
    # TODO: Implementovat generátor
    pass

def process_line(line):
    # TODO: Regex pro parsování
    # Pattern např: r"\[(.*?)\] (\w+): (.*?) - User: ([\w\.-]+@[\w\.-]+)"
    pass

def analyze_logs(input_file, output_file):
    # TODO: Spojit vše dohromady
    pass

if __name__ == "__main__":
    analyze_logs("sample_data.txt", "errors.csv")
```

## **Testování**

Spusťte testy pomocí:
```bash
python3 -m unittest test_ukol.py
```
