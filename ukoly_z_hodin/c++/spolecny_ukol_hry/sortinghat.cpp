#include <iostream>

int main() {

  // The magic starts here

  int gryffindor = 0;
  int hufflepuff = 0;
  int ravenclaw = 0;
  int slytherin = 0;

  int answer1;
  int answer2;
  int answer3;
  int answer4;

  std::cout << "===================================\n";
  std::cout << "Rozřazovací kvíz moudrého klobouku!\n";
  std::cout << "===================================\n\n";

  std::cout << "Q1) Až umřu, chci, aby si mě lidé pamatovali jako:\n\n 1) Dobrotivého\n 2) Velkého\n 3) Chytrého\n 4) Odvážného\n";

  std::cout << "Napiš svou odpověď (1-4): ";
  std::cin >> answer1;

  if (answer1 == 1) {
    hufflepuff++;
  } else if (answer1 == 2) {
    slytherin++;
  } else if (answer1 == 3) {
    ravenclaw++;
  } else if (answer1 == 4) {
    gryffindor++;
  } else {
    std::cout << "Neplatný vstup\n";
  }

  std::cout << "\nQ2) Svítání nebo soumrak?\n\n 1) Svítání\n 2) Soumrak\n";

  std::cout << "Napiš svou odpověď (1-2): ";
  std::cin >> answer2;

  if (answer2 == 1) {
    gryffindor++;
    ravenclaw++;
  } else if (answer2 == 2) {
    hufflepuff++;
    slytherin++;
  } else {
    std::cout << "Neplatný vstup\n";
  }

  std::cout << "\nQ3) Který druh nástroje je pro vaše ucho nejlepší?\n\n 1) Housel\n 2) Trumpeta\n 3) Piano\n 4) Bubny\n";

  std::cout << "Napiš svou odpověď (1-4): ";
  std::cin >> answer3;

  if (answer3 == 1) {
    slytherin++;
  } else if (answer3 == 2) {
    hufflepuff++;
  } else if (answer3 == 3) {
    ravenclaw++;
  } else if (answer3 == 4) {
    gryffindor++;
  } else {
    std::cout << "Neplatný vstup\n";
  }

  std::cout << "\nQ4) Která cesta tě láká nejvíce?\n\n 1) Široká, slunná travnatá cesta\n 2) Úzká, temná ulička osvětlená lucernami\n 3) Klikatá, listím posetá stezka lesem\n 4) Lemovaná dlážděná ulice (starobylými budovami)\n";

  std::cout << "Napiš svou odpověď (1-4): ";
  std::cin >> answer4;

  if (answer4 == 1) {
    hufflepuff++;
  } else if (answer4 == 2) {
    slytherin++;
  } else if (answer4 == 3) {
    gryffindor++;
  } else if (answer4 == 4) {
    ravenclaw++;
  } else {
    std::cout << "Neplatný vstup\n";
  }

  std::cout << "\nGratulujeme k zařazení do... ";

  int max = 0;
  std::string house;

  if (gryffindor > max) {
  
  max = gryffindor;
  house = "Nebelvír";
  
}

if (hufflepuff > max) {

  max = hufflepuff;
  house = "Mrzimor";
  
}

if (ravenclaw > max) {
  
  max = ravenclaw;
  house = "Havraspár";
  
}

if (slytherin > max) {
  
  max = slytherin;
  house = "Zmijozel";
  
}

std::cout << house << "!\n";

return 0;


  
}
