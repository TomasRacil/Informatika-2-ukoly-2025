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
    with open(soubor, "r", encoding="utf-8") as file:
        for line in file:
            line = line.strip()
            if not line:          # přeskočí prázdné řádky
                continue

            radek = line.split(",")
            jmeno = radek[0]
            znamky = [int(z) for z in radek[1:] if z.strip() != ""]

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
    # TODO: Implementujte výpočet průměru
    if len(znamky) == 0:
        return 0.0
    else:
        prumer = sum(znamky)/len(znamky)
        return prumer


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
    # TODO: Projděte seznam studentů
    # 1. Pro každého zavolejte spocitej_prumer
    # 2. Zavolejte prospel
    # 3. Uložte do slovníku vysledky pod klíčem jména studenta
    for student in studenti:
        jmeno = student["jmeno"]
        znamky = student["znamky"]

        prumer = spocitej_prumer(znamky)
        prospel_student = prospel(prumer) 
        vysledky[jmeno] = {
            "prumer": prumer,
            "prospel": prospel_student
        }
    return vysledky


def uloz_report(vystupni_soubor: str, vysledky: dict) -> None:
    """
    Uloží výsledky do souboru ve formátu:
    Jmeno: Prumer (PROSPEL/NEPROSPEL)
    """
    # TODO: Otevřete soubor pro zápis a zapište formátované výsledky
    with open(vystupni_soubor, "w", encoding="utf-8") as soubor:
        for jmeno, informace in vysledky.items():
            prumer = informace["prumer"]
            prospel = "PROSPEL" if informace["prospel"] else "NEPROSPEL"
            
            soubor.write(f"{jmeno}: {prumer:.1f} ({prospel})\n")
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