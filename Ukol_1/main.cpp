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
    // std::string getFileContent(std::string filename) je deklarace funkce
    std::ifstream file(filename); //  ifstream je třída pro čtení ze souboru
    if (!file.is_open()) {
        return "";
        // !file.is_open() je podmínka, která kontroluje, zda se soubor nepodařilo otevřít
    }

    std::stringstream content; // slouží jako buffer pro načtený obsah souboru
    content << file.rdbuf(); //  načtení obsahu souboru do proměnné content
    file.close(); //  zavření souboru
    return content.str(); //  vrácení obsahu proměnné content jako řetězec
}

/**
 * @brief Spočítá počet všech znaků v textu.
 * @param content Text k analýze.
 * @return Počet znaků.
 */
int countCharacters(std::string content) {
    // TODO: Doplňte kód pro spočítání znaků.
    int characters = content.length(); // .length do proměnné characters uloží počet znaků v řetězci content
    return characters; // vrátí počet znaků
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
        return 0; // empty kontroluje, zda je řetězec prázdný (pokud ano, vrací 0)
    }
    int lines = 1; // neprázdný soubor má min 1 řádek
    for (char c : content) { // datový typ char (c) prochází řetězec content znak po znaku
        if (c == '\n') {
            lines++; // pokud tam bude \n, počet řádků (lines) += 1
        }
    }
    return lines; // počet řádků
}

/**
 * @brief Spočítá počet slov v textu.
 * @param content Text k analýze.
 * @return Počet slov.
 */
int countWords(std::string content) {
    // TODO: Doplňte kód pro spočítání slov.
    // Nápověda: Můžete použít std::stringstream pro snadné oddělení slov.
    std::stringstream words(content); // std::stringstream slouží k rozdělení řetězce content na slova uložená v proměnné words
    std::string word; // proměnná word k ukládání jednotlivých slov
    int count = 0; // počet slov
    while (words >> word) { // oddělená slova z words se postupně načítají do proměnné word
        count++; // slova += 1
    }
    return count; // celkový počet slov
}

/**
 * @brief Spočítá počet samohlásek (a, e, i, o, u) v textu.
 * @param content Text k analýze.
 * @return Počet samohlásek.
 */
int countVowels(std::string content) {
    // TODO: Doplňte kód pro spočítání samohlásek.
    // Nápověda: Procházejte řetězec znak po znaku a použijte tolower() pro zjednodušení.
    int vowels = 0; // počet samohlásek
    for (char c : content) { // procházení řetězce content znak po znaku
        char lowerC = std::tolower(c); // převedení znaku na malá písmena
        if (lowerC == 'a' || lowerC == 'e' || lowerC == 'i' || lowerC == 'o' || lowerC == 'u') {
            vowels++; // pokud je znak samohláska, počet samohlásek += 1
        }
    }
    return vowels; // vrácení počtu samohlásek
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

