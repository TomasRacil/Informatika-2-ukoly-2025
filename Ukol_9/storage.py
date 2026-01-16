import json
from typing import List
from models import Product

class Storage:
    def __init__(self, filename: str = "inventory.json"):
        self.filename = filename

    def save_products(self, products: List[Product]):
        """Uloží seznam produktů do JSON souboru."""
        # TODO: Převést produkty na dicty a uložit
        with open(self.filename, 'w', encoding='utf-8') as f:
            json.dump([product.to_dict() for product in products], f, ensure_ascii=False, indent=4)
        

    def load_products(self) -> List[Product]:
        """Načte produkty z JSON souboru."""
        # TODO: Načíst soubor, ošetřit FileNotFoundError/JSONDecodeError
        try:
            with open(self.filename, 'r', encoding='utf-8') as f:
                data = json.load(f)
                return [Product.from_dict(item) for item in data]
        except (FileNotFoundError, json.JSONDecodeError):
            pass
        # TODO: Vrátit seznam instancí Product
        return []
