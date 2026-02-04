import json
from typing import List
from models import Product

class Storage:
    def __init__(self, filename: str = "inventory.json"):
        self.filename = filename

    def save_products(self, products: List[Product]):
        """Uloží seznam produktů do JSON souboru."""
        # TODO: Převést produkty na dicty a uložit
        products_data = []
        for produkt in products:
            products_data.append(produkt.to_dict())

        with open(self.filename, "w", encoding="utf-8") as f:
            json.dump(products_data, f, ensure_ascii=False, indent=4)

    def load_products(self) -> List[Product]:
        """Načte produkty z JSON souboru."""
        # TODO: Načíst soubor, ošetřit FileNotFoundError/JSONDecodeError
        # TODO: Vrátit seznam instancí Product
        try:
            with open(self.filename, 'r', encoding='utf-8') as f:
                products_data = json.load(f)
                return [Product.from_dict(item) for item in products_data]
                    
        except FileNotFoundError:
            return []
                
        except json.JSONDecodeError:
            print(f"Varování: Soubor {self.filename} je poškozený nebo prázdný. Načítám prázdný seznam.")
            return []
