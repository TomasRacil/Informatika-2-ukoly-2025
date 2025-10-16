#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>

using namespace std;
// --- Funkce k implementaci ---

/**
 * @brief Načte obsah souboru do řetězce.
 * @param filename Název souboru.
 * @return Obsah souboru jako std::string.
 */
std::string getFileContent(std::string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        return "";
    }
    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

/**
 * @brief Spočítá počet všech znaků v textu.
 * @param content Text k analýze.
 * @return Počet znaků.
 */
int countCharacters(std::string content) {
    return static_cast<int>(content.size());
}

/**
 * @brief Spočítá počet řádků v textu.
 * @param content Text k analýze.
 * @return Počet řádků.
 */
int countLines(std::string content) {
    if (content.empty()) return 0;

    int radky = 0;
    for (char c : content) {
        if (c == '\n') {
            radky++;
        }
    }
    
    if (content.back() != '\n') {
        radky++;
    }
    return radky;
}

/**
 * @brief Spočítá počet slov v textu.
 * @param content Text k analýze.
 * @return Počet slov.
 */
int countWords(std::string content) {
    stringstream strstring(content);
    string slovo;
    int count = 0;
    while (strstring >> slovo) {
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
    int pocet = 0;
    for (char c : content) {
        char male_pismen = static_cast<char>(tolower(c)); 
        if (male_pismen == 'a' || male_pismen == 'e' || male_pismen == 'i' || male_pismen == 'o' || male_pismen == 'u') {
            pocet++;
        }
    }
    return pocet;
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

