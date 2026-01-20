from typing import Optional

class Product:
    """
    Reprezentuje produkt ve skladu.
    """
    def __init__(self, name: str, price: float, quantity: int, category: str = "General"):
        # Změna: Používáme setter (self.name = ...) místo přímého zápisu do _name,
        # aby se provedla validace hned při startu.
        self.name = name       
        self.category = category
        self.price = price
        self.quantity = quantity

    @property
    def name(self) -> str:
        return self._name

    @name.setter
    def name(self, value: str):
        # Validace: Název nesmí být prázdný ani obsahovat jen mezery
        if not value or not value.strip():
            raise ValueError("Název produktu nesmí být prázdný.")
        self._name = value

    @property
    def price(self) -> float:
        return self._price

    @price.setter
    def price(self, value: float):
        if value < 0:
            raise ValueError(f"Cena nesmí být záporná. Zadáno: {value}")
        self._price = value

    @property
    def quantity(self) -> int:
        return self._quantity

    @quantity.setter
    def quantity(self, value: int):
        if value < 0:
            raise ValueError(f"Množství nesmí být záporné. Zadáno: {value}")
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
        return Product(
            name=data['name'], 
            price=data['price'], 
            quantity=data['quantity'],
            category=data.get('category', "General")
        )

    def __str__(self) -> str:
        return f"[Produkt] {self._name} (Kat: {self.category}) | Cena: {self._price} Kč | Skladem: {self._quantity} ks"