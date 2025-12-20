from os.path import join, dirname, realpath

class Lod:
    def __init__(self, filename:str):
        self.__path:str = join(dirname(realpath(__file__)),filename)
        self.x:int = 0
        self.y:int = 0
        self.stupne:int = 90
    
    def stupne_na_smer(self)->str:
        match self.stupne:
            case 0:
                return 'N'
            case 90:
                return 'E'
            case 180:
                return 'S'
            case 270:
                return 'W'
    
    def navigate(self):
        with open(self.__path, 'r', encoding='utf-8') as f:
            for line in f:
                line = line.strip()
                if len(line)>0:
                    prikaz = line[0]
                    hodnota = int(line[1:])
                    if(prikaz=='F'): self.posun_dopredu(hodnota)
                    elif prikaz == 'L' or prikaz == 'R': self. zmen_smer(prikaz, hodnota)
                    else: self.posun_smerem(prikaz, hodnota)
    
    def zmen_smer(self, smer:str, stupne:int)->None:
        match smer:
            case 'R':
                self.stupne = (self.stupne + stupne) % 360
            case 'L':
                self.stupne = (self.stupne - stupne) % 360
                if (self.stupne < 0):
                    self.stupne += 360
            
            
    def posun_dopredu(self, kroky:int )->None:
        self.posun_smerem(self.stupne_na_smer(), kroky)
        
    def posun_smerem(self, smer:str, kroky:int):
        match smer:
            case 'N':
                self.y += kroky
            case 'S':
                self.y -= kroky
            case 'E':
                self.x += kroky
            case 'W':
                self.x -= kroky
        
        
    def vypis_pozici(self)->None:
        print(f"Pozice x: {self.x}, pozice y: {self.y}, smer: {self.stupne}, manhatnovska vzdalenost: {abs(self.x) + abs(self.y)}")
        
def main():
    lod = Lod("data.txt")
    lod.navigate()
    lod.vypis_pozici()

if __name__ == "__main__":
    main()