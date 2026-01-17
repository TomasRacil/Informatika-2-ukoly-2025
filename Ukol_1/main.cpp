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
string getFileContent(string filename) {
    // TODO: Doplňte kód pro načtení souboru.
    // Nápověda: Použijte std::ifstream a std::stringstream.
    // V případě, že se soubor nepodaří otevřít, vraťte prázdný řetězec "".
    ifstream file(filename);
    if (file) { 
        stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }
    else {
        return "";
    }
}

/**
 * @brief Spočítá počet všech znaků v textu.
 * @param content Text k analýze.
 * @return Počet znaků.
 */
int countCharacters(string content) {
    // TODO: Doplňte kód pro spočítání znaků.
int delka = content.length();

return delka;

}

/**
 * @brief Spočítá počet řádků v textu.
 * @param content Text k analýze.
 * @return Počet řádků.
 */
int countLines(string content) {
    // TODO: Doplňte kód pro spočítání řádků.
    // Nezapomeňte, že i neprázdný soubor bez znaku nového řádku má 1 řádek.
    if (content.empty()) {
        return 0;
    }
    int pocetRadku = 1; 
    for (char c : content) {
        if (c == '\n') {
            pocetRadku++;
        }
    }
    return pocetRadku;
}

/**
 * @brief Spočítá počet slov v textu.
 * @param content Text k analýze.
 * @return Počet slov.
 */
int countWords(string content) {
    // TODO: Doplňte kód pro spočítání slov.
    // Nápověda: Můžete použít std::stringstream pro snadné oddělení slov.
    stringstream ss(content);
    string slovo;
    int pocetSlov = 0;
    while (ss >> slovo) {
        pocetSlov++;
    }
    return pocetSlov;
}

/**
 * @brief Spočítá počet samohlásek (a, e, i, o, u) v textu.
 * @param content Text k analýze.
 * @return Počet samohlásek.
 */
int countVowels(string content) {
    // TODO: Doplňte kód pro spočítání samohlásek.
    // Nápověda: Procházejte řetězec znak po znaku a použijte tolower() pro zjednodušení.
    int pocetSamohlasek = 0;
    for (char c : content) {
        char lowerC = tolower(c);
        if (lowerC == 'a' || lowerC == 'e' || lowerC == 'i' || lowerC == 'o' || lowerC == 'u') {
            pocetSamohlasek++;
        }
    }
    return pocetSamohlasek;
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

