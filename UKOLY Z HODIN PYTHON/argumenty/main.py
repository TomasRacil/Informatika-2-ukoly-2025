import argparse

# 1. Parser  
parser = argparse.ArgumentParser(description="Popis programu")

# 2. Argumenty  
parser.add_argument("cislo", type=int,help="Zadejte číslo") # Povinný  
parser.add_argument("--mocnina", type=int, default=2) # Volitelný

# 3. Zpracování  
args = parser.parse_args()

print(f"Mocnina {args.mocnina} čísla {args.cislo}, je {args.cislo**args.mocnina}.")