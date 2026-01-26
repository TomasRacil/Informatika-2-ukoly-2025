class Product:
    """
    Reprezentuje produkt ve skladu.
    """

    def __init__(self, name: str, price: float, quantity: int):
        self.name = name
        self.price = price
        self.quantity = quantity

    @property
    def name(self) -> str:
        return self._name

    @name.setter
    def name(self, value: str):
        if not isinstance(value, str):
            raise TypeError("Název produktu musí být řetězec.")
        if not value.strip():
            raise ValueError("Název produktu nesmí být prázdný.")
        self._name = value.strip()

    @property
    def price(self) -> float:
        return self._price

    @price.setter
    def price(self, value: float):
        if value < 0:
            raise ValueError("Cena produktu nesmí být záporná.")
        self._price = float(value)

    @property
    def quantity(self) -> int:
        return self._quantity

    @quantity.setter
    def quantity(self, value: int):
        if not isinstance(value, int):
            raise TypeError("Množství musí být celé číslo.")
        if value < 0:
            raise ValueError("Množství produktu nesmí být záporné.")
        self._quantity = value

    def to_dict(self) -> dict:
        """Vrátí slovníkovou reprezentaci pro JSON."""
        return {
            "name": self._name,
            "price": self._price,
            "quantity": self._quantity
        }

    @staticmethod
    def from_dict(data: dict) -> "Product":
        """Vytvoří instanci Product ze slovníku."""
        return Product(data["name"], data["price"], data["quantity"])

    def __str__(self) -> str:
        return f"{self._name} | Cena: {self._price:.2f} | Množství: {self._quantity}"