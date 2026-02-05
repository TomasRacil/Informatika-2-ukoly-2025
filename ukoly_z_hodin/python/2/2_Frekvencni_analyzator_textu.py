from typing import Dict

def spocitej_znaky(text: str) -> Dict[str, int]:
    """
    Vrátí slovník: znak -> počet výskytů.
    Malá/velká písmena nerozlišujeme, mezery a další bílé znaky ignorujeme.
    """
    counts: Dict[str, int] = {}
    for ch in text.lower():
        if ch.isspace():  # ignorovat mezery a jiné bílé znaky
            continue
        counts[ch] = counts.get(ch, 0) + 1
    return counts

if __name__ == "__main__":
    s = input("Zadejte text pro analýzu: ")
    result = spocitej_znaky(s)
    # vytiskneme seřazeně podle znaku pro přehlednost
    for ch in sorted(result):
        print(f"'{ch}': {result[ch]}")