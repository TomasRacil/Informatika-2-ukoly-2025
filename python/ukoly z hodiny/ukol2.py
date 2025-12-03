def spocitej_znaky(text):
    text = text.lower()      # vše na malá písmena
    vysledky = {}            # slovník pro počty znaků

    for znak in text:
        if znak == " ":      
            continue
        if znak not in vysledky:
            vysledky[znak] = 1
        else:
            vysledky[znak] += 1

    return vysledky

print(spocitej_znaky(input("zadej slova: ")))