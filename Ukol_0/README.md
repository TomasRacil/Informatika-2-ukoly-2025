# Úkol 0: Hello World

Vítejte u prvního úkolu! Cílem tohoto úkolu je seznámit se s procesem odevzdávání a ověřit, že máte správně nastavené vývojové prostředí pro C++ i Python.

## Zadání

Vaším úkolem je upravit funkci `hello_world()` ve dvou souborech tak, aby vracela řetězec `"Hello world!"`.

### Soubory k úpravě:

1.  **Python:** `Ukol_0/python/hello_world.py`
2.  **C++:** `Ukol_0/cpp/hello_world.cpp`

V obou souborech je funkce `hello_world()`, která aktuálně vrací prázdný řetězec `""`. Změňte její implementaci tak, aby vracela přesně `Hello world!`.

## Jak fungují testy?

Abyste si mohli ověřit, že je vaše řešení správné, jsou v repozitáři připraveny automatické testy. Tyto soubory nemusíte měnit, ale je dobré vědět, jak fungují.

### Python (`test.py`)
Soubor `Ukol_0/python/test.py` používá standardní Python knihovnu `unittest`.
* Na začátku si naimportuje vaši funkci: `from hello_world import hello_world`.
* Poté definuje testovací případ, který kontroluje, zda se výstup vaší funkce shoduje s očekávaným řetězcem: `self.assertEqual(hello_world(), "Hello world!")`. Pokud se hodnoty neshodují, test selže.

### C++ (`test.cpp`)
Soubor `Ukol_0/cpp/test.cpp` používá framework Google Test.
* Nejprve vloží kód z vašeho souboru: `#include "hello_world.cpp"`.
* Následně definuje test `TEST(TestyFunkci, hello_world)`, který pomocí makra `EXPECT_EQ(hello_world(), "Hello world!")` porovná hodnotu vrácenou vaší funkcí s očekávaným řetězcem. Pokud se hodnoty liší, test selže.

## Testování

Po úpravě si můžete funkčnost ověřit spuštěním lokálních testů.

* **Spuštění Python testů:**
    ```shell
    cd Ukol_0/python && python3 -m unittest discover
    ```
* **Spuštění C++ testů:**
    ```shell
    cd Ukol_0/cpp && mkdir -p build && cd build && cmake .. && make && ./mytests
    ```

## Odevzdání

Jakmile budou vaše úpravy hotové a testy budou lokálně procházet, postupujte podle pokynů v hlavním `README.md` souboru repozitáře pro vytvoření commmitu a následného pull requestu.