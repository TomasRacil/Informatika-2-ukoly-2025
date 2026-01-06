from ast import Dict, List
import os
from typing import Any

def nacti_data(soubor: str) -> list:
    """
    Načte data ze souboru.
    Vrací seznam slovníků ve formátu: [{'jmeno': 'Jan', 'znamky': [1, 2]}, ...]
    """
    data: List[Dict[str, Any]] = []
    try:
        with open(soubor, "r", encoding="utf-8") as f:
            for line in f:
                line = line.strip()
                if not line:
                    continue
                parts = [p.strip() for p in line.split(",")]
                if not parts:
                    continue
                jmeno = parts[0]
                znamky: List[int] = []
                for token in parts[1:]:
                    if not token:
                        continue
                    try:
                        znamka = int(token)
                        znamky.append(znamka)
                    except ValueError:
                        # ignorovat nečíselné hodnoty
                        continue
                data.append({"jmeno": jmeno, "znamky": znamky})
    except FileNotFoundError:
        # necháváme volajícího aby ošetřil neexistující soubor; vrátíme prázdný seznam
        return []
    return data


def spocitej_prumer(znamky: list) -> float:
    """
    Vypočítá aritmetický průměr ze seznamu známek.
    Pokud je seznam prázdný, vrací 0.0.
    """
    if not znamky:
        return 0.0
    try:
        prumer = sum(znamky) / len(znamky)
    except Exception:
        return 0.0
    return round(float(prumer), 2)


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
    vysledky: Dict[str, Dict[str, Any]] = {}
    for s in studenti:
        jmeno = s.get("jmeno", "")
        znamky = s.get("znamky", [])
        prumer = spocitej_prumer(znamky)
        prospech = prospel(prumer)
        vysledky[jmeno] = {"prumer": prumer, "prospel": prospech}
    return vysledky


def uloz_report(vystupni_soubor: str, vysledky: dict) -> None:
    """
    Uloží výsledky do souboru ve formátu:
    Jmeno: Prumer (PROSPEL/NEPROSPEL)
    """
    with open(vystupni_soubor, "w", encoding="utf-8") as f:
        for jmeno in sorted(vysledky.keys(), key=lambda x: x.lower()):
            data = vysledky[jmeno]
            prumer = data.get("prumer", 0.0)
            prospech = data.get("prospel", False)
            status = "PROSPEL" if prospech else "NEPROSPEL"
            f.write(f"{jmeno}: {prumer:.2f} ({status})\n")


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
