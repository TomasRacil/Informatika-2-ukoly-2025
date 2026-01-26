import argparse
import datetime
from models import Product
from storage import Storage

def log_action(func):
    """Dekorátor pro zápis akcí do history.log s časovým razítkem."""
    def wrapper(*args, **kwargs):
        now = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        with open("history.log", "a", encoding="utf-8") as f:
            f.write(f"[{now}] Spuštěna akce: {func.__name__}\n")
        return func(*args, **kwargs)
    return wrapper

class InventoryManager:
    def __init__(self, storage: Storage):
        self.storage = storage
        self.products = self.storage.load_products()

    @log_action
    def add_product(self, name: str, price: float, quantity: int):
        new_product = Product(name, price, quantity)
        self.products.append(new_product)
        self.storage.save_products(self.products)
        print(f"Produkt {name} přidán.")

    def list_products(self):
        if not self.products:
            print("Sklad je prázdný.")
            return
        for product in self.products:
            print(product)

    def search_products(self, query: str):
        found = [p for p in self.products if query.lower() in p.name.lower()]
        if not found:
            print(f"Žádný produkt neobsahuje: {query}")
        else:
            for p in found:
                print(p)

    def total_value(self):
        total = sum(p.price * p.quantity for p in self.products)
        print(f"Celková hodnota skladu: {total:.2f} Kč")

def main():
    parser = argparse.ArgumentParser(description="Systém správy skladu")
    subparsers = parser.add_subparsers(dest="command")

    # add
    add_parser = subparsers.add_parser("add", help="Přidat produkt")
    add_parser.add_argument("--name", required=True)
    add_argument_price = add_parser.add_argument("--price", required=True, type=float)
    add_argument_qty = add_parser.add_argument("--qty", required=True, type=int)

    # list
    subparsers.add_parser("list", help="Vypsat produkty")
    
    # search
    search_parser = subparsers.add_parser("search", help="Hledat produkt")
    search_parser.add_argument("--query", required=True)

    # total
    subparsers.add_parser("total", help="Celková hodnota skladu")

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
    else:
        parser.print_help()

if __name__ == "__main__":
    main()