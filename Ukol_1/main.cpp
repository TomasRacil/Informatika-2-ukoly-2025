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
std::string getFileContent(const std::string filename) {
    std::ifstream soubor("text_k_analyze.txt");
    if (!soubor.is_open())
    {
        std::cout << "Soubor se nepodařilo otevřít!" << std::endl;
        return "";
    }
    std::ostringstream ss;
    ss << soubor.rdbuf();
    return ss.str();
}
/**
 * @brief Spočítá počet všech znaků v textu.
 * @param content Text k analýze.
 * @return Počet znaků.
 */
int countCharacters(const std::string content) {
    return content.size();
}

/**
 * @brief Spočítá počet řádků v textu.
 * @param content Text k analýze.
 * @return Počet řádků.
 */
int countLines(const std::string content) {
    int countLines = 0;
    std::istringstream iss(content);
    std::string line;
    while (std::getline(iss, line)) {
        countLines++;
    }
    return countLines;
}
/**
 * @brief Spočítá počet slov v textu.
 * @param content Text k analýze.
 * @return Počet slov.
 */
int countWords(const std::string content) {
    int countWords = 0;
    std::istringstream iss(content);
    std::string soubor;
    while (iss >> soubor) {
        countWords++;
    }
    return countWords;
}

/**
 * @brief Spočítá počet samohlásek (a, e, i, o, u) v textu.
 * @param content Text k analýze.
 * @return Počet samohlásek.
 */
int countVowels(std::string content) {
    int countVowels = 0;
    for (char c : content) 
    {
        c = std::tolower(static_cast<unsigned char>(c));
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') 
        {
            countVowels++;
        }
    }
        return countVowels;
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

