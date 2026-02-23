import json
from models import Product, Electronics, PerishableProduct

class Storage:
    def __init__(self, filename="products.json"):
        self.filename = filename

    def load_products(self):
        try:
            with open(self.filename, 'r', encoding='utf-8') as file:
                data = json.load(file)
                # Tady využijeme tvou statickou metodu from_dict!
                return [Product.from_dict(p) for p in data]
        except (FileNotFoundError, json.JSONDecodeError):
            return []

    def save_products(self, products):
        # Tady využijeme tvou metodu to_dict()
        data = [p.to_dict() for p in products]
        with open(self.filename, 'w', encoding='utf-8') as file:
            json.dump(data, file, indent=4, ensure_ascii=False)