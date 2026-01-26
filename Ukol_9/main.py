import argparse
import sys
from models import Product
from storage import Storage

# TODO: Implementovat dekorátor @log_action (zapsat do history.log)
def log_action(func):
    def wrapper(*args, **kwargs):
        with open("history.log", "a") as log_file:
            log_file.write(f"Action: {func.__name__}\n")
        return func(*args, **kwargs)
    return wrapper
class InventoryManager:
    def __init__(self, storage: Storage):
        self.storage = storage
        self.products = self.storage.load_products()

    @log_action
    def add_product(self, name: str, price: float, quantity: int):
        # TODO: Vytvořit produkt, přidat do self.products, uložit
        new_product = Product(name = name, price = price, quantity = quantity)
        self.products.append(new_product)
        self.storage.save_products(self.products)
            
    def list_products(self):
        # TODO: Vypsat všechny produkty
        for product in self.products:
            print(product)

        print("\n=== Seznam produktů ===")
        for i, product in enumerate(self.products, 1):
            print(f"{i}. {product}")
        print()

    def search_products(self, query: str):
        # TODO: Vyhledat produkty obsahující query v názvu
        total = sum(p.price * p.quantity for p in self.products)
        print(f"Celková hodnota skladu: {total} Kč")

        if not found:
            print(
                f"Nebyly nalezeny žádné produkty odpovídající dotazu '{query}'")
            return

        print(f"\n=== Nalezené produkty pro '{query}' ===")
        for i, product in enumerate(found, 1):
            print(f"{i}. {product}")
        print()
    
    def total_value(self):
        # TODO: Spočítat celkovou hodnotu
        total = sum(p.price * p.quantity for p in self.products)
        print(f"\nCelková hodnota skladu: {total:.2f} Kč")
        
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
