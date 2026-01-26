import json
from typing import List
from models import Product

class Storage:
    def __init__(self, filename: str = "inventory.json"):
        self.filename = filename

    def save_products(self, products: List[Product]):
        """Uloží seznam produktů do JSON souboru."""
        data = [p.to_dict() for p in products]

        with open(self.filename, "w", encoding="utf-8") as f:
            json.dump(data, f, ensure_ascii=False, indent=4)

    def load_products(self) -> List[Product]:
        """Načte produkty z JSON souboru."""
        try:
            with open(self.filename, "r", encoding="utf-8") as f:
                data = json.load(f)

            products = []
            for item in data:
                products.append(Product.from_dict(item))

            return products

        except FileNotFoundError:
            return []

        except json.JSONDecodeError:
            return []
