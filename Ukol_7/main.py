import math

class Vector2D:
    def __init__(self, x, y):
        """
        Konstruktor: Nastaví souřadnice x a y.
        """
        self.x = x
        self.y = y

    def __str__(self):
        """
        Vrací textovou reprezentaci vektoru ve formátu: Vector(x, y)
        """
        # Implementace formátovaného výpisu pomocí f-stringu
        return f"Vector({self.x}, {self.y})"

    def __add__(self, other):
        """
        Operátor +: Sečte dva vektory.
        Vrací novou instanci Vector2D.
        """
        # Implementace sčítání: (x1+x2, y1+y2)
        return Vector2D(self.x + other.x, self.y + other.y)

    def __sub__(self, other):
        """
        Operátor -: Odečte druhý vektor od prvního.
        Vrací novou instanci Vector2D.
        """
        # Implementace odčítání: (x1-x2, y1-y2)
        return Vector2D(self.x - other.x, self.y - other.y)

    def __mul__(self, other):
        """
        Operátor *: 
        - Pokud je 'other' číslo (int/float), provede skalární násobení a vrátí nový Vector2D.
        - Pokud je 'other' Vector2D, provede skalární součin a vrátí číslo.
        """
        if isinstance(other, (int, float)):
            # Implementace násobení skalárem: (x*k, y*k)
            return Vector2D(self.x * other, self.y * other)
        elif isinstance(other, Vector2D):
            # Implementace skalárního součinu: x1*x2 + y1*y2
            return self.x * other.x + self.y * other.y
        else:
            raise TypeError("Násobení je podporováno pouze s číslem nebo jiným vektorem.")

    def __eq__(self, other):
        """
        Operátor ==: Porovná dva vektory na shodu.
        """
        # Implementace porovnání: musí být stejný typ a stejné souřadnice
        if isinstance(other, Vector2D):
            return self.x == other.x and self.y == other.y
        return False

    def __abs__(self):
        """
        Funkce abs(): Vrátí délku (magnitudu) vektoru.
        """
        # Implementace výpočtu délky (Pythagorova věta): odmocnina z (x^2 + y^2)
        return math.sqrt(self.x**2 + self.y**2)