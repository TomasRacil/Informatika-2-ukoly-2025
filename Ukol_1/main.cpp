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
    std::string result = "";
    std::ifstream stream(filename);
    if (stream.is_open())
    {
        std::string line;
        while (getline(stream, line))
        {
          result.append(line);
          result.push_back('\n');
        }
        result.pop_back();
    }

    return result;
}

/**
 * @brief Spočítá počet všech znaků v textu.
 * @param content Text k analýze.
 * @return Počet znaků.
 */
int countCharacters(std::string content) {
    // TODO: Doplňte kód pro spočítání znaků.
    int count = 0;
    for (int i = 0; i < content.length(); i++)
    {
        if(content[i] != '\0'){
            count++;
        }
    }
    return count;
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
    int lines = 0;
    std::istringstream stream(content);
    std::string line;
    while (std::getline(stream, line)) {
        lines++;
    }
    return lines > 0 ? lines : 1;
}

/**
 * @brief Spočítá počet slov v textu.
 * @param content Text k analýze.
 * @return Počet slov.
 */
int countWords(std::string content) {
   std::istringstream stream(content);
   std::string word;
   int count = 0;
   while (stream >> word) {
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
    int count = 0;
    for (char c : content) {
        if (std::tolower(c) == 'a' || std::tolower(c) == 'e' ||
            std::tolower(c) == 'i' || std::tolower(c) == 'o' ||
            std::tolower(c) == 'u') {
            count++;
        }
    }
    return count;
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

