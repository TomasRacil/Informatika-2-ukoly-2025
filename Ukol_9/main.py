import argparse
import sys
from models import Product
from storage import Storage
from datetime import datetime

# TODO: Implementovat dekorátor @log_action (zapsat do history.log)
def log_action(func):
    def wrapper(*args, **kwargs):
        result = func(*args, **kwargs)
        with open("history.log", "a", encoding="utf-8") as f:
            timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
            f.write(f"[{timestamp}] Spuštěna funkce: {func.__name__}\n")
    return wrapper

class InventoryManager:
    def __init__(self, storage: Storage):
        self.storage = storage
        self.products = self.storage.load_products()

    @log_action
    def add_product(self, name: str, price: float, quantity: int):
        # TODO: Vytvořit produkt, přidat do self.products, uložit
        produkt = Product(name, price, quantity)
        self.products.append(produkt)
        self.storage.save_products(self.products)
        print(f"Produkt {name} přidán.")

    def list_products(self):
        # TODO: Vypsat všechny produkty
        if not self.products:
            print("Sklad je prázdný.")
            return
        else:
            for product in self.products:
                print(product)

    def search_products(self, query: str):
        # TODO: Vyhledat produkty obsahující query v názvu
        produkty = self.storage.load_products()
        produktyl : list[Product]
        for produkt in produkty:
            if produkt.name.lower() == query.lower():
                produktyl.append(produkt)

        if len(produktyl) == 0:
            print("Produkt nenajit")
        else:
            for produkt in produktyl:
                print(produkt.name)
    
    def total_value(self):
        # TODO: Spočítat celkovou hodnotu
        for produkt in self.products:
            total = total + (produkt.price * produkt.quantity)
        print(f"Celkem: {total}")

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
