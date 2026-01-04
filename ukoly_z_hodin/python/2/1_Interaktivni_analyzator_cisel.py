from typing import List

def vypis_statistiku(seznam: List[float]) -> None:
    if not seznam:
        print("Žádná čísla ke zpracování.")
        return

    soucet = sum(seznam)
    nejvetsi = max(seznam)
    nejmensi = min(seznam)
    prumer = soucet / len(seznam)

    pocet_sudych = sum(1 for x in seznam if float(x).is_integer() and int(x) % 2 == 0)
    pocet_lichych = sum(1 for x in seznam if float(x).is_integer() and int(x) % 2 != 0)

    print(f"Součet: {soucet}")
    print(f"Největší: {nejvetsi}")
    print(f"Nejmenší: {nejmensi}")
    print(f"Počet sudých: {pocet_sudych}")
    print(f"Počet lichých: {pocet_lichych}")
    print(f"Průměr: {prumer}")

def main() -> None:
    seznam: List[float] = []
    print("Zadejte čísla. Napište 'stop' pro ukončení.")

    while True:
        try:
            vstup = input("Číslo nebo 'stop': ").strip()
        except EOFError:
            break
        if vstup.lower() == "stop":
            break
        if vstup == "":
            continue
        try:
            cislo = float(vstup)
        except ValueError:
            print("Neplatný vstup — zadejte prosím číslo nebo 'stop'.")
            continue
        seznam.append(cislo)

    vypis_statistiku(seznam)

if __name__ == "__main__":
    main()