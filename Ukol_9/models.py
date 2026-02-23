class Product:
    """
    Reprezentuje základní produkt ve skladu.
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
        if not value or len(value.strip()) == 0:
            raise ValueError("Název produktu nesmí být prázdný.")
        self._name = value.strip()

    @property
    def price(self) -> float:
        return self._price

    @price.setter
    def price(self, value: float):
        if value < 0:
            raise ValueError("Cena nesmí být záporná.")
        self._price = float(value)

    @property
    def quantity(self) -> int:
        return self._quantity

    @quantity.setter
    def quantity(self, value: int):
        if value < 0:
            raise ValueError("Množství nesmí být záporné.")
        self._quantity = int(value)

    def to_dict(self) -> dict:
        """Vrátí slovníkovou reprezentaci pro JSON."""
        return {
            "name": self.name,
            "price": self.price,
            "quantity": self.quantity
        }

    @staticmethod
    def from_dict(data: dict) -> 'Product':
        """Vytvoří instanci Product nebo podtřídy ze slovníku."""
        # Pokud JSON obsahuje brand, jde o elektroniku
        if 'brand' in data:
            return Electronics(data['name'], data['price'], data['quantity'], data['brand'])
        # Pokud obsahuje expiration_date, jde o potravinu
        elif 'expiration_date' in data:
            return PerishableProduct(data['name'], data['price'], data['quantity'], data['expiration_date'])
        return Product(data['name'], data['price'], data['quantity'])

    def __str__(self) -> str:
        return f"{self.name:<20} | Cena: {self.price:>8.2f} Kč | Skladem: {self.quantity:>4} ks"


class Electronics(Product):
    def __init__(self, name, price, quantity, brand):
        super().__init__(name, price, quantity)
        self.brand = brand

    @property
    def brand(self):
        return self._brand
    
    @brand.setter
    def brand(self, value):
        if not value:
            raise ValueError("Elektronika musí mít uvedenou značku.")
        self._brand = value

    def to_dict(self):
        # Operátor | slouží ke sloučení slovníků (Python 3.9+)
        return super().to_dict() | {"brand": self.brand}
    
    def __str__(self):
        return super().__str__() + f" | Značka: {self.brand}"


class PerishableProduct(Product):
    def __init__(self, name, price, quantity, expiration_date):
        super().__init__(name, price, quantity)
        self.expiration_date = expiration_date

    @property
    def expiration_date(self):
        return self._expiration_date
    
    @expiration_date.setter
    def expiration_date(self, value):
        # Tady by se dala přidat kontrola na datetime objekt, 
        # pro teď kontrolujeme nenulovost
        if not value:
            raise ValueError("Produkt podléhající zkáze musí mít datum spotřeby.")
        self._expiration_date = value

    def to_dict(self):
        return super().to_dict() | {"expiration_date": self.expiration_date}
    
    def __str__(self):
        return super().__str__() + f" | Spotřebujte do: {self.expiration_date}"