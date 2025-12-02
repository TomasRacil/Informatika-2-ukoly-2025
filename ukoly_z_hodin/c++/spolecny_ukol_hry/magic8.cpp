#include <iostream>
#include <cstdlib>

int main() {

  // Your future is here

  std::cout << "MAGIC 8-BALL:\n\n";

  srand(time(NULL));

  int answer = std::rand() % 10;
  
  //std::cout << answer;

  if (answer == 0) {

    std::cout << "Je to jisté.\n";

  }
  else if (answer == 1) {

    std::cout << "Je to rozhodně tak.\n";

  }
  else if (answer == 2) {

    std::cout << "Bez pochyby.\n";

  }
  else if (answer == 3) {

    std::cout << "Ano - určitě.\n";

  }
  else if (answer == 4) {

    std::cout << "Můžeš se na to spolehnout.\n";

  }
  else if (answer == 5) {

    std::cout << "Jak to vidím já, ano.\n";

  }
  else if (answer == 6) {

    std::cout << "Nejspíš.\n";

  }
  else if (answer == 7) {

    std::cout << "Vypadá to dobře.\n";

  }
  else if (answer == 8) {

    std::cout << "Ano.\n";

  }
  else {
  
  std::cout << "Velmi pochybné.\n";
  
  }


}