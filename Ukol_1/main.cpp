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
 * @return Obsah souboru jako string.
 */
std::string getFileContent(std::string filename) {
    std::ifstream in(filename, std::ios::in | std::ios::binary);
    if (!in) {
        return "";
    }
    std::ostringstream ss;
    ss << in.rdbuf();
    return ss.str();
}

/**
 * @brief Spočítá počet všech znaků v textu.
 * @param content Text k analýze.
 * @return Počet znaků.
 */
int countCharacters(std::string content) {
    // Počet všech znaků včetně mezer a nových řádků
    return static_cast<int>(content.size());
}

/**
 * @brief Spočítá počet řádků v textu.
 * @param content Text k analýze.
 * @return Počet řádků.
 */
int countLines(std::string content) {
    if (content.empty()) return 0;
    int lines = 0;
    for (char c : content) if (c == '\n') ++lines;
    // Pokud poslední znak není newline, pak je potřeba přičíst poslední řádek
    if (content.back() != '\n') ++lines;
    return lines;
}

/**
 * @brief Spočítá počet slov v textu.
 * @param content Text k analýze.
 * @return Počet slov.
 */
int countWords(std::string content) {
    std::istringstream iss(content);
    std::string word;
    int count = 0;
    while (iss >> word) ++count;
    return count;
}

/**
 * @brief Spočítá počet samohlásek (a, e, i, o, u) v textu.
 * @param content Text k analýze.
 * @return Počet samohlásek.
 */
int countVowels(std::string content) {
    int count = 0;
    for (unsigned char ch : content) {
        char c = static_cast<char>(std::tolower(ch));
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') ++count;
    }
    return count;
}

// --- Hlavní program (neměnit) ---

#ifndef __TEST__
int main() {
    string filename = "text_k_analyze.txt";
    string content = getFileContent(filename);

    if (content.empty() && filename == "text_k_analyze.txt") {
         cerr << "Chyba: Soubor je prázdný nebo se nepodařilo ho otevřít." << endl;
         return 1;
    }

    // Volání jednotlivých analytických funkcí
    int pocetZnaku = countCharacters(content);
    int pocetRadku = countLines(content);
    int pocetSlov = countWords(content);
    int pocetSamohlasek = countVowels(content);

    // Výpis výsledků
    cout << "--- Vysledky analyzy souboru ---" << endl;
    cout << "Pocet znaku: " << pocetZnaku << endl;
    cout << "Pocet radku: " << pocetRadku << endl;
    cout << "Pocet slov: " << pocetSlov << endl;
    cout << "Pocet samohlasek: " << pocetSamohlasek << endl;

    return 0;
}
#endif // __TEST__