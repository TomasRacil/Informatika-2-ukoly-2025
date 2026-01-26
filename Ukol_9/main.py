import argparse
import sys, logging, time
from models import Product
from storage import Storage

logging.basicConfig(  
    level=logging.INFO,  # Loguj vše od INFO výše (DEBUG se ignoruje)  
    filename='history.log',  # Ulož do souboru  
    format='%(asctime)s - %(levelname)s - %(message)s' # Přidej čas  
)

# TODO: Implementovat dekorátor @log_action (zapsat do history.log)
def log_action(func):
    def wrapper(*args, **kwargs):
        # ... logika logování ...

        logging.info(f"Produkt: {args[1]}, v hodnote: {args[2]} a mnozstvi {args[3]} byl pridan")
        return func(*args, **kwargs)
    return wrapper

class InventoryManager:
    def __init__(self, storage: Storage):
        self.storage = storage
        self.products = self.storage.load_products()

    @log_action
    def add_product(self, name: str, price: float, quantity: int):
        # TODO: Vytvořit produkt, přidat do self.products, uložit
        new_product = Product(name, price, quantity)
        self.products.append(new_product)
        self.storage.save_products(self.products)

        print(f"Produkt {name} přidán.")

    def list_products(self):
        # TODO: Vypsat všechny produkty
        print(*self.products)

    def search_products(self, query: str):
        # TODO: Vyhledat produkty obsahující query v názvu
        matching_products = [product for product in self.products if query.lower() in product.name.lower()]

        print(*matching_products)
    
    def total_value(self):
        # TODO: Spočítat celkovou hodnotu
        print(sum((product.price * product.quantity for product in self.products)))

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
