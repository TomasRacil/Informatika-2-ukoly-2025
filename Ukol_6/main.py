import os

def nacti_data(soubor: str) -> list:
    data = []
    with open(soubor, "r", encoding="utf-8") as f:
        for radek in f:
            radek = radek.strip()
            if not radek:
                continue

            casti = radek.split(",")
            jmeno = casti[0].strip()

            # OPRAVA – ignoruj prázdné položky
            znamky = [int(z.strip()) for z in casti[1:] if z.strip() != ""]

            data.append({
                "jmeno": jmeno,
                "znamky": znamky
            })
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
        pr = prospel(prumer)

        vysledky[jmeno] = {
            "prumer": prumer,
            "prospel": pr
        }

    return vysledky


def uloz_report(vystupni_soubor: str, vysledky: dict) -> None:
    """
    Uloží výsledky do souboru ve formátu:
    Jmeno: Prumer (PROSPEL/NEPROSPEL)
    """
    with open(vystupni_soubor, "w", encoding="utf-8") as f:
        for jmeno, udaje in vysledky.items():
            prumer = udaje["prumer"]
            prospel_txt = "PROSPEL" if udaje["prospel"] else "NEPROSPEL"

            f.write(f"{jmeno}: {prumer:.2f} ({prospel_txt})\n")


if __name__ == "__main__":
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
