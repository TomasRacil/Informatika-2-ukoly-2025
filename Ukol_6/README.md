# **Úkol 6: Evidence prospěchu studentů (Python)**

Cílem tohoto úkolu je procvičit si kompletní základy jazyka Python na praktickém příkladu. Vytvoříte skript, který načte data o známkách studentů ze souboru, zpracuje je (vypočítá průměry, rozhodne o prospěchu) a výsledky uloží do nového souboru.

## **Zadání**

V souboru `main.py` implementujte sadu funkcí pro zpracování školních výsledků. Data jsou uložena v textovém souboru, kde každý řádek reprezentuje jednoho studenta.

### **Formát vstupního souboru**

Každý řádek obsahuje jméno studenta a seznam jeho známek oddělených čárkami.  
Příklad:

```text
Jan Novak,1,2,1,3  
Petr Svoboda,5,5,4  
Eva Dvorakova,1,1
```

### **Funkce k implementaci**

Veškerý kód pište do souboru `Ukol_6/main.py`. Musíte implementovat následující funkce:

1. **`nacti_data(soubor: str) -> list`**  
   * Otevře zadaný soubor a načte z něj data.  
   * Vrátí **seznam slovníků**. Každý slovník bude reprezentovat jednoho studenta a bude mít klíče:  
     * `"jmeno"` (`str`): Jméno studenta.  
     * `"znamky"` (`list[int]`): Seznam známek jako celých čísel.  
   * *Tip:* Nezapomeňte ošetřit konce řádků a převést známky z textu na čísla.  
2. **`spocitej_prumer(znamky: list) -> float`**  
   * Přijme seznam čísel (známek) a vrátí jejich aritmetický průměr.  
   * Pokud je seznam prázdný, vrátí `0.0`.  
3. **`prospel(prumer: float) -> bool`**  
   * Rozhodne, zda student prospěl.  
   * Vrátí `True`, pokud je průměr menší nebo roven `3.5`. Jinak vrátí `False`.  
4. **`zpracuj_vysledky(studenti: list) -> dict`**  
   * Přijme seznam studentů (ve formátu z funkce `nacti_data`).  
   * Pro každého studenta vypočítá průměr a určí, zda prospěl.  
   * Vrátí slovník, kde klíčem je jméno studenta a hodnotou je další slovník s klíči:  
     * `"prumer"` (`float`)  
     * `"prospel"` (`bool`)  
5. **`uloz_report(vystupni_soubor: str, vysledky: dict) -> None`**  
   * Zapíše výsledky do souboru ve formátu: `Jméno: Průměr (PROSPEL/NEPROSPEL)`.  
   * Příklad výstupu: `Jan Novak: 1.75 (PROSPEL)`

## **Testování**

Pro ověření funkčnosti vašeho řešení jsou připraveny automatické testy.

* **Spuštění testů:**  
  ```shell
  cd Ukol_6 && python3 -m unittest discover
  ```

## **Odevzdání**

Postupujte standardním způsobem: commit, push a vytvoření Pull Requestu.