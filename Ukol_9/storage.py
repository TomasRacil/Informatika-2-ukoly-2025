import json
from typing import List
from models import Product

class Storage:
    def __init__(self, filename: str = "inventory.json"):
        self.filename = filename

    def save_products(self, products: List[Product]):
        """Uloží seznam produktů do JSON souboru."""
        # TODO: Převést produkty na dicty a uložit
        products_to_dicts = [product.to_dict() for product in products]

        with open(self.filename, mode="w", encoding="utf-8") as f:
            json.dump(products_to_dicts, f)

            f.close()
        pass

    def load_products(self) -> List[Product]:
        """Načte produkty z JSON souboru."""
        # TODO: Načíst soubor, ošetřit FileNotFoundError/JSONDecodeError
        # TODO: Vrátit seznam instancí Product
        products = []

        try:
            with open(self.filename, mode="r", encoding="utf-8") as f:
                products = [Product(*product.values()) for product in json.load(f)]
                
                f.close()
                return products
        except FileNotFoundError as e:
            print("ERROR OCCUCRED",e)
            open(self.filename, "a").close()
            return []
        except json.JSONDecodeError as e:
            print("ERROR OCCUCRED",e)
            return []
