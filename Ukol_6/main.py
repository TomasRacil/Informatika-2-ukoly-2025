import os
from os.path import join, dirname, realpath
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

    with open(soubor) as cteni:
        for line in cteni:
            student = line.split(',')
            znamkyint = []
            for znamky in student[1:]:
                if znamky.strip() != "":
                    znamkyint.append(int(znamky))
            data.append({"jmeno" : student[0], "znamky" : znamkyint})
    return data


def spocitej_prumer(znamky: list) -> float:
    """
    Vypočítá aritmetický průměr ze seznamu známek.
    Pokud je seznam prázdný, vrací 0.0.
    """
    # TODO: Implementujte výpočet průměru
    prumer : float = 0
    for znamka in znamky:
        prumer = prumer + znamka
    
    if len(znamky) == 0:
        return 0.0
    else:
        prumer = prumer /len(znamky)
        return prumer


def prospel(prumer: float) -> bool:
    """
    Vrátí True, pokud je průměr <= 3.5, jinak False.
    """
    # TODO: Implementujte podmínku prospěchu
    if(prumer <= 3.5):
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
        prumer = spocitej_prumer(student['znamky'])
        bprospel = prospel(prumer)
        vysledky[student['jmeno']] = {'prumer' : prumer, 'prospel' : bprospel}
    return vysledky


def uloz_report(vystupni_soubor: str, vysledky: dict) -> None:
    """
    Uloží výsledky do souboru ve formátu:
    Jmeno: Prumer (PROSPEL/NEPROSPEL)
    """
    with open(vystupni_soubor, 'w') as psani:
        for student in vysledky:
            psani.writelines((student + ":", " ",str(vysledky[student]['prumer']), " PROSPEL" if vysledky[student]['prospel'] == True else " NEPROSPEL", "\n"))
    # TODO: Otevřete soubor pro zápis a zapište formátované výsledky
    pass


if __name__ == "__main__":
    # Tento blok slouží pro vaše manuální testování
    # Vytvořte si soubor 'studenti.txt' s testovacími daty pro vyzkoušení
    
    vstup = join(dirname(realpath(__file__)),"studenti.txt")
    vystup = join(dirname(realpath(__file__)),"report.txt")

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