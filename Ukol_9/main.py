import argparse
import sys
import functools
from datetime import datetime
from models import Product
from storage import Storage

# Dekorátor pro logování akcí


def log_action(func):
    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        action_name = func.__name__
        timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")

        try:
            result = func(*args, **kwargs)
            log_message = f"[{timestamp}] Akce: {action_name} - Status: OK"
            with open("history.log", "a") as log_file:
                log_file.write(log_message + "\n")
            return result
        except Exception as e:
            log_message = f"[{timestamp}] Akce: {action_name} - Status: CHYBA ({str(e)})"
            with open("history.log", "a") as log_file:
                log_file.write(log_message + "\n")
            raise
    return wrapper


class InventoryManager:
    def __init__(self, storage: Storage):
        self.storage = storage
        self.products = self.storage.load_products()

    @log_action
    def add_product(self, name: str, price: float, quantity: int):
        product = Product(name, price, quantity)
        self.products.append(product)
        self.storage.save_products(self.products)
        print(f"Produkt '{name}' přidán.")

    def list_products(self):
        if not self.products:
            print("Sklad je prázdný.")
            return

        print("\n=== SEZNAM PRODUKTŮ ===")
        for idx, product in enumerate(self.products, 1):
            print(f"{idx}. {product}")
        print()

    def search_products(self, query: str):
        query_lower = query.lower()
        results = [p for p in self.products if query_lower in p.name.lower()]

        if not results:
            print(f"Žádné produkty neodpovídají hledanému slovu '{query}'.")
            return

        print(f"\n=== VÝSLEDKY HLEDÁNÍ PRO '{query}' ===")
        for idx, product in enumerate(results, 1):
            print(f"{idx}. {product}")
        print()

    def total_value(self):
        total = sum(p.price * p.quantity for p in self.products)
        print(f"\nCelková hodnota skladu: {total:,.2f}Kč\n")


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

    # Příkaz 'total'
    subparsers.add_parser("total", help="Vypsat celkovou hodnotu skladu")

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
