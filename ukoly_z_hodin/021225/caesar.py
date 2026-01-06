abeceda = list("abcdefghijklmnopqrstuvwxyz")

def sifruj(text, posun):
    vysledek = "" 

    for znak in text:
        index = abeceda.index(znak)

        novy_index = (index + posun)

        if (novy_index) >= len(abeceda):
            novy_index = novy_index - len(abeceda)
        
        if (znak.isupper()):
            vysledek += abeceda[novy_index].upper()
        else:
            vysledek += abeceda[novy_index]

    return vysledek




def main():
    input_text = input("Zadejte text k zašifrování: ")

    result = sifruj(input_text, 3)

    print("Zašifrovaný text:", result)

main()