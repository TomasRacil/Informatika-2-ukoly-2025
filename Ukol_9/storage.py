import json
from typing import List
from models import Product

class Storage:
    def __init__(self, filename: str = "inventory.json"):
        self.filename = filename

    def save_products(self, products: List[Product]):
        """Uloží seznam produktů do JSON souboru."""
        # TODO: Převést produkty na dicty a uložit
        with open(self.filename, "w") as f:
            json.dump([p.to_dict() for p in products], f, indent=4)

    def load_products(self) -> List[Product]:
        """Načte produkty z JSON souboru."""
        # TODO: Načíst soubor, ošetřit FileNotFoundError/JSONDecodeError
        # TODO: Vrátit seznam instancí Product
        try:
            with open(self.filename, "r") as f:
                data = json.load(f)
                return [Product.from_dict(item) for item in data]
        except (FileNotFoundError, json.JSONDecodeError):
            return []