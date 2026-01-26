class Product:
    """
    Reprezentuje produkt ve skladu.
    """
    def __init__(self, name: str, price: float, quantity: int, category: str = "General"):
        # TODO: Inicializace, využití properties pro validaci
        self.name = name
        self.price = price
        self.quantity = quantity
        self.category = category

    @property
    def name(self) -> str:
        return self._name

    @name.setter
    def name(self, value: str):
        if not value or len(value.strip()) == 0:
            raise ValueError("Název produktu nemůže být prázdný.")
        self._name = value

    @property
    def price(self) -> float:
        return self._price

    @price.setter
    def price(self, value: float):
        if value < 0:
            raise ValueError("Cena nesmí být záporná.")
        # TODO: Validace, raise ValueError pokud < 0
        self._price = value

    @property
    def quantity(self) -> int:
        return self._quantity

    @quantity.setter
    def quantity(self, value: int):
        if value < 0:
            raise ValueError("Množství nesmí být záporné.")
        # TODO: Validace
        self._quantity = value

    def to_dict(self) -> dict:
        """Vrátí slovníkovou reprezentaci pro JSON."""
        return {
            "name": self._name,
            "price": self._price,
            "quantity": self._quantity,
            "category": self.category
        }

    @staticmethod
    def from_dict(data: dict) -> 'Product':
        """Vytvoří instanci Product ze slovníku."""
        return Product(data['name'], data['price'], data['quantity'], data.get('category', 'General'))

    def __str__(self) -> str:
        # TODO: Hezký výpis
        return f"[Produkt: {self._name} | Cena: {self._price} Kč | Množství: {self._quantity} Ks | Kategorie: {self.category}]"