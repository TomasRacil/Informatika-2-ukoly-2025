#include <iostream>

int main() {
  double pesos;
  double reais;
  double soles;
  double dollars;

  std::cout << "Vložte množství Kolumbijských Pesos: ";
  std::cin >> pesos;

  std::cout << "Vložte množství Kolumbijských Reais: ";
  std::cin >> reais;

  std::cout << "Vložte množství Kolumbijských Soles: ";
  std::cin >> soles;

// Pesos conversion rate: 0.00032
// Reais conversion rate: 0.27
// Soles conversion rate: 0.3

dollars = (0.00032 * pesos) + (0.27 * reais) + (0.3 * soles);

std::cout << "Hodnota v US dollarech činní = $" << dollars << "\n"; 

}