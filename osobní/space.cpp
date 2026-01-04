#include <iostream>

int main() {

  double mercury = 0.38;
  double venus = 0.91;
  double mars = 0.38;
  double jupiter = 2.34;
  double saturn = 1.06;
  double uranus = 0.92;
  double neptune = 1.19;
  int planet;
  int vaha;
  int finalnivaha;

  std::cout << "Tabulka planet:\n1. Mercury\n2. Venus\n3. Mars\n4. Jupiter\n5. Saturn\n6. Uranus\n7. Neptune\n";

  std::cout << "\nNa jaké planetě si přeješ zápasit? (vyber číslo): ";
  std::cin >> planet;

  std::cout << "\nKolik vážíš v kg: ";
  std::cin >> vaha;

  if (planet == 1) {

    finalnivaha = vaha * mercury;

  } else if (planet == 2) {

    finalnivaha = vaha * venus;

  } else if (planet == 3) {

    finalnivaha = vaha * mars;

  } else if (planet == 4) {

    finalnivaha = vaha * jupiter;

  } else if (planet == 5) {

    finalnivaha = vaha * saturn;

  } else if (planet == 6) {

    finalnivaha = vaha * uranus;

  } else if (planet == 7) {

    finalnivaha = vaha * neptune;

  }

  std::cout << "\nTvoje váha bude: " << finalnivaha << "\n";


  
  
  
  
  
  
  
  
  
  
  
  
}