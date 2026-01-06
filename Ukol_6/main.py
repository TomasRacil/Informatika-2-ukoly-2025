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

            # zbytek → známky (může být prázdné pole)
            znamky = []
            if len(casti) > 1:
                for z in casti[1:]:
                    z = z.strip()
                    if z.isdigit():  # ignoruj prázdné
                        znamky.append(int(z))

            data.append({"jmeno": jmeno, "znamky": znamky})

    return data


def spocitej_prumer(znamky: list) -> float:
    """Vypočítá aritmetický průměr."""
    if not znamky:
        return 0.0
    return sum(znamky) / len(znamky)


def prospel(prumer: float) -> bool:
    """Vrátí True, pokud průměr <= 3.5."""
    return prumer <= 3.5


def zpracuj_vysledky(studenti: list) -> dict:
    """
    Vrátí slovník:
    {'Jmeno': {'prumer': X, 'prospel': Y}}
    """
    vysledky = {}

    for s in studenti:
        jmeno = s["jmeno"]
        znamky = s["znamky"]
        prumer = spocitej_prumer(znamky)
        vysledky[jmeno] = {
            "prumer": prumer,
            "prospel": prospel(prumer)
        }

    return vysledky


def uloz_report(vystupni_soubor: str, vysledky: dict) -> None:
    """
    Zapíše výsledky do souboru:
    Jmeno: Prumer (PROSPEL/NEPROSPEL)
    """
    with open(vystupni_soubor, "w", encoding="utf-8") as f:
        for jmeno, info in vysledky.items():
            stav = "PROSPEL" if info["prospel"] else "NEPROSPEL"
            f.write(f"{jmeno}: {info['prumer']} ({stav})\n")


if __name__ == "__main__":
    # Tento blok slouží pro vaše manuální testování
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
