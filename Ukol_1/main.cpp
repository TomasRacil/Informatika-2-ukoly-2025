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
    ifstream file(filename);
    if(!file.is_open()){
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
int countCharacters(string content) {
    return content.size();
}

int countLines(string content) {
    if (content.empty()) return 0;

    int countL = 0;
    for(char c : content){
        if(c == '\n'){
            countL++;
        }
    }
    return countL + 1;
}

int countWords(string content) {
    int countW = 0;
    bool inWord;

    for(char c : content){
        if(isalpha(c)){
            if(!inWord){
                inWord = true;
                countW++;
            }
        }
        else{
            inWord = false;
        }
    }
    return countW;
}

int countVowels(string content) {
    int countV = 0;
    for(char c : content){
        c = tolower(c);
        if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'){
            countV++;
        }
    }
    return countV;
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

