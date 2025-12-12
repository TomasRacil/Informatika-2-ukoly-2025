# **Úkol 1: Analýza textového souboru**

Cílem tohoto úkolu je procvičit si práci se soubory, stringy a rozdělení problému na menší, samostatně řešitelné a testovatelné funkce v rámci jednoho souboru.

## **Zadání**

Vytvořte konzolovou aplikaci v C++, která analyzuje soubor `text_k_analyze.txt`. Vaším úkolem je implementovat sadu funkcí v souboru `main.cpp`, z nichž každá provádí specifickou část analýzy.

### **Funkce k implementaci v `main.cpp`:**

1. `getFileContent`: Načte celý obsah souboru do jednoho řetězce (string).  
2. `countCharacters`: Spočítá celkový počet znaků.  
3. `countLines`: Spočítá počet řádků.  
4. `countWords`: Spočítá počet slov (slovo je definováno jako posloupnost znaků oddělená bílými znaky).  
5. `countVowels`: Spočítá počet samohlásek (a, e, i, o, u, bez ohledu na velikost).

### **Soubory k úpravě:**

* **C++:** `Ukol_1/main.cpp`

V tomto souboru naleznete připravené funkce nad funkcí `main()`. Vaším úkolem je doplnit jejich těla tak, aby správně fungovaly. Část souboru s funkcí `main()` a výpisem výsledků neměňte.

## **Testování**

Pro ověření funkčnosti vašeho řešení spusťte lokální testy. Testy jsou navrženy tak, aby kontrolovaly každou funkci zvlášť.

* **Spuštění C++ testů:** 
```shell 
cd Ukol_1 && mkdir -p build && cd build && cmake .. && make && ./mytests
```

## **Odevzdání**

Postupujte podle pokynů v hlavním README.md souboru repozitáře pro vytvoření commmitu a následného pull requestu.