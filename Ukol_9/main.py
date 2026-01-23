import argparse
import sys
from models import Product
from storage import Storage

# TODO: Implementovat dekorátor @log_action (zapsat do history.log)
def log_action(func):
    def wrapper(*args, **kwargs):
        # ... logika logování ...
        output = func(*args, **kwargs)
        with open("history.log", "a") as f:
            timestamp = __import__('datetime').datetime.now().strftime("%d-%m-%Y %H:%M:%S")
            f.write(f"[{timestamp}] {func.__name__}\n")
        return output
    return wrapper

class InventoryManager:
    def __init__(self, storage: Storage):
        self.storage = storage
        self.products = self.storage.load_products()

    @log_action
    def add_product(self, name: str, price: float, quantity: int):
        # TODO: Vytvořit produkt, přidat do self.products, uložit
        product = Product(name, price, quantity)
        self.products.append(product)
        self.storage.save_products(self.products)
        print(f"Produkt {name} přidán.")

    def list_products(self):
        # TODO: Vypsat všechny produkty
        for product in self.products:
            print(product)
        else:
            print("Žádné produkty na skladě.")

    def search_products(self, query: str):
        # TODO: Vyhledat produkty obsahující query v názvu
        results = [p for p in self.products if query.lower() in p._name.lower()]
        for product in results:
            print(product)
        if not results:
            print("Nebyly nalezeny žádné produkty.")
    
    def total_value(self):
        # TODO: Spočítat celkovou hodnotu
        if not self.products:
            print("Žádné produkty na skladě.")
            return
        else: 
            total = sum(p.price * p.quantity for p in self.products)
            print(f"Celková hodnota skladu: {total}")

def main():
    parser = argparse.ArgumentParser(description="Systém správy skladu")
    subparsers = parser.add_subparsers(dest="command")

    # Příkaz 'add'
    add_parser = subparsers.add_parser("add", help="Přidat produkt")
    add_parser.add_argument("--name", required=True, help="Název produktu")
    add_parser.add_argument("--price", required=True, type=float, help="Cena")
    add_parser.add_argument("--qty", required=True, type=int, help="Množství")

    # Příkaz 'list'
    subparsers.add_parser("list", help="Vypsat produkty")
    
    # Příkaz 'search'
    search_parser = subparsers.add_parser("search", help="Hledat produkt")
    search_parser.add_argument("--query", required=True, help="Hledaný text")

    args = parser.parse_args()
    
    storage = Storage()
    manager = InventoryManager(storage)

    if args.command == "add":
        manager.add_product(args.name, args.price, args.qty)
    elif args.command == "list":
        manager.list_products()
    elif args.command == "search":
        manager.search_products(args.query)
    # TODO: Další příkazy
    else:
        parser.print_help()

if __name__ == "__main__":
    main()
