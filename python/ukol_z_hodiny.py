import functools
import csv
import logging


logging.basicConfig(  
    level=logging.INFO,  # Loguj vše od INFO výše (DEBUG se ignoruje)  
    filename='python/app.log',  # Ulož do souboru  
    format='%(asctime)s - %(levelname)s - %(message)s' # Přidej čas  
)

logging.info("start programu")
def log_operace(func):
    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        print(f"[LOG] Volána metoda '{func.__name__}' "
              f"s argumenty: {args[1:] if args else ''} {kwargs if kwargs else ''}")
        return func(*args, **kwargs)
    return wrapper


class Polozka:
    def __init__(self, nazev: str, cena: float, pocet: int):
        self.nazev = nazev
        self.cena = cena
        self.pocet = pocet

    def __str__(self):
        return f"{self.nazev} {self.cena} Kč ({self.pocet} ks)"

    def __repr__(self):
        logging.info(f"Polozka('{self.nazev}', {self.cena}, {self.pocet})")
        return f"Polozka('{self.nazev}', {self.cena}, {self.pocet})"

    def __eq__(self, other):
        return isinstance(other, Polozka) and \
               self.nazev == other.nazev and self.cena == other.cena

    def __add__(self, other):
        if not isinstance(other, Polozka):
            logging.error("Lze sčítat pouze dvě položky.")
        if self.nazev != other.nazev or self.cena != other.cena:
            logging.error("Nelze sčítat různé položky.")
        return Polozka(self.nazev, self.cena, self.pocet + other.pocet)


class Sklad:
    def __init__(self):
        self._polozky = {}   # správný atribut!

    def __len__(self):
        return sum(p.pocet for p in self._polozky.values())

    def __getitem__(self, nazev):
        return self._polozky.get(nazev, None)

    @log_operace
    def pridej_polozku(self, polozka: Polozka):
        if polozka.nazev in self._polozky:
            self._polozky[polozka.nazev] = self._polozky[polozka.nazev] + polozka
        else:
            self._polozky[polozka.nazev] = polozka

    @log_operace
    def odeber_polozku(self, nazev: str, pocet: int):
        if nazev not in self._polozky:
            logging.error(f"Položka '{nazev}' není ve skladu.")

        pol = self._polozky[nazev]

        if pocet > pol.pocet:
            logging.error(f"Nedostatek zboží '{nazev}': požadováno {pocet}, dostupné {pol.pocet}")

        pol.pocet -= pocet

        if pol.pocet == 0:
            del self._polozky[nazev]

    # -------------------------------
    # Uložení / načtení do CSV
    # -------------------------------

    def uloz_do_csv(self, filename):
        with open(filename, "w", newline="", encoding="utf-8") as f:
            w = csv.writer(f)
            w.writerow(["nazev", "cena", "pocet"])
            for p in self._polozky.values():
                w.writerow([p.nazev, p.cena, p.pocet])

    @staticmethod
    def nacti_z_csv(filename):
        sklad = Sklad()
        with open(filename, "r", encoding="utf-8") as f:
            r = csv.DictReader(f)
            for row in r:
                p = Polozka(row["nazev"], float(row["cena"]), int(row["pocet"]))
                sklad.pridej_polozku(p)
        return sklad


# -------------------------------
# TEST
# -------------------------------
def main():
    jablka = Polozka("Jablko", 10, 50)
    dalsi_jablka = Polozka("Jablko", 10, 20)
    hrusky = Polozka("Hruška", 15, 30)

    print("Test sčítání:", jablka + dalsi_jablka)

    sklad = Sklad()
    sklad.pridej_polozku(jablka)
    sklad.pridej_polozku(dalsi_jablka)
    sklad.pridej_polozku(hrusky)

    print("Hruška ze skladu:", sklad["Hruška"])
    print("Celkem kusů:", len(sklad))

    sklad.uloz_do_csv("sklad_data.csv")
    logging.info("ulozeno do csv")

    novy = Sklad.nacti_z_csv("sklad_data.csv")
    print("Načteno ks zboží:", len(novy))
    logging.info("program se ukoncil spravne")


if __name__ == "__main__":
    main()