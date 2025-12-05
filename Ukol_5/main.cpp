#include <iostream>
#include <vector>
#include <memory>
#include "valecnik.h"
#include "mag.h"

#ifndef __TEST__

int main()
{
    std::cout << "=== RPG ARENA ===" << std::endl;

    // Vytvorime instanci Valecnika a Maga
    Valecnik conan("Conan", 100, 15, 5); // 100 HP, 15 DMG, 5 Armor
    Mag gandalf("Gandalf", 70, 20, 25);  // 70 HP, 20 DMG (zaklad), 25 Mana

    conan.vypisInfo();
    gandalf.vypisInfo();

    std::cout << "\n--- Souboj zacina ---\n"
              << std::endl;

    int kolo = 1;
    while (conan.jeZiva() && gandalf.jeZiva())
    {
        std::cout << "Kolo " << kolo << ":" << std::endl;

        conan.utok(gandalf);
        if (!gandalf.jeZiva())
            break;

        gandalf.utok(conan);

        std::cout << "Stav po kole " << kolo << ":" << std::endl;
        conan.vypisInfo();
        gandalf.vypisInfo();
        std::cout << "-----------------------" << std::endl;
        kolo++;
    }

    std::cout << "\n=== KONEC HRY ===" << std::endl;
    if (conan.jeZiva())
    {
        std::cout << "Vitez: " << conan.getJmeno() << std::endl;
    }
    else
    {
        std::cout << "Vitez: " << gandalf.getJmeno() << std::endl;
    }

    return 0;
}

#endif