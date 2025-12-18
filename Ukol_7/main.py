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
        return f"Vector({self.x}, {self.y})"

    def __add__(self, other):
        """
        Operátor +: Sečte dva vektory.
        Vrací novou instanci Vector2D.
        """
        if not isinstance(other, Vector2D):
            raise TypeError("Sčítání je podporováno pouze mezi vektory.")
        return Vector2D(self.x + other.x, self.y + other.y)

    def __sub__(self, other):
        """
        Operátor -: Odečte druhý vektor od prvního.
        Vrací novou instanci Vector2D.
        """
        if not isinstance(other, Vector2D):
            raise TypeError("Odčítání je podporováno pouze mezi vektory.")
        return Vector2D(self.x - other.x, self.y - other.y)

    def __mul__(self, other):
        """
        Operátor *: 
        - Pokud je 'other' číslo (int/float), provede skalární násobení a vrátí nový Vector2D.
        - Pokud je 'other' Vector2D, provede skalární součin a vrátí číslo.
        """
        if isinstance(other, (int, float)):
            return Vector2D(self.x * other, self.y * other)
        elif isinstance(other, Vector2D):
            return self.x * other.x + self.y * other.y
        else:
            raise TypeError(
                "Násobení je podporováno pouze s číslem nebo jiným vektorem.")

    def __eq__(self, other):
        """
        Operátor ==: Porovná dva vektory na shodu.
        """
        if not isinstance(other, Vector2D):
            return False
        return self.x == other.x and self.y == other.y

    def __abs__(self):
        """
        Funkce abs(): Vrátí délku (magnitudu) vektoru.
        """
        return math.sqrt(self.x * self.x + self.y * self.y)


if __name__ == "__main__":
    v1 = Vector2D(3, 4)
    print(f"Můj vektor: {v1}")
    print(f"Délka: {abs(v1)}")
