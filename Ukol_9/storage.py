import json
from typing import List
from models import Product

class Storage:
    def __init__(self, filename: str = "inventory.json"):
        self.filename = filename

    def save_products(self, products: List[Product]):
        """Uloží seznam produktů do JSON souboru."""
        data = [product.to_dict() for product in products]

        with open(self.filename, "w", encoding="utf-8") as f:
            json.dump(data, f, ensure_ascii=False, indent=4)


    def load_products(self) -> List[Product]:
        """Načte produkty z JSON souboru."""
        try:
            with open(self.filename, "r", encoding="utf-8") as f:
                data = json.load(f)

        except FileNotFoundError:
            return []

        except json.JSONDecodeError:
            print("Varování: Soubor s daty je poškozený. Načítám prázdný sklad.")
            return []

        products = []
        for item in data:
            try:
                products.append(Product.from_dict(item))
            except (KeyError, ValueError, TypeError) as e:
                print(f"Varování: Neplatný záznam přeskočen: {item} ({e})")

        return products
