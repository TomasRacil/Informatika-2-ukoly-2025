from functools import wraps
import csv


# ==============================================================================
# Část 2: Dekorátor pro logování
# ==============================================================================

def log_operace(func):
    """Dekorátor pro logování operací"""
    @wraps(func)
    def wrapper(*args, **kwargs):
        # args[0] je self, zbytek jsou argumenty
        args_str = ', '.join(repr(arg) for arg in args[1:])
        kwargs_str = ', '.join(f'{k}={v!r}' for k, v in kwargs.items())
        all_args = ', '.join(filter(None, [args_str, kwargs_str]))
        
        print(f"[LOG] Volána metoda '{func.__name__}' s argumenty: ({all_args})")
        
        result = func(*args, **kwargs)
        return result
    return wrapper


# ==============================================================================
# Část 1: Třída Polozka a magické metody
# ==============================================================================

class Polozka:
    """Reprezentuje zboží ve skladu"""
    
    def __init__(self, nazev, cena, mnozstvi):
        """
        Konstruktor položky
        
        Args:
            nazev (str): Název zboží
            cena (float): Cena za kus
            mnozstvi (int): Množství kusů
        """
        self.nazev = nazev
        self.cena = cena
        self.mnozstvi = mnozstvi
    
    def __str__(self):
        """Čitelný popis položky"""
        return f"{self.nazev}: {self.cena} Kč ({self.mnozstvi} ks)"
    
    def __repr__(self):
        """Formát vhodný pro debugging"""
        return f"Polozka('{self.nazev}', {self.cena}, {self.mnozstvi})"
    
    def __eq__(self, other):
        """Dvě položky jsou stejné, pokud mají stejný název a cenu"""
        if not isinstance(other, Polozka):
            return False
        return self.nazev == other.nazev and self.cena == other.cena
    
    def __add__(self, other):
        """
        Sečte dvě instance Polozka
        
        Args:
            other: Druhá položka k sečtení
            
        Returns:
            Polozka: Nová instance se sečteným množstvím
            
        Raises:
            ValueError: Pokud položky nemají stejný název a cenu
        """
        if not isinstance(other, Polozka):
            return NotImplemented
        
        if self == other:  # Použije __eq__
            return Polozka(self.nazev, self.cena, self.mnozstvi + other.mnozstvi)
        else:
            raise ValueError(f"Nelze sčítat různé zboží: {self.nazev} vs {other.nazev}")


# ==============================================================================
# Část 3 a 4: Třída Sklad
# ==============================================================================

class Sklad:
    """Spravuje kolekci položek ve skladu"""
    
    def __init__(self):
        """Inicializuje prázdný sklad"""
        self._polozky = {}  # Slovník: nazev -> Polozka
    
    # --------------------------------------------------------------------------
    # Magické metody
    # --------------------------------------------------------------------------
    
    def __len__(self):
        """Vrátí celkový počet kusů všeho zboží na skladu"""
        return sum(polozka.mnozstvi for polozka in self._polozky.values())
    
    def __getitem__(self, nazev):
        """
        Umožní získat položku podle názvu pomocí indexace
        
        Args:
            nazev: Název položky
            
        Returns:
            Polozka: Položka s daným názvem
            
        Raises:
            KeyError: Pokud položka neexistuje
        """
        if nazev not in self._polozky:
            raise KeyError(f"Položka '{nazev}' není ve skladu")
        return self._polozky[nazev]
    
    # --------------------------------------------------------------------------
    # Context Manager (Část 4)
    # --------------------------------------------------------------------------
    
    def __enter__(self):
        """Vstup do context manageru"""
        print("Otevírám sklad...")
        return self
    
    def __exit__(self, exc_type, exc_val, exc_tb):
        """Výstup z context manageru - automatické uložení"""
        print("Zavírám sklad a ukládám data...")
        self.uloz_do_csv("autosave_sklad.csv")
        return False  # Nepotlačujeme výjimky
    
    # --------------------------------------------------------------------------
    # Metody pro správu skladu (Část 3)
    # --------------------------------------------------------------------------
    
    @log_operace
    def pridej_polozku(self, polozka):
        """
        Přidá objekt Polozka. Pokud už existuje, zvýší množství.
        
        Args:
            polozka (Polozka): Položka k přidání
        """
        if not isinstance(polozka, Polozka):
            raise TypeError("Očekává se objekt typu Polozka")
        
        if polozka.nazev in self._polozky:
            # Položka existuje - použijeme __add__
            existujici = self._polozky[polozka.nazev]
            self._polozky[polozka.nazev] = existujici + polozka
        else:
            # Nová položka
            self._polozky[polozka.nazev] = polozka
    
    @log_operace
    def odeber_polozku(self, nazev, pocet):
        """
        Sníží množství. Pokud klesne na 0, položku odstraní.
        
        Args:
            nazev (str): Název položky
            pocet (int): Počet kusů k odebrání
            
        Raises:
            KeyError: Pokud položka neexistuje
            ValueError: Pokud není dostatek kusů
        """
        if nazev not in self._polozky:
            raise KeyError(f"Položka '{nazev}' není ve skladu")
        
        polozka = self._polozky[nazev]
        
        if pocet > polozka.mnozstvi:
            raise ValueError(
                f"Nedostatek zboží '{nazev}': "
                f"požadováno {pocet}, dostupné {polozka.mnozstvi}"
            )
        
        polozka.mnozstvi -= pocet
        
        if polozka.mnozstvi == 0:
            del self._polozky[nazev]
    
    # --------------------------------------------------------------------------
    # Práce se soubory (Persistence)
    # --------------------------------------------------------------------------
    
    def uloz_do_csv(self, soubor):
        """
        Uloží všechny položky do CSV souboru
        
        Args:
            soubor (str): Cesta k souboru
        """
        with open(soubor, 'w', newline='', encoding='utf-8') as f:
            writer = csv.writer(f)
            writer.writerow(['nazev', 'cena', 'mnozstvi'])  # Hlavička
            
            for polozka in self._polozky.values():
                writer.writerow([polozka.nazev, polozka.cena, polozka.mnozstvi])
    
    @classmethod
    def nacti_z_csv(cls, soubor):
        """
        Načte sklad ze souboru CSV
        
        Args:
            soubor (str): Cesta k souboru
            
        Returns:
            Sklad: Nový sklad s načtenými položkami
        """
        sklad = cls()
        
        with open(soubor, 'r', encoding='utf-8') as f:
            reader = csv.DictReader(f)
            
            for row in reader:
                polozka = Polozka(
                    nazev=row['nazev'],
                    cena=float(row['cena']),
                    mnozstvi=int(row['mnozstvi'])
                )
                sklad._polozky[polozka.nazev] = polozka
        
        return sklad
    
    def vypis_sklad(self):
        """Vypíše obsah skladu"""
        print("\n=== Obsah skladu ===")
        if not self._polozky:
            print("Sklad je prázdný")
        else:
            for polozka in self._polozky.values():
                print(f"  {polozka}")
            print(f"Celkem kusů: {len(self)}")
        print("=" * 40)


# ==============================================================================
# Testovací skript
# ==============================================================================

def main():
    print("=== TESTOVÁNÍ INVENTORY SYSTÉMU ===\n")
    
    # 1. Vytvoření položek
    print("--- Část 1: Vytvoření položek a test sčítání ---")
    jablka = Polozka("Jablko", 10, 50)
    dalsi_jablka = Polozka("Jablko", 10, 20)
    hrusky = Polozka("Hruška", 15, 30)
    
    print(f"Jablka: {jablka}")
    print(f"Další jablka: {dalsi_jablka}")
    print(f"Test sčítání: {jablka + dalsi_jablka}")
    
    # Test chyby při sčítání různého zboží
    try:
        print(f"Chybné sčítání: {jablka + hrusky}")
    except ValueError as e:
        print(f"Chyba (očekáváno): {e}")
    
    # 2. Práce se skladem
    print("\n--- Část 2 a 3: Práce se skladem ---")
    sklad = Sklad()
    sklad.pridej_polozku(jablka)
    sklad.pridej_polozku(dalsi_jablka)  # Log: Volána metoda pridej...
    sklad.pridej_polozku(hrusky)         # Log: Volána metoda pridej...
    
    sklad.vypis_sklad()
    
    print(f"\nPoložka ve skladu: {sklad['Hruška']}")
    print(f"Celkem kusů na skladu: {len(sklad)}")
    
    # Test odebrání
    print("\n--- Test odebrání zboží ---")
    sklad.odeber_polozku('Hruška', 10)
    sklad.vypis_sklad()
    
    # 3. Uložení a načtení
    print("\n--- Část 3: Uložení a načtení ze souboru ---")
    sklad.uloz_do_csv("sklad_data.csv")
    print("Uloženo do sklad_data.csv")
    
    novy_sklad = Sklad.nacti_z_csv("sklad_data.csv")
    print(f"Načteno {len(novy_sklad)} kusů zboží z nového skladu.")
    novy_sklad.vypis_sklad()
    
    # 4. Test Context Manageru
    print("\n--- Část 4: Test Context Manageru ---")
    with Sklad() as temp_sklad:
        temp_sklad.pridej_polozku(Polozka("Meruňka", 25, 15))
        temp_sklad.pridej_polozku(Polozka("Broskev", 30, 10))
        temp_sklad.vypis_sklad()
    # Při opuštění with bloku se automaticky uloží do autosave_sklad.csv
    
    print("\n--- Ověření autosave ---")
    autosaved = Sklad.nacti_z_csv("autosave_sklad.csv")
    print(f"Z autosave načteno {len(autosaved)} kusů zboží.")
    autosaved.vypis_sklad()


if __name__ == "__main__":
    main()
