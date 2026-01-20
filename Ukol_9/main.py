import argparse
import sys
from datetime import datetime
from functools import wraps
from models import Product
from storage import Storage


def log_action(func):
    """Dekorátor pro logování akcí do souboru history.log"""
    @wraps(func)
    def wrapper(*args, **kwargs):
        timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        func_name = func.__name__

        # Zavoláme původní funkci
        result = func(*args, **kwargs)

        # Zapíšeme do logu
        try:
            with open("history.log", "a", encoding="utf-8") as log_file:
                log_file.write(
                    f"[{timestamp}] {func_name} - {args[1:]} {kwargs}\n")
        except Exception as e:
            print(f"Chyba při logování: {e}")

        return result
    return wrapper


class InventoryManager:
    def __init__(self, storage: Storage):
        self.storage = storage
        self.products = self.storage.load_products()

    @log_action
    def add_product(self, name: str, price: float, quantity: int):
        """Přidá produkt do skladu."""
        try:
            product = Product(name, price, quantity)
            self.products.append(product)
            self.storage.save_products(self.products)
            print(f"Produkt {name} přidán.")
        except ValueError as e:
            print(f"Chyba: {e}")

    def list_products(self):
        """Vypíše všechny produkty."""
        if not self.products:
            print("Sklad je prázdný.")
            return

        print("\n=== Seznam produktů ===")
        for i, product in enumerate(self.products, 1):
            print(f"{i}. {product}")
        print()

    def search_products(self, query: str):
        """Vyhledá produkty obsahující query v názvu."""
        query_lower = query.lower()
        found = [p for p in self.products if query_lower in p.name.lower()]

        if not found:
            print(
                f"Nebyly nalezeny žádné produkty odpovídající dotazu '{query}'")
            return

        print(f"\n=== Nalezené produkty pro '{query}' ===")
        for i, product in enumerate(found, 1):
            print(f"{i}. {product}")
        print()

    def total_value(self):
        """Vypočítá a vypíše celkovou hodnotu skladu."""
        total = sum(p.price * p.quantity for p in self.products)
        print(f"\nCelková hodnota skladu: {total:.2f} Kč")
        return total


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
