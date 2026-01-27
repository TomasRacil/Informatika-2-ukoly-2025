import json
from typing import List
from models import Product

class Storage:
    def __init__(self, filename: str = "inventory.json"):
        self.filename = filename

    def save_products(self, products: List[Product]):
        """Uloží seznam produktů do JSON souboru."""
        data = [p.to_dict() for p in products]
        try:
            with open(self.filename, 'w', encoding='utf-8') as f:
                json.dump(data, f, indent=4, ensure_ascii=False)
        except IOError as e:
            print(f"Chyba při ukládání souboru: {e}")

    def load_products(self) -> List[Product]:
        """Načte produkty z JSON souboru."""
        try:
            with open(self.filename, 'r', encoding='utf-8') as f:
                data = json.load(f)
                return [Product.from_dict(item) for item in data]
        except FileNotFoundError:
            # Pokud soubor neexistuje, vrátíme prázdný seznam (začínáme s prázdným skladem)
            return []
        except json.JSONDecodeError:
            print(f"Varování: Soubor {self.filename} je poškozený. Načítám prázdný sklad.")
            return []
