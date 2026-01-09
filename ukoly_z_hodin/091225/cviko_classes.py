

class Uzivatel:
    def __init__(self, jmeno):
        self.jmeno = jmeno

class Admin(Uzivatel):
    def __init__(self, jmeno, prava):
        super().__init__(jmeno)
        self.prava = prava

    def smaz_databazi(self):
        if (self.prava == "full-access"):
            print("Removing database")

def main():
    muj_uzivatel = Uzivatel("hi")

    admin = Admin(muj_uzivatel, "full-access")

    print(admin.prava)

    admin.smaz_databazi()

if (__name__ == "__main__"):
    main()