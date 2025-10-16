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
    std::ifstream file(filename);           // otevřít soubor pro čtení
    if (!file.is_open()) {                  // když se nepodaří otevřít
        return "";                          // vrať prázdný řetězec
    }
    std::stringstream buffer;               // pomocný stream
    buffer << file.rdbuf();                 // načti celý soubor do bufferu
    return buffer.str();                    // vrať obsah jako string
}

/**
 * @brief Spočítá počet všech znaků v textu.
 * @param content Text k analýze.
 * @return Počet znaků.
 */
int countCharacters(std::string content) {
    return static_cast<int>(content.size()); // délka řetězce = počet znaků
}

/**
 * @brief Spočítá počet řádků v textu.
 * @param content Text k analýze.
 * @return Počet řádků.
 */
int countLines(std::string content) {
    if (content.empty()) return 0;          // prázdný text => 0 řádků
    int lines = 0;
    for (char c : content) {                // projdi všechny znaky
        if (c == '\n') {                    // když narazíš na konec řádku
            lines++;                        // přičti řádek
        }
    }
    if (content.back() != '\n') {           // pokud poslední znak není '\n'
        lines++;                            // započítej poslední řádek
    }
    return lines;
}

/**
 * @brief Spočítá počet slov v textu.
 * @param content Text k analýze.
 * @return Počet slov.
 */
int countWords(std::string content) {
    std::stringstream ss(content);          // udělej stream z textu
    std::string word;
    int count = 0;
    while (ss >> word) {                    // čti po „slovech“ (oddělených bílými znaky)
        count++;
    }
    return count;
}

/**
 * @brief Spočítá počet samohlásek (a, e, i, o, u) v textu.
 * @param content Text k analýze.
 * @return Počet samohlásek.
 */
int countVowels(std::string content) {
    int vowels = 0;
    for (char ch : content) {                                   // projdi každý znak
        unsigned char uch = static_cast<unsigned char>(ch);     // bezpečný převod
        char low = static_cast<char>(std::tolower(uch));        // na malé písmeno
        if (low == 'a' || low == 'e' || low == 'i'              // počítej a,e,i,o,u
         || low == 'o' || low == 'u') {
            vowels++;
        }
    }
    return vowels;
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


