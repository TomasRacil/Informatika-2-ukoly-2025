from os.path import join, realpath, dirname

cesta = join(dirname(realpath(__file__)), "data.txt")

with open(cesta, "r", encoding="utf-8") as f:
    for c, line in enumerate(f):
        for znak in line:
            cisla = [znak for znak in line if znak.isdigit()]
            suma += int(cisla[0] + cisla[-1]) # -1 posledni prvek
            # if znak.isdigit():
            #    print(c, line)