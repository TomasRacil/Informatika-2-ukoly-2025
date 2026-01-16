import json
from typing import List
from models import Product

class Storage:
    def __init__(self, filename: str = "inventory.json"):
        self.filename = filename

    def save_products(self, products: List[Product]):
        """Uloží seznam produktů do JSON souboru."""
        # TODO: Převést produkty na dicty a uložit
        slovniky = []
        for p in products:
            produkt_slovnik = p.to_dict()
            slovniky.append(produkt_slovnik)

        with open(self.filename, 'w', encoding='utf-8') as f:
            json.dump(slovniky, f, indent=4, ensure_ascii=False)

    def load_products(self) -> List[Product]:
        """Načte produkty z JSON souboru."""
        # TODO: Načíst soubor, ošetřit FileNotFoundError/JSONDecodeError
        try:
            with open(self.filename, 'r', encoding='utf-8') as f:
                data = json.load(f)

            seznam_produktu = []
            for item in data:
                produkt = Product.from_dict(item)
                seznam_produktu.append(produkt)

            return seznam_produktu
        except FileNotFoundError:
            print("Soubor nenalezen")
            return []
        except json.JSONDecodeError:
            print("Soubor je poškozený")
            return []
        # TODO: Vrátit seznam instancí Product
        return []
