import math

class Vector2D:
    def __init__(self, x, y):
        """
        Konstruktor: Nastaví souřadnice x a y.
        """
        if not isinstance(x, (int, float)) or not isinstance(y, (int, float)):
            raise TypeError("Souřadnice musí být čísla (int nebo float).")

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
        """
        if not isinstance(other, Vector2D):
            raise TypeError("Sčítat lze pouze s jiným vektorem.")
        return Vector2D(self.x + other.x, self.y + other.y)

    def __sub__(self, other):
        """
        Operátor -: Odečte dva vektory.
        """
        if not isinstance(other, Vector2D):
            raise TypeError("Odečítat lze pouze jiný vektor.")
        return Vector2D(self.x - other.x, self.y - other.y)

    def __mul__(self, other):
        """
        Operátor *: Skalární násobení nebo skalární součin.
        """
        if isinstance(other, (int, float)):
            # Skalární násobení
            return Vector2D(self.x * other, self.y * other)

        elif isinstance(other, Vector2D):
            # Skalární součin
            return self.x * other.x + self.y * other.y

        else:
            raise TypeError("Násobení je podporováno pouze s číslem nebo jiným vektorem.")

    def __eq__(self, other):
        """
        Operátor ==: Porovná dva vektory.
        """
        if not isinstance(other, Vector2D):
            return False
        return self.x == other.x and self.y == other.y

    def __abs__(self):
        """
        Funkce abs(): Vrátí délku vektoru.
        """
        return math.sqrt(self.x**2 + self.y**2)


if __name__ == "__main__":
    v1 = Vector2D(3, 4)
    print(f"Můj vektor: {v1}")
    print(f"Délka: {abs(v1)}")
