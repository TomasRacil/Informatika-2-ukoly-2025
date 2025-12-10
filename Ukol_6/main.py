import os


def nacti_data(soubor: str) -> list:
    """
    Načte data ze souboru.
    Vrací seznam slovníků ve formátu: [{'jmeno': 'Jan', 'znamky': [1, 2]}, ...]
    """
    data = []
    try:
        with open(soubor, 'r', encoding='utf-8') as f:
            for radek in f:
                radek = radek.strip()
                if not radek:
                    continue
                parts = radek.split(',')
                jmeno = parts[0].strip()
                znamky = [int(x.strip()) for x in parts[1:] if x.strip() != ""]
                data.append({'jmeno': jmeno, 'znamky': znamky})
    except FileNotFoundError:
        print(f"Soubor {soubor} nebyl nalezen")
    return data


def spocitej_prumer(znamky: list) -> float:
    """
    Vypočítá aritmetický průměr ze seznamu známek.
    Pokud je seznam prázdný, vrací 0.0.
    """
    if not znamky:
        return 0.0
    else:
        prumer = sum(znamky) / len(znamky)
    return prumer


def prospel(prumer: float) -> bool:
    """
    Vrátí True, pokud je průměr <= 3.5, jinak False.
    """
    if prumer <= 3.5 and prumer > 0:
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
        prumer = spocitej_prumer(znamky)
        prospel_nebo_ne = prospel(prumer)
        vysledky[jmeno] = {'prumer': prumer, 'prospel': prospel_nebo_ne}
    return vysledky


def uloz_report(vystupni_soubor: str, vysledky: dict) -> None:
    """
    Uloží výsledky do souboru ve formátu:
    Jmeno: Prumer (PROSPEL/NEPROSPEL)
    """
    with open(vystupni_soubor, 'w', encoding='utf-8') as f:
        for jmeno, data in vysledky.items():
            prumer = data['prumer']
            if data['prospel']:
                prospesnost = 'PROSPEL'
            else:
                prospesnost = 'NEPROSPEL'
            f.write(f"{jmeno}: {prumer} ({prospesnost})\n")


if __name__ == "__main__":
    # Tento blok slouží pro vaše manuální testování
    # Vytvořte si soubor 'studenti.txt' s testovacími daty pro vyzkoušení

    vstup = "Ukol_6/studenti.txt"
    vystup = "Ukol_6/report.txt"

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
