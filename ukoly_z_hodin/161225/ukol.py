from os import dirname, join, realpath

class Polozka:
    def __init__(self, nazev:str, cena:int, mnozstvi:int):
        self.nazev = nazev 
        self.cena = cena
        self.mnozstvi = mnozstvi
        pass 
    def __str__(self):
        return f"{self.nazev}: {self.cena} Kč ({self.mnozstvi} ks)" 
    def __repr__(self):
        # Polozka('Jablko', 25.5, 100)
        return tuple(self.nazev, self.cena, self.mnozstvi)

