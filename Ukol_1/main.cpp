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

    std::ifstream CteniSouboru(filename);
    std::string text;
    std::string ftext;

    while (std::getline(CteniSouboru, text)) 
    {
        ftext += text +'\n';
    }
    if(ftext == "")
    {
        return "";
    }
    else
    {
        return ftext;
    }
}

/**
 * @brief Spočítá počet všech znaků v textu.
 * @param content Text k analýze.
 * @return Počet znaků.
 */
int countCharacters(std::string content) {
    int znak = 0;
    if(content.size() >0)
    {
    for(int i =0; i<content.size()-1; i++)
    {
        char c = content[i];
        znak++;
    }
    }
    if(znak>0)
    {
        return znak;
    }
    else
    {
    return 0;
    }
}

/**
 * @brief Spočítá počet řádků v textu.
 * @param content Text k analýze.
 * @return Počet řádků.
 */
int countLines(std::string content) {
    // TODO: Doplňte kód pro spočítání řádků.
    // Nezapomeňte, že i neprázdný soubor bez znaku nového řádku má 1 řádek.
    int pocet =0;
    if(content.size() >0)
    {
    for(int i =0; i<content.size(); i++)
    {
        if (content[i] == '\n')
        {
           pocet++; 
        }
    }
    }
    return pocet;
}

/**
 * @brief Spočítá počet slov v textu.
 * @param content Text k analýze.
 * @return Počet slov.
 */
int countWords(std::string content) {
    // TODO: Doplňte kód pro spočítání slov.
    // Nápověda: Můžete použít std::stringstream pro snadné oddělení slov.
    int pocet=0;
    bool radek = false;
    if(content.empty())
    {
        return 0;
    }
    if(content.size() >0)
    {
    for(int i =0; i<content.size(); i++)
    {
        if (content[i] == 32)
        {
           pocet++; 
        }
        else if(content[i] == '\n')
        {
            pocet++;
            radek = true;
        }
        if(i + 1 < content.size() && content[i] == '\n' && content[i+1] == '\n')
        {
            pocet--;
        }
    }
    }
    if(radek)
    {
        return pocet;
    }
    else
    {
        return pocet+1;
    }
}

/**
 * @brief Spočítá počet samohlásek (a, e, i, o, u) v textu.
 * @param content Text k analýze.
 * @return Počet samohlásek.
 */
int countVowels(std::string content) {
    // TODO: Doplňte kód pro spočítání samohlásek.
    // Nápověda: Procházejte řetězec znak po znaku a použijte tolower() pro zjednodušení.
    int pocet=0;
    if(content.size() >0)
    {
    for(int i =0; i<content.size(); i++)
    {
        if(std::tolower(content[i])== 'a' || std::tolower(content[i])== 'e' || std::tolower(content[i])== 'i' || std::tolower(content[i])== 'o' || std::tolower(content[i])== 'u')
        {
            pocet++;
        }
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
         return 0;
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

