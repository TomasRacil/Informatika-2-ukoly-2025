import os
from os.path import join, dirname, realpath
def nacti_data(soubor: str) -> list:
    """
    Načte data ze souboru.
    Vrací seznam slovníků ve formátu: [{'jmeno': 'Jan', 'znamky': [1, 2]}, ...]
    """
    data = []
    with open(soubor, "r", encoding="UTF-8") as file:
        for line in file:
            line = line.strip()
            if not line: 
                  continue

            parts = [p.strip() for p in line.split(",")]
            jmeno : str = parts[0]
            znamky:list[int] = [int(z) for z in parts[1:] if z.isdigit()]
            data.append({'jmeno':jmeno,'znamky':znamky})
    return data


def spocitej_prumer(znamky: list) -> float:
    if not znamky:
     return 0.0
    else: 
     return sum(znamky)/len(znamky)


def prospel(prumer: float) -> bool:
    if prumer <= 3.5 :
        return True
    else:
         return False
   


def zpracuj_vysledky(studenti: list) -> dict:
    """
    Zpracuje seznam studentů a vrátí slovník s výsledky.
    Formát výstupu: {'Jmeno': {'prumer': 1.5, 'prospel': True}, ...}
    """
    vysledky = {}
    for student in studenti:
        jmeno = student['jmeno']
        znamky = student['znamky']
        prumer: float = spocitej_prumer(znamky)
        uspesnost: bool = prospel(prumer)
        vysledky[jmeno] = {'prumer': prumer, 'prospel': uspesnost}
    return vysledky

def uloz_report(vystupni_soubor: str, vysledky: dict) -> None:
    """
    Uloží výsledky do souboru ve formátu:
    Jmeno: Prumer (PROSPEL/NEPROSPEL)
    """
    # TODO: Otevřete soubor pro zápis a zapište formátované výsledky
    with open(vystupni_soubor, "w", encoding="utf-8") as file:
        for jmeno, data in vysledky.items():
            prumer = data['prumer']
            uspesnost = "PROSPEL" if data['prospel'] else "NEPROSPEL"
            file.write(f"{jmeno}: {prumer}, ({uspesnost})\n")
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