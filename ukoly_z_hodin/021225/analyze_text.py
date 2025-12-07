def spocitej_znaky(text):
    znak_dict = {}

    for znak in text:
        znak = znak.lower()
        if znak == ' ':
            continue
        if znak in znak_dict:
            znak_dict[znak] += 1
        else:
            znak_dict[znak] = 1

    return znak_dict

def main():
    text = input("Zadejte text pro analyzu:")

    vysledek = spocitej_znaky(text)

    print(f"Pocet jednotlivych znaku: {vysledek}")

main()