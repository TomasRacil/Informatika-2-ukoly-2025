"""def vypis_statistiku(seznam):
    if not seznam:
        print("Seznam je prázdný.")
        return

    nejmensi = min(seznam)
    nejvetsi = max(seznam)
    soucet = nejmensi + nejvetsi
    pocet_sudych = sum(1 for cislo in seznam if cislo % 2 == 0)
    prumer = sum(seznam) / len(seznam)

    print("Statistika:")
    print(f"Součet nejmenšího a největšího čísla: {soucet}")
    print(f"Počet sudých čísel: {pocet_sudych}")
    print(f"Průměr čísel: {prumer:.2f}")

cisla = []
while True:
    vstup = input("Zadej číslo (nebo 'stop' pro ukončení): ")
    if vstup.lower() == 'stop':
        break
    try:
        cislo = int(vstup)
        cisla.append(cislo)
    except ValueError:
        print("Prosím, zadej platné číslo.")
vypis_statistiku(cisla)"""

"""def spocitej_znaky(text):
    text = text.lower()
    vysledky = {}

    for znak in text:
        if znak == " ":
            continue
        if znak in vysledky:
            vysledky[znak] += 1
        else:
            vysledky[znak] = 1
    return vysledky

vstup = input("Zadej text: ")
vysledek = spocitej_znaky(vstup)
print(f"Počet výskytů jednotlivých znaků: {vysledek}")"""

"""studenti = []

def pridej_studenta(jmeno, znamky):
    student = {'jmeno': jmeno, 'znamky': znamky}
    studenti.append(student)

def nejlepsi_student(studenti):
    if not studenti:
        return None
    
    nejlepsi = None
    nejlepsi_prumer = float("inf")
    for student in studenti:
        prumer = sum(student['znamky']) / len(student['znamky'])
        if prumer < nejlepsi_prumer:
            nejlepsi_prumer = prumer
            nejlepsi = student

    print(f"Nejlepší student je {nejlepsi['jmeno']} s průměrem {nejlepsi_prumer:.2f}")

pridej_studenta("Jan", [1, 2, 1, 3])
pridej_studenta("Eva", [2, 2, 2, 2])
pridej_studenta("Petr", [3, 2, 1, 3])
nejlepsi_student(studenti)"""

"""with open("system.log", "w", encoding="utf-8") as f:
    f.write("INFO: Systém byl spuštěn\n")
    f.write("WARNING: Nízké místo na disku\n")
    f.write("ERROR: SMOLIK\n")
    f.write("INFO: Kontrola proběhla úspěšně\n")
    f.write("ERROR: PACHOLIK\n")

with open("system.log", "r", encoding="utf-8") as f:
    radky = f.readlines()

error = [r for r in radky if "ERROR" in r]

with open("errors.log", "w", encoding="utf-8") as f:
    f.writelines(error)"""

def sifruj (text, posun):
    vysledek = ""
    for znak in text:
        if "a" <= znak <= "z":
            novy_znak = chr((ord(znak) - ord("a") + posun) % 26 + ord("a"))
            vysledek += novy_znak
        elif "A" <= znak <= "Z":
            novy_znak = chr((ord(znak) - ord("A") + posun) % 26 + ord("A"))
            vysledek += novy_znak
        else:
            vysledek += znak
    return vysledek

print(sifruj("Ahoj, světe!", 3))




