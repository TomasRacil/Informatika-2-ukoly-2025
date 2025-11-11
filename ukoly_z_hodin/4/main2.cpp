// PREHOZENI CISEL
#include <iostream>

int main() {

int a = 0;
int b = 0;
int c = 0;
int d = 0;

std::cout << "Zadej cislo a: ";
std::cin >> a;
std::cout << "Zadej cislo b: ";
std::cin >> b;

std::cout << "Cislo a pred prehodenim: " << a << std::endl;
std::cout << "Cislo b pred prehodenim: " << b << std::endl;

//int temp = a;
//a = b;
//b = temp;


c = a + c; // moje cislo a + 0 = moje cislo c. Proste C = A
d = b + d; // moje cislo b + 0 = moje cislo d  Proste D = B
a = d; 
b = c;


std::cout << "Cislo a po prehodeni: " << a << std::endl;
std::cout << "Cislo b po prehodeni: " << b << std::endl;




}