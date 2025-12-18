# **Úkol 5: RPG Soubojový systém (Dědičnost a Polymorfismus)**

Vaším úkolem je naprogramovat logiku pro jednoduchý RPG soubojový systém. Máte připravenou kostru tříd a testy. Musíte doplnit implementaci metod v `.cpp` souborech tak, aby testy procházely a hra fungovala.

## **Cíle**

1. Pochopit, jak funguje dědičnost v C++ (`class Potomek : public Predek`).  
2. Implementovat polymorfismus pomocí `virtual` metod a `override`.  
3. Správně volat konstruktor předka.

## **Instrukce**

1. Prozkoumejte hlavičkové soubory (`.h`), abyste viděli, jaké atributy a metody třídy mají.  
2. Otevřete soubory `postava.cpp`, `valecnik.cpp` a `mag.cpp`.  
3. Doplňte chybějící kód na místech označených `// TODO`.

## **Pravidla tříd**

### **Postava (Základní třída)**

* **utok**: Vypíše informaci a zavolá `prijmiUtok` na cíli.  
* **prijmiUtok**: Odečte poškození od životů (životy nesmí klesnout pod 0).

### **Válečník (Dědí z Postava)**

* **utok**: Pokud má válečník pod 30 % maximálních životů, zuří (Berserk) a jeho síla se pro tento útok násobí 1.5x.  
* **prijmiUtok**: Válečník má brnění. Poškození se nejprve sníží o hodnotu brnění, až zbytek jde do životů.

### **Mág (Dědí z Postava)**

* **utok**:  
  * Pokud má dost many (>= 10), sešle Fireball (poškození = síla * 2) a odečte 10 many.  
  * Pokud nemá manu, udeří holí (poškození = síla * 0.5) a zregeneruje 5 many.

## **Struktura souborů**

* `main.cpp` - Hlavní smyčka hry (již předpřipravena, můžete upravit).  
* `postava.h / .cpp` - Hlavička a implementace základní třídy.  
* `valecnik.h / .cpp` - Hlavička a implementace Válečníka.  
* `mag.h / .cpp` - Hlavička a implementace Mága.  
* `test.cpp` - Testy pro ověření funkčnosti.

## **Testování**

* **Spuštění C++ testů:**  
  ```bash
  cd Ukol_5 && mkdir -p build && cd build && cmake .. && make && ./mytests
  ```

## **Odevzdání**

Postupujte podle pokynů v hlavním `README.md` souboru repozitáře.