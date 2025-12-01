from os.path import join, dirname, realpath

def load_file(cesta:str=join(dirname(realpath(__file__)), "data.txt"))->str:
    with open(cesta,"r", encoding="utf-8") as f:
        return f.read()

"""
def prepare_file(soubor:str)->list[str,dict]:
    vystup = soubor.split('\n\n')
    vystup[1] = {radek.split('->')[0].strip():radek.split('->')[1].strip() for radek in vystup[1].split('\n')}
    return tuple vystup
"""

def main():
    print(load_file)

if __name__ == "__main__":
    main()