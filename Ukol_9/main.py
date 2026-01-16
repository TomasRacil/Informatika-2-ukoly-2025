import argparse
import sys
from models import Product
from storage import Storage
from datetime import datetime

# TODO: Implementovat dekorátor @log_action (zapsat do history.log)
def log_action(func):
    def wrapper(self, *args, **kwargs):
        # ... logika logování ...
        prikaz = func.__name__
        timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        log_message = f"{timestamp} | Command: {prikaz}"

        if prikaz == "add_product":
            name = args[0]
            price = args[1]
            qty = args[2]
            log_message = f"{timestamp} ADD | Produkt: '{name}' | Cena: {price} Kč | Množství: {qty}"
        
        if prikaz == "remove_product":
            name = args[0]
            qty = args[1]
            log_message = f"{timestamp} REMOVE | Produkt: '{name}' | Množství: {qty}"
        
        try:
            with open("history.log", "a", encoding="utf-8") as f:
                f.write(log_message + "\n")
        except Exception as e:
            print(f"ERROR: {e}", file=sys.stderr)
        return func(self, *args, **kwargs)
    return wrapper

class InventoryManager:
    def __init__(self, storage: Storage):
        self.storage = storage
        self.products = self.storage.load_products()

    @log_action
    def add_product(self, name: str, price: float, quantity: int):
        # TODO: Vytvořit produkt, přidat do self.products, uložit
        novy_produkt = Product(name=name, price=price, quantity=quantity)
        self.products.append(novy_produkt)
        self.storage.save_products(self.products)
        print(f"Produkt {name} přidán.")

    def list_products(self):
        # TODO: Vypsat všechny produkty
        if not self.products:
            print("Sklad je prázdný")
            return
        
        print("Název | Cena | Množství")
        for p in self.products:
            print(f"{p.name} | {p.price} | {p.quantity}")

    def search_products(self, query: str):
        # TODO: Vyhledat produkty obsahující query v názvu
        vysledky = []

        for p in self.products:
            if query.lower() in p.name.lower():
                vysledky.append(p)
        
        if not vysledky:
            print("Hledání neodpovídá žádný produkt")
            return
        
        for p in vysledky:
            print(f"{p.name} | {p.price} Kč | {p.quantity} ks")
    
    def total_value(self):
        # TODO: Spočítat celkovou hodnotu
        celkova_hodnota = sum(p.price * p.quantity for p in self.products)
        print(f"Celková hodnota: {celkova_hodnota:,.2f} Kč")

    @log_action
    def remove_product(self, name: str, quantity: int):
        produkt_nalezen = False
        
        for p in self.products:
            if p.name.lower() == name.lower():
                p.quantity -= quantity
                produkt_nalezen = True

            if p.quantity <= 0:
                self.products.remove(p)
                print(f"Produkt {name} byl odstraněn")
            else:
                print(f"Z produktu {name} bylo odebráno {quantity} ks, zbývá: {p.quantity}")
                 
            self.storage.save_products(self.products)
            break

        if not produkt_nalezen:
            print(f"Produkt {name} nenalezen")

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

    subparsers.add_parser("total", help="Celková hodnota skladu")

    remove_parser = subparsers.add_parser("remove", help="Odebrat množství nebo produkt")
    remove_parser.add_argument("--name", required=True, help="Název produktu")
    remove_parser.add_argument("--qty", required=True, type=int, help="Množství k odebrání")

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
    elif args.command == "total":
        manager.total_value()
    elif args.command == "remove":
        manager.remove_product(args.name, args.qty)
    else:
        parser.print_help()

if __name__ == "__main__":
    main()
