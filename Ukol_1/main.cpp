#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>
#include <vector>

// --- Funkce k implementaci ---

/**
 * @brief Načte obsah souboru do řetězce.
 * @param filename Název souboru.
 * @return Obsah souboru jako std::string.
 */
std::string getFileContent(std::string filename) {
    // TODO: Doplňte kód pro načtení souboru.
    // Nápověda: Použijte std::ifstream a std::stringstream.
    // V případě, že se soubor nepodaří otevřít, vraťte prázdný řetězec "".
    std::stringstream obsah;
    std::string nacteni;
    std::ifstream soubor(filename);

    if (!soubor.is_open()) {
        return "";
    }

    obsah << soubor.rdbuf();
    return obsah.str();
}

/**
 * @brief Spočítá počet všech znaků v textu.
 * @param content Text k analýze.
 * @return Počet znaků.
 */
int countCharacters(std::string content) {
    // TODO: Doplňte kód pro spočítání znaků.
    int i = 0;

    for (char c : content) {
        i++;
    }
    return i;
}

/**
 * @brief Spočítá počet řádků v textu.
 * @param content Text k analýze.
 * @return Počet řádků.
 */
int countLines(std::string content) {
    // TODO: Doplňte kód pro spočítání řádků.
    // Nezapomeňte, že i neprázdný soubor bez znaku nového řádku má 1 řádek.
    int pocetRadku = 0;
    std::stringstream obsah(content);
    std::string radek;

    while (getline(obsah, radek)) {
        pocetRadku++;
    }

    return pocetRadku;
}

/**
 * @brief Spočítá počet slov v textu.
 * @param content Text k analýze.
 * @return Počet slov.
 */
int countWords(std::string content) {
    // TODO: Doplňte kód pro spočítání slov.
    // Nápověda: Můžete použít std::stringstream pro snadné oddělení slov.

    std::stringstream obsah(content);
    int i = 0;
    std::string slovo;

    while (obsah >> slovo) {
        i++;
    }

    return i;
}

/**
 * @brief Spočítá počet samohlásek (a, e, i, o, u) v textu.
 * @param content Text k analýze.
 * @return Počet samohlásek.
 */
int countVowels(std::string content) {
    // TODO: Doplňte kód pro spočítání samohlásek.
    // Nápověda: Procházejte řetězec znak po znaku a použijte tolower() pro zjednodušení.

    int samohlasky = 0;

    for (char c : content) {
        if (tolower(c) == 'a') {
            samohlasky++;
        }
        else if (tolower(c) == 'e') {
            samohlasky++;
        }
        else if (tolower(c) == 'i') {
            samohlasky++;
        }
        else if (tolower(c) == 'o') {
            samohlasky++;
        }
        else if (tolower(c) == 'u') {
            samohlasky++;
        }
    }

    return samohlasky;
}


// --- Hlavní program (neměnit) ---

#ifndef __TEST__
int main() {
    std::string filename = "text_k_analyze.txt";
    std::string content = getFileContent(filename);

    if (content.empty() && filename == "text_k_analyze.txt") {
         std::cerr << "Chyba: Soubor je prázdný nebo se nepodařilo ho otevřít." << std::endl;
         return 1;
    }

    // Volání jednotlivých analytických funkcí
    int pocetZnaku = countCharacters(content);
    int pocetRadku = countLines(content);
    int pocetSlov = countWords(content);
    int pocetSamohlasek = countVowels(content);

    // Výpis výsledků
    std::cout << "--- Vysledky analyzy souboru ---" << std::endl;
    std::cout << "Pocet znaku: " << pocetZnaku << std::endl;
    std::cout << "Pocet radku: " << pocetRadku << std::endl;
    std::cout << "Pocet slov: " << pocetSlov << std::endl;
    std::cout << "Pocet samohlasek: " << pocetSamohlasek << std::endl;

    return 0;
}
#endif // __TEST__

