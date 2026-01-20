class Product:
    """
    Reprezentuje produkt ve skladu.
    """
    def __init__(self, name: str, price: float, quantity: int):
        # TODO: Inicializace, využití properties pro validaci
        self.name = name
        self.price = price
        self.quantity = quantity

    @property
    def name(self) -> str:
        return self._name

    @name.setter
    def name(self, value: str):
        if not value or not isinstance(value, str) or value.strip() == "":
            raise ValueError("Název produktu nesmí být prázdný")
        self._name = value

    @property
    def price(self) -> float:
        return self._price

    @price.setter
    def price(self, value: float):
        # TODO: Validace, raise ValueError pokud < 0
        if value < 0:
            raise ValueError("Cena nesmí být záporná")
        self._price = value

    @property
    def quantity(self) -> int:
        return self._quantity

    @quantity.setter
    def quantity(self, value: int):
        # TODO: Validace
        if value < 0:
            raise ValueError("Množství nesmí být záporné")
        self._quantity = value

    def to_dict(self) -> dict:
        """Vrátí slovníkovou reprezentaci pro JSON."""
        return {
            "name": self._name,
            "price": self._price,
            "quantity": self._quantity
        }

    @staticmethod
    def from_dict(data: dict) -> 'Product':
        """Vytvoří instanci Product ze slovníku."""
        return Product(data['name'], data['price'], data['quantity'])

    def __str__(self) -> str:
        # TODO: Hezký výpis
        return f"{self._name} cena: {self._price} Kč, skladem: {self._quantity} ks"
