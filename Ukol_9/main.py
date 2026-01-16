import argparse
import datetime
from models import Product
from storage import Storage

# TODO: Implementovat dekorátor @log_action (zapsat do history.log)
def log_action(func):
    def wrapper(*args, **kwargs):
        now = datetime.datetime.now()
        with open("history.log", "a") as log_file:
            log_file.write(f"{now} - {func.__name__} {args[1:]}\n")
        return func(*args, **kwargs)
    return wrapper

class InventoryManager:
    def __init__(self, storage: Storage):
        self.storage = storage
        self.products = self.storage.load_products()

    @log_action
    def add_product(self, name: str, price: float, quantity: int):
        produkt = Product(name, price, quantity)
        self.products.append(produkt)
        print(f"Produkt {name} přidán.")
        self.storage.save_products(self.products)

    @log_action
    def remove_product(self, name: str):
        product = self.search_products(name)
        if product:
            self.products.remove(product)
            print(f"Produkt {name} odstraněn.")
            self.storage.save_products(self.products)
        else:
            print(f"Produkt {name} nenalezen.")


    def list_products(self):
        for product in self.products:
            print(f"Produkt {product._name} cena: {product._price} množství: {product._quantity}")


    def search_products(self, query: str):
        for product in self.products:
            if query == product._name:
                return product
        return None

    
    def total_value(self):
        celkova_hodnota = 0
        for product in self.products:
            celkova_hodnota += product._price * product._quantity
        print(f"Celková hodnota skladu: {celkova_hodnota}")

def main():
    parser = argparse.ArgumentParser(description="Systém správy skladu")
    subparsers = parser.add_subparsers(dest="command")

    # Příkaz 'add'
    add_parser = subparsers.add_parser("add", help="Přidat produkt")
    add_parser.add_argument("--name", required=True, help="Název produktu")
    add_parser.add_argument("--price", required=True, type=float, help="Cena")
    add_parser.add_argument("--qty", required=True, type=int, help="Množství")

    # Příkaz 'remove'
    remove_parser = subparsers.add_parser("remove", help="Odstranit produkt")
    remove_parser.add_argument("--name", required=True, help="Název produktu k odstranění")

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
    elif args.command == "remove":
        manager.remove_product(args.name)
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
