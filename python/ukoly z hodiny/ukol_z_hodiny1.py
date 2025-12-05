class student():

    def __init__(self, jmeno:str, rocnik:int, znamky:list[int]) -> None:
        self.jmeno:str = jmeno
        self.__rocnik:int = rocnik
        self.__znamky:list[int] = znamky

    @property
    def rocnik(self):
        return self.__rocnik
    
    @property
    def znamky(self):
        return self.__znamky
    

    @rocnik.setter
    def rocnik(self, value):
        if 1 <= value <= 5:
            self.__rocnik = value
        else:
            raise ValueError("rocniky jsou pouze 1 az 5")
        

    @znamky.setter
    def znamky(self, znamky):
        if 1<= znamky <= 5:
            self.__znamky = znamky
        else:
            raise ValueError("znamky jsou pouze od 1 do 5")


    def pridej_znamku(self, znamka:int):
        self.znamky.append(znamka)

    def prumer(self) -> float:
        return sum(self.znamky)/len(self.znamky)


def funkce():
    """
    Docstring for funkce
    """
    pass

def main():
    s1 = student("Jakub", 4, [1,2,3,4])
    s1.rocnik = 8
    print("tady je rocnik", s1.rocnik)
    #print(funkce) #vypise adresu te funkce
    #print(funkce.__doc__) #vypise ten jeji docstring
    s1.pridej_znamku(2)
    print("toto je prumer", s1.prumer())




if __name__ == "__main__":
    main()