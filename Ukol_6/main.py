import os
from os.path import join, dirname, realpath


def nacti_data(soubor: str) -> list:
    """
    Načte data ze souboru.
    Vrací seznam slovníků ve formátu: [{'jmeno': 'Jan', 'znamky': [1, 2]}, ...]
    """
    data = []

    soubor = join(dirname(realpath(__file__)), soubor)

    with open(soubor, 'r', encoding='utf-8') as f:
        f_data = f.read().splitlines()

        for line in f_data:
            [jmeno, znamky] = line.split(",", 1)
            
            znamky = [int(znamka) for znamka in znamky.split(",") if (znamka != "")]

            data.append({"jmeno": jmeno, "znamky": znamky})
            
    # TODO: Implementujte načítání souboru
    # 1. Otevřete soubor pro čtení
    # 2. Projděte řádek po řádku
    # 3. Rozdělte řádek podle čárky (první prvek je jméno, zbytek jsou známky)
    # 4. Převeďte známky na int
    # 5. Přidejte slovník do seznamu data
    return data


def spocitej_prumer(znamky: list) -> float:
    """
    Vypočítá aritmetický průměr ze seznamu známek.
    Pokud je seznam prázdný, vrací 0.0.
    """

    if (len(znamky) > 0):
        return sum(znamky) / len(znamky)

    # TODO: Implementujte výpočet průměru
    return 0.0


def prospel(prumer: float) -> bool:
    """
    Vrátí True, pokud je průměr <= 3.5, jinak False.
    """

    # nemůže prospět, pokud nemá žádné známky
    if (prumer == 0.0):
        return False
    
    if (prumer <= 3.5):
        return True

    # TODO: Implementujte podmínku prospěchu
    return False


def zpracuj_vysledky(studenti: list) -> dict:
    """
    Zpracuje seznam studentů a vrátí slovník s výsledky.
    Formát výstupu: {'Jmeno': {'prumer': 1.5, 'prospel': True}, ...}
    """
    vysledky = {}

    for student in studenti:
        prumer = spocitej_prumer(student['znamky'])
        passed = prospel(prumer)

        vysledky[student["jmeno"]] = {"prumer": prumer, "prospel": passed}

    # TODO: Projděte seznam studentů
    # 1. Pro každého zavolejte spocitej_prumer
    # 2. Zavolejte prospel
    # 3. Uložte do slovníku vysledky pod klíčem jména studenta
    return vysledky


def uloz_report(vystupni_soubor: str, vysledky: dict) -> None:
    """
    Uloží výsledky do souboru ve formátu:
    Jmeno: Prumer (PROSPEL/NEPROSPEL)
    """
    # TODO: Otevřete soubor pro zápis a zapište formátované výsledky

    with open(vystupni_soubor, 'w', encoding='utf-8') as f:
        for jmeno, data in vysledky.items():
            status = "PROSPEL" if data['prospel'] else "NEPROSPEL"
            f.write(f"{jmeno}: {data['prumer']} ({status})\n")
    pass


if __name__ == "__main__":
    # Tento blok slouží pro vaše manuální testování
    # Vytvořte si soubor 'studenti.txt' s testovacími daty pro vyzkoušení
    
    vstup = join(dirname(realpath(__file__)), "studenti.txt")
    vystup = join(dirname(realpath(__file__)), "report.txt")

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