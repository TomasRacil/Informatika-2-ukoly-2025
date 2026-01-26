import json
from typing import List
from models import Product


class Storage:
    def __init__(self, filename: str = "inventory.json"):
        self.filename = filename

    def save_products(self, products: List[Product]):
        """Uloží seznam produktů do JSON souboru."""
        try:
            data = [p.to_dict() for p in products]
            with open(self.filename, 'w', encoding='utf-8') as f:
                json.dump(data, f, ensure_ascii=False, indent=2)
        except Exception as e:
            print(f"Chyba při ukládání do souboru: {e}")

    def load_products(self) -> List[Product]:
        """Načte produkty z JSON souboru."""
        try:
            with open(self.filename, 'r', encoding='utf-8') as f:
                data = json.load(f)
                return [Product.from_dict(item) for item in data]
        except FileNotFoundError:
            # Soubor neexistuje - vrátíme prázdný seznam
            return []
        except json.JSONDecodeError:
            # Soubor je poškozený - vrátíme prázdný seznam
            print(
                f"Varování: Soubor {self.filename} je poškozený, vracím prázdný seznam")
            return []
        except Exception as e:
            print(f"Chyba při načítání ze souboru: {e}")
            return []
