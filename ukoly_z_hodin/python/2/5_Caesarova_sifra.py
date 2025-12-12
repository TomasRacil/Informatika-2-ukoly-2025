from typing import Union

def sifruj(text: str, posun: Union[int, str]) -> str:
    """Caesarova sifra: posun muze byt cele cislo (kladne/záporne) nebo string predstavuji cislo."""
    try:
        shift = int(posun)
    except (TypeError, ValueError):
        raise ValueError("posun musi byt cele cislo")

    out_chars = []
    for ch in text:
        if 'a' <= ch <= 'z':
            base = ord('a')
            out_chars.append(chr((ord(ch) - base + shift) % 26 + base))
        elif 'A' <= ch <= 'Z':
            base = ord('A')
            out_chars.append(chr((ord(ch) - base + shift) % 26 + base))
        else:
            out_chars.append(ch)
    return ''.join(out_chars)

if __name__ == "__main__":

    try:
        txt = input("Text k zasifrovani: ")
        p = input("Posun (cele cislo): ")
        print("Vysledek:", sifruj(txt, p))
    except Exception as e:
        print("Chyba:", e)