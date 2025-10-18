#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>

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
    std::ifstream file(filename);
    if (!file.is_open()) {
        return "";
    }
    std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();;
}

/**
 * @brief Spočítá počet všech znaků v textu.
 * @param content Text k analýze.
 * @return Počet znaků.
 */
int countCharacters(std::string content) {
    // TODO: Doplňte kód pro spočítání znaků.
    return static_cast<int>(content.size());
}

/**
 * @brief Spočítá počet řádků v textu.
 * @param content Text k analýze.
 * @return Počet řádků.
 */
int countLines(std::string content) {
    // TODO: Doplňte kód pro spočítání řádků.
    // Nezapomeňte, že i neprázdný soubor bez znaku nového řádku má 1 řádek.
    if (content.empty()) {
        return 0;
    }
    int pocetradku = 1; // Začínáme s 1 řádkem
    for (char c : content) {
        if (c == '\n') {
            pocetradku++;
        }
    }
    return pocetradku;
}

/**
 * @brief Spočítá počet slov v textu.
 * @param content Text k analýze.
 * @return Počet slov.
 */
int countWords(std::string content) {
    // TODO: Doplňte kód pro spočítání slov.
    // Nápověda: Můžete použít std::stringstream pro snadné oddělení slov.
    std::stringstream ss(content);
    std::string word;
    int pocetslov = 0;
    while (ss >> word) {
        pocetslov++;
    }
    return pocetslov;
}

/**
 * @brief Spočítá počet samohlásek (a, e, i, o, u) v textu.
 * @param content Text k analýze.
 * @return Počet samohlásek.
 */
int countVowels(std::string content) {
    // TODO: Doplňte kód pro spočítání samohlásek.
    // Nápověda: Procházejte řetězec znak po znaku a použijte tolower() pro zjednodušení.
    int pocetpismen = 0;
    for (char c : content) {
        char malapismena = std::tolower(static_cast<unsigned char>(c)); 
        if (malapismena == 'a' || malapismena == 'e' || malapismena == 'i' || malapismena == 'o' || malapismena == 'u') {
            pocetpismen++;
        }
    }
    return pocetpismen;
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

