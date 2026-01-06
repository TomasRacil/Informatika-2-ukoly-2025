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
    with open(soubor) as f:
        for x in f:
            x = x.strip()
            radek = x.split(',')
            radek = [x for x in radek if x.strip()]
            jmeno = radek[0]
            znamky = list(map(int, radek[1:]))

            slovnik = {
                "jmeno" : jmeno,
                "znamky" : znamky
            }

            data.append(slovnik)

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
    for x in studenti:
        jmeno = (x["jmeno"])
        prumer = spocitej_prumer(x["znamky"])
        var_prospel = prospel(prumer)
        vysledky[jmeno] = {
            "prumer" : prumer,
            "prospel" : var_prospel
        }
    return vysledky


def uloz_report(vystupni_soubor: str, vysledky: dict) -> None:
    """
    Uloží výsledky do souboru ve formátu:
    Jmeno: Prumer (PROSPEL/NEPROSPEL)
    """
    # TODO: Otevřete soubor pro zápis a zapište formátované výsledky
    with open(vystupni_soubor, "w") as f:
        for jmeno, studijni_vysledky in vysledky.items():
            if studijni_vysledky["prospel"]:
                text_prospel = "PROSPEL"
            else:
                text_prospel = "NEPROSPEL"

            f.write(f"{jmeno}: {studijni_vysledky['prumer']} ({text_prospel})\n")
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