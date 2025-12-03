import string

abeceda = string.ascii_lowercase   
posun = int(input("zadej klic: "))

def caesar(pismeno, shift):
    if pismeno not in abeceda:
        return pismeno  

    index = abeceda.index(pismeno)
    novy = (index + shift) % 26
    return abeceda[novy]

text = str(input("zadej onbsah sifry: "))
zasifrovany = ""

for znak in text:
    zasifrovany += caesar(znak, posun)

print(zasifrovany)
