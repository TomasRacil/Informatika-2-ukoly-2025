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
        # TODO: Implementujte formátovaný výpis
        return f"Vector({self.x}, {self.y})"

    def __add__(self, other):
        """
        Operátor +: Sečte dva vektory.
        Vrací novou instanci Vector2D.
        """
        # TODO: Implementujte sčítání
        # return Vector2D(..., ...)
        return Vector2D(self.x + other.x, self.y + other.y)

    def __sub__(self, other):
        """
        Operátor -: Odečte druhý vektor od prvního.
        Vrací novou instanci Vector2D.
        """
        # TODO: Implementujte odčítání
        return Vector2D(self.x - other.x, self.y - other.y)

    def __mul__(self, other):
        """
        Operátor *: 
        - Pokud je 'other' číslo (int/float), provede skalární násobení a vrátí nový Vector2D.
        - Pokud je 'other' Vector2D, provede skalární součin a vrátí číslo.
        """
        if isinstance(other, (int, float)):
            # TODO: Implementujte násobení skalárem (číslem)
            # print("Je číslo")
            return Vector2D(self.x * other, self.y * other)
        elif isinstance(other, Vector2D):
            # TODO: Implementujte skalární součin (vektor * vektor)
            # print("Je vektor")
            return self.x * other.x + self.y * other.y
        else:
            raise TypeError("Násobení je podporováno pouze s číslem nebo jiným vektorem.")

    def __eq__(self, other):
        """
        Operátor ==: Porovná dva vektory na shodu.
        """
        # TODO: Implementujte porovnání
        if (self.x == other.x and self.y == other.y):
            return True
        return False

    def __abs__(self):
        """
        Funkce abs(): Vrátí délku (magnitudu) vektoru.
        """
        # TODO: Implementujte výpočet délky (Pythagorova věta)
        return math.sqrt(self.x ** 2 + self.y ** 2)

if __name__ == "__main__":
    # Zde si můžete zkoušet svůj kód ručně
    v1 = Vector2D(3, 4)
    v2 = Vector2D(5, 3)
    print(f"Můj vektor: {v1}")
    print(f"Délka: {abs(v1)}")
