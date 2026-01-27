# **Úkol 7: Vektorová aritmetika (Python OOP a Magické metody)**

Cílem tohoto úkolu je naučit se pracovat s třídami v jazyce Python a pochopit koncept tzv. **magických metod** (magic methods / dunder methods). Tyto metody umožňují definovat chování objektů pro vestavěné funkce a operátory (např. `+`, `-`, `*`, `str()`, `len()`).

## **Zadání**

V souboru main.py implementujte třídu `Vector2D`, která bude reprezentovat dvourozměrný vektor. Vaším úkolem je doplnit implementaci magických metod tak, aby s instancemi této třídy šlo pracovat intuitivně jako s čísly.

### **Metody k implementaci:**

1. **`__init__(self, x, y)`** (Konstruktor)  
   * Inicializuje vektor se souřadnicemi `x` a `y`.  
   * Pokud nejsou `x` nebo `y` čísla (`int` nebo `float`), měl by vyvolat `TypeError` (volitelné, ale doporučené).  
2. **`__str__(self)`** (Reprezentace pro výpis)  
   * Vrací řetězec ve formátu `Vector(x, y)`.  
   * Příklad: Pro x=1, y=2 vrátí `"Vector(1, 2)"`.  
3. **`__add__(self, other)`** (Operátor `+`)  
   * Sečte dva vektory (sečte odpovídající souřadnice).  
   * Vrací **novou instanci** `Vector2D`.  
4. **`__sub__(self, other)`** (Operátor `-`)  
   * Odečte druhý vektor od prvního.  
   * Vrací **novou instanci** `Vector2D`.  
5. **`__mul__(self, other)`** (Operátor `*`)  
   * Pokud je other číslo (`int`/`float`), provede **skalární násobení** (vynásobí obě souřadnice tímto číslem).  
   * Pokud je other instance `Vector2D`, provede **skalární součin** (`x1*x2 + y1*y2`) a vrátí číslo.  
   * Vrací buď novou instanci `Vector2D` (při násobení číslem), nebo `float`/int` (při násobení vektorem).  
6. **`__eq__(self, other)`** (Operátor `==`)  
   * Porovná dva vektory. Vrátí `True`, pokud jsou jejich souřadnice shodné, jinak `False`.  
7. **`__abs__(self)`** (Funkce `abs()`)  
   * Vrátí délku vektoru (magnitudu).  
   * Vzorec: `sqrt(x^2 + y^2)`.

### **Soubory k úpravě:**

* **Python:** `Ukol_7/main.py`

V tomto souboru naleznete kostru třídy. Doplňte kód na místa označená `# TODO`.

## **Příklad použití (pro představu)**

```python
v1 = Vector2D(1, 2)  
v2 = Vector2D(3, 4)

print(v1)        # Vypíše: Vector(1, 2)  
v3 = v1 + v2     # v3 bude Vector(4, 6)  
delka = abs(v3)  # Vypočítá délku vektoru v3  
soucin = v1 * 5  # soucin bude Vector(5, 10)
```

## **Testování**

Pro ověření funkčnosti spusťte připravené testy:

* Spuštění testů: 

```shell  
  cd Ukol_7 && python3 -m unittest discover
```

## **Odevzdání**

Postupujte standardním způsobem: commit, push a vytvoření Pull Requestu.