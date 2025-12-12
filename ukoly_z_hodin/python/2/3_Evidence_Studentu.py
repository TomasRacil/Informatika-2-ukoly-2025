# evidence studentu

from typing import List, Dict, Optional

studenti: List[Dict[str, object]] = []

def pridej_studenta(jmeno: str, znamky: List[float]) -> None:
    """Přidá studenta ve formátu {'jmeno': ..., 'znamky': [...]}."""
    studenti.append({"jmeno": jmeno, "znamky": list(znamky)})

def _prumer(znamky: List[float]) -> float:
    return sum(znamky) / len(znamky) if znamky else float("inf")

def nejlepsi_student(seznam_studentu: List[Dict[str, object]]) -> Optional[Dict[str, object]]:
    """Najde studenta s nejnižším průměrem známek a vytiskne jeho jméno a průměr."""
    if not seznam_studentu:
        print("Seznam studentů je prázdný.")
        return None
    best = min(seznam_studentu, key=lambda s: _prumer(s["znamky"]))
    avg = _prumer(best["znamky"])
    print(f"Nejlepší student: {best['jmeno']} (průměr {avg:.2f})")
    return best

# --- přidejte/úpravte studenty zde ---
pridej_studenta("Jan Novák", [1, 2, 1])
pridej_studenta("Petra Svobodová", [2, 2, 1, 3])
pridej_studenta("Karel Dvořák", [3, 2, 2])
# můžete přidat další: pridej_studenta("Jméno", [znamky])

if __name__ == "__main__":
    print("Seznam studentů a jejich průměry:")
    for s in studenti:
        avg = _prumer(s["znamky"])
        print(f" - {s['jmeno']}: {avg:.2f} ({s['znamky']})")
    print()
    nejlepsi_student(studenti)