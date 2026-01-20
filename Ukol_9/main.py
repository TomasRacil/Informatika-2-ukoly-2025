import argparse
import sys
from datetime import datetime
from typing import List
from models import Product
from storage import Storage

# Implementace dekorátoru @log_action
def log_action(func):
    def wrapper(*args, **kwargs):
        # Zavoláme původní funkci
        result = func(*args, **kwargs)
        
        # Získáme název akce (název metody)
        action_name = func.__name__
        
        # Zápis do souboru
        timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        log_entry = f"[{timestamp}] Akce: {action_name} | Args: {args[1:]} {kwargs}\n"
        
        with open("history.log", "a", encoding="utf-8") as f:
            f.write(log_entry)
            
        return result
    return wrapper

class InventoryManager:
    def __init__(self, storage: Storage):
        self.storage = storage
        self.products: List[Product] = self.storage.load_products()

    @log_action
    def add_product(self, name: str, price: float, quantity: int):
        try:
            new_product = Product(name, price, quantity)
            self.products.append(new_product)
            self.storage.save_products(self.products)
            print(f"Úspěch: Produkt '{name}' byl přidán.")
        except ValueError as e:
            print(f"Chyba: {e}")

    def list_products(self):
        if not self.products:
            print("Sklad je prázdný.")
            return
        
        print(f"{'NÁZEV':<20} {'CENA':<10} {'MNOŽSTVÍ':<10} {'KATEGORIE'}")
        print("-" * 55)
        for p in self.products:
            print(f"{p.name:<20} {p.price:<10} {p.quantity:<10} {p.category}")

    def search_products(self, query: str):
        found = [p for p in self.products if query.lower() in p.name.lower()]
        if found:
            print(f"Nalezeno {len(found)} produktů:")
            for p in found:
                print(p)
        else:
            print(f"Žádný produkt odpovídající '{query}' nebyl nalezen.")
    
    def total_value(self):
        total = sum(p.price * p.quantity for p in self.products)
        print(f"Celková hodnota skladu: {total:,.2f} Kč")

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

    # Příkaz 'total' (Chyběl v původním kódu)
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