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
string getFileContent(string filename) {
    ifstream soubor(filename);
    if (!soubor.is_open()) {
        return "";    
        return 0;                // soubor se nepodařilo otevřít
    }
    
}

/**
 * @brief Spočítá počet všech znaků v textu.
 * @param content Text k analýze.
 * @return Počet znaků.
 */
int countCharacters(string content) {
    int pocet_znaku = 0;
    int i = 0;
    while (i < content.length()){
        pocet_znaku++;
        i++;
    }
    return pocet_znaku;

}

/**
 * @brief Spočítá počet řádků v textu.
 * @param content Text k analýze.
 * @return Počet řádků.
 */
int countLines(string content) {
    if (content.empty()) return 0;
    int radky = 1;                    // neprázdný text bez '\n' má 1 řádek
    for (unsigned char ch : content) {
        if (ch == '\n') ++radky;
    }
    return radky;
}

/**
 * @brief Spočítá počet slov v textu.
 * @param content Text k analýze.
 * @return Počet slov.
 */
int countWords(string content) {
    istringstream iss(content);
    string slovo;
    int pocet = 0;
    while (iss >> slovo) ++pocet;      // oddělení slov podle whitespace
    return pocet;
}

/**
 * @brief Spočítá počet samohlásek (a, e, i, o, u) v textu.
 * @param content Text k analýze.
 * @return Počet samohlásek.
 */
int countVowels(string content) {
    int pocet = 0;
    for (unsigned char ch : content) {
        char c = static_cast<char>(tolower(ch));
        if (c=='a' || c=='e' || c=='i' || c=='o' || c=='u') ++pocet;
    }
    return pocet;
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

