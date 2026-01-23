import argparse
import sys
from models import Product
from storage import Storage

# TODO: Implementovat dekorátor @log_action (zapsat do history.log)
def log_action(func):
    def wrapper(*args, **kwargs):
        # ... logika logování ...
        result = func(*args,**kwargs)
        with open("history.log", "a", encoding = "utf-8") as log_file:
            log_file.write(f"Action:{func.__name__}, Args:{args[1:]}, Kwargs:{kwargs}\n")
        return result
    return wrapper

class InventoryManager:
    def __init__(self, storage: Storage):
        self.storage = storage
        self.products = self.storage.load_products()

    @log_action
    def add_product(self, name: str, price: float, quantity: int):
        product=Product(name, price, quantity)
        self.products.append(product)
        self.storage.save_products(self.products)
        print(f"Produkt {name} přidán.")

    def list_products(self):
        if self.products:
            print("Nebyly nalezeny produkty v listu")
            return
        for product in self.products:
            print(product)

    def search_products(self, query: str):
        results = [p for p in self.products if query.lower() in p._name.lower()]
        if not results:
            print("nebyly nalezeny produkty s tímto jménem")
            return
        for product in results:
            print(product)
    
    def total_value(self):
        total = sum(p.price * p.quantity for p in self.products)
        print(f"celková hodnota zboží je: {total:.2f} Kč")

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
    elif args.command == "total":
        manager.total_value()
    # TODO: Další příkazy
    else:
        parser.print_help()

if __name__ == "__main__":
    main()
