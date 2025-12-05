import os

def nacti_data(soubor: str) -> list:
    """
    Načte data ze souboru.
    Vrací seznam slovníků ve formátu: [{'jmeno': 'Jan', 'znamky': [1, 2]}, ...]
    """
    data = []
    with open(soubor, "r", encoding="utf-8") as f:
        for radek in f:
            radek = radek.strip()
            if not radek:
                continue
            casti = radek.split(",")
            jmeno = casti[0].strip()
            znamky = [int(x) for x in casti[1:] if x.strip().isdigit()]
            data.append({"jmeno": jmeno, "znamky": znamky})

    return data


def spocitej_prumer(znamky: list) -> float:
    """
    Vypočítá aritmetický průměr ze seznamu známek.
    Pokud je seznam prázdný, vrací 0.0.
    """
    if not znamky:
        return 0.0
    return sum(znamky) / len(znamky)



def prospel(prumer: float) -> bool:
    """
    Vrátí True, pokud je průměr <= 3.5, jinak False.
    """
    # TODO: Implementujte podmínku prospěchu
    return prumer <= 3.5

def zpracuj_vysledky(studenti: list) -> dict:
    """
    Zpracuje seznam studentů a vrátí slovník s výsledky.
    Formát výstupu: {'Jmeno': {'prumer': 1.5, 'prospel': True}, ...}
    """
    vysledky = {}
    for student in studenti:
        jmeno = student["jmeno"]
        znamky = student["znamky"]
        prumer = spocitej_prumer(znamky)
        vysledky[jmeno] = {
            "prumer": prumer,
            "prospel": prospel(prumer)
        }
    return vysledky


def uloz_report(vystupni_soubor: str, vysledky: dict) -> None:
    """
    Uloží výsledky do souboru ve formátu:
    Jmeno: Prumer (PROSPEL/NEPROSPEL)
    """
    with open(vystupni_soubor, "w", encoding = "utf-8") as f:
        for jmeno, data in vysledky.items():
            prumer = data['prumer']
            status = "PROSPEL" if data['prospel'] else "NEPROSPEL"
            f.write(f"{jmeno}: {prumer:.2f} ({status})\n")


if __name__ == "__main__":
    print(os.getcwd()) # z nejakeho dovodu mi to nenacita subory v workspace bez tohoto pricom to nema vplyv na cestu
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