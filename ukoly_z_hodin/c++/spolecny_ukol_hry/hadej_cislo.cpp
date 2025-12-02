#include <iostream>
#include <cstdlib>

int main(){
    // Hádej číslo
    
    //int number;
    int guess;
    
    std::cout << "Vítej ve hře Hádej číslo!\n";
    std::cout << "Myslím si číslo mezi 1 a 10. Zkus to uhodnout: ";
    std::cin >> guess;

    srand(time(NULL));
    int number = std::rand() % 10;
  
  //std::cout << answer;

  if (number == 0) {

    number = 1;

  }
  else if (number == 1) {

    number = 2;

  }
  else if (number == 2) {

    number = 3;

  }
  else if (number == 3) {

    number = 4;

  }
  else if (number == 4) {

    number = 5;

  }
  else if (number == 5) {

    number = 6;

  }
  else if (number == 6) {

    number = 7;

  }
  else if (number == 7) {

    number = 8;

  }
  else if (number == 8) {

    number = 9;

  }
  else {
  
  number = 10;
  
  }

    if(guess == number){
        std::cout << "Gratuluji! Uhodl jsi mé číslo.\n";
    } else {
        std::cout << "Špatně! Moje číslo bylo " << number << ".\n";
    }

    return 0;
}