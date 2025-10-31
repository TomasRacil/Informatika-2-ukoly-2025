#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>
#include <regex>

// --- Funkce k implementaci ---

/**
 * @brief Načte obsah souboru do řetězce.
 * @param filename Název souboru.
 * @return Obsah souboru jako std::string.
 */
std::string getFileContent(std::string filename)
{
    // TODO: Doplňte kód pro načtení souboru.
    // Nápověda: Použijte std::ifstream a std::stringstream.
    // V případě, že se soubor nepodaří otevřít, vraťte prázdný řetězec "".

    std::ifstream soubor(filename);

    if (!soubor || !soubor.is_open())
    {
        return "";
    }

    std::stringstream content;

    content << soubor.rdbuf();
    soubor.close();

    return content.str();
}

/**
 * @brief Spočítá počet všech znaků v textu.
 * @param content Text k analýze.
 * @return Počet znaků.
 */
int countCharacters(std::string content)
{
    // TODO: Doplňte kód pro spočítání znaků.
    int total_characters = 0;

    for (char ch : content) {
        total_characters++;
    }

    return total_characters;
}

/**
 * @brief Spočítá počet řádků v textu.
 * @param content Text k analýze.
 * @return Počet řádků.
 */
int countLines(std::string content)
{
    // TODO: Doplňte kód pro spočítání řádků.
    // Nezapomeňte, že i neprázdný soubor bez znaku nového řádku má 1 řádek.

    int lines = 0;

    // prvni radek nema znak \n
    if (!content.empty()) {
        lines++;
    }

    for (char ch : content) {
        if (ch == '\n') {
            lines++;
        }
    }

    return lines;
}

/**
 * @brief Spočítá počet slov v textu.
 * @param content Text k analýze.
 * @return Počet slov.
 */
int countWords(std::string content)
{
    // TODO: Doplňte kód pro spočítání slov.
    // Nápověda: Můžete použít std::stringstream pro snadné oddělení slov.

    std::stringstream ss(content);
    std::string words;
    int word_count = 0;

    while (ss >> words) {
        word_count++;
    }

    return word_count;
}

/**
 * @brief Spočítá počet samohlásek (a, e, i, o, u) v textu.
 * @param content Text k analýze.
 * @return Počet samohlásek.
 */
int countVowels(std::string content)
{
    // TODO: Doplňte kód pro spočítání samohlásek.
    // Nápověda: Procházejte řetězec znak po znaku a použijte tolower() pro zjednodušení.
    std::regex samohlasky("[aeiou]", std::regex_constants::icase);

    int total_vowels = 0;

    for (char ch : content) {
        if (std::regex_search(std::string(1, ch), samohlasky)) {
            total_vowels++;
        }
    }
    return total_vowels;
}

// --- Hlavní program (neměnit) ---

#ifndef __TEST__
int main()
{
    std::string filename = "text_k_analyze.txt";
    std::string content = getFileContent(filename);

    if (content.empty() && filename == "text_k_analyze.txt")
    {
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
