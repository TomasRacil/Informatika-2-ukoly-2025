import os

def nacti_data(soubor: str) -> list:
    """
    Načte data ze souboru.
    Vrací seznam slovníků ve formátu: [{'jmeno': 'Jan', 'znamky': [1, 2]}, ...]
    """
    data = []
    # TODO: Implementujte načítání souboru
    # 1. Otevřete soubor pro čtení
    # 2. Projděte řádek po řádku
    # 3. Rozdělte řádek podle čárky (první prvek je jméno, zbytek jsou známky)
    # 4. Převeďte známky na int
    # 5. Přidejte slovník do seznamu data
    
    try:
        with open(soubor, 'r', encoding='utf-8') as f:
            for radek in f:
                radek = radek.strip()
                if not radek:
                    continue

                casti = [c.strip() for c in radek.split(',')]
                jmeno = casti[0]
                znamky_str = casti[1:]

                try:
                    znamky = [int(z) for z in znamky_str if z]
                except ValueError:
                    print(f"Varování: Přeskakuji řádek s neplatnými známkami pro studenta '{jmeno}'.")
                    continue

                data.append({'jmeno': jmeno, 'znamky': znamky})
    except FileNotFoundError:
        print(f"Chyba: Soubor '{soubor}' nebyl nalezen.")
    return data


def spocitej_prumer(znamky: list) -> float:
    """
    Vypočítá aritmetický průměr ze seznamu známek.
    Pokud je seznam prázdný, vrací 0.0.
    """
    # TODO: Implementujte výpočet průměru
    if znamky:
        return sum(znamky) / len(znamky)
    else:
        return 0.0


def prospel(prumer: float) -> bool:
    """
    Vrátí True, pokud je průměr <= 3.5, jinak False.
    """
    # TODO: Implementujte podmínku prospěchu
    if prumer <= 3.5:
        return True
    else:
        return False
    


def zpracuj_vysledky(studenti: list) -> dict:
    """
    Zpracuje seznam studentů a vrátí slovník s výsledky.
    Formát výstupu: {'Jmeno': {'prumer': 1.5, 'prospel': True}, ...}
    """
    vysledky = {}
    # TODO: Projděte seznam studentů
    # 1. Pro každého zavolejte spocitej_prumer
    # 2. Zavolejte prospel
    # 3. Uložte do slovníku vysledky pod klíčem jména studenta
    for student in studenti:
        jmeno = student['jmeno']
        znamky = student['znamky']
        prumer = spocitej_prumer(znamky)
        uspesnost = prospel(prumer)
        vysledky[jmeno] = {'prumer': prumer, 'prospel': uspesnost}
    return vysledky


def uloz_report(vystupni_soubor: str, vysledky: dict) -> None:
    """
    Uloží výsledky do souboru ve formátu:
    Jmeno: Prumer (PROSPEL/NEPROSPEL)
    """
    # TODO: Otevřete soubor pro zápis a zapište formátované výsledky
    with open(vystupni_soubor, 'w', encoding='utf-8') as f:
        for jmeno, data in vysledky.items():
            prumer = data['prumer']
            status = "PROSPEL" if data['prospel'] else "NEPROSPEL"
            f.write(f"{jmeno}: {prumer:.2f} ({status})\n")
    pass


if __name__ == "__main__":
    # Tento blok slouží pro vaše manuální testování
    # Vytvořte si soubor 'studenti.txt' s testovacími daty pro vyzkoušení
    
    vstup = "studenti.txt"
    vystup = "report.txt"

    if os.path.exists(vstup):
        print(f"Načítám data z {vstup}...")
        data = nacti_data(vstup)
        print(f"Načteno: {data}")
        
        zpracovano = zpracuj_vysledky(data)
        print(f"Výsledky: {zpracovano}")
        
        uloz_report(vystup, zpracovano)
        print(f"Report uložen do {vystup}")
    else:
        print(f"Soubor {vstup} neexistuje. Vytvořte ho pro testování.")