import json
from typing import List
from models import Product

class Storage:
    def __init__(self, filename: str = "inventory.json"):
        self.filename = filename

    def save_products(self, products: List[Product]):
        """Uloží seznam produktů do JSON souboru."""
        # TODO: Převést produkty na dicty a uložit
        with open(self.filename, 'w') as file:
            json.dump([product.to_dict() for product in products], file, indent=4)
            for product in products:
                print(f"Uloženo {product.name} do {self.filename}")

    def load_products(self) -> List[Product]:
        """Načte produkty z JSON souboru."""
        # TODO: Načíst soubor, ošetřit FileNotFoundError/JSONDecodeError
        # TODO: Vrátit seznam instancí Product
        products: List[Product] = []
        try:
            with open(self.filename, 'r') as file:
                data = json.load(file)
                for item in data:
                    products.append(Product.from_dict(item))
        except:
            pass
        return products
