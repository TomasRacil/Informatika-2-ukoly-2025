from os.path import join, dirname, realpath


def load_file(cesta: str = join(dirname(realpath(__file__)), "data.txt")) -> str:
    with open(cesta, "r", encoding="utf-8") as f:
        return f.read()


def prepare_file(soubor: str) -> tuple[str, dict]:
    vystup = soubor.split('\n\n')
    vystup[1] = {
        radek.split('->')[0].strip(): radek.split('->')[1].strip()
        for radek in vystup[1].split('\n')
        }
    return tuple(vystup)

def polymerizace(pravidla:dict, polymer:str, pocet_cyklu:int)->str:
    for _ in range(pocet_cyklu):
        rozdeleny_polymer = [polymer[i]+pravidla[polymer[i]+polymer[i+1]]+polymer[i+1] for i in range(len(polymer)-1)] 
        polymer = rozdeleny_polymer[0]+"".join([prvek[1:] for prvek in rozdeleny_polymer[1:]])
    elementy = set(polymer)
    pocty = [polymer.count(element) for element in elementy]
    return max(pocty)-min(pocty)

def main():
    vychozi_polymer, pravidla = prepare_file(load_file())
    print(polymerizace(pravidla, vychozi_polymer, 40))
    
if __name__ == "__main__":
    main()  