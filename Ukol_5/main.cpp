#include <iostream>
#include "valecnik.h"
#include "mag.h"

#ifndef __TEST__

int main() {
    std::cout << "=== RPG ARENA ===" << std::endl;

    Valecnik conan("Conan", 100.0, 15.0, 5.0); // 100 HP, 15 DMG, 5 Armor
    Mag gandalf("Gandalf", 70.0, 20.0, 25.0);  // 70 HP, 20 DMG, 25 Mana

    conan.vypisInfo();
    gandalf.vypisInfo();

    std::cout << "\n--- Souboj zacina ---\n" << std::endl;

    int kolo = 1;
    while (conan.jeZiva() && gandalf.jeZiva()) {
        std::cout << "Kolo " << kolo << ":" << std::endl;

        // Conan útočí
        conan.utok(gandalf);
        if (!gandalf.jeZiva()) break;

        // Gandalf odpovídá
        gandalf.utok(conan);
        if (!conan.jeZiva()) break;

        std::cout << "Stav po kole " << kolo << ":" << std::endl;
        conan.vypisInfo();
        gandalf.vypisInfo();
        std::cout << "-----------------------" << std::endl;
        kolo++;
    }

    std::cout << "\n=== KONEC HRY ===" << std::endl;
    if (conan.jeZiva()) {
        std::cout << "Vitez: " << conan.getJmeno() << std::endl;
    } else {
        std::cout << "Vitez: " << gandalf.getJmeno() << std::endl;
    }

    return 0;
}

#endif
