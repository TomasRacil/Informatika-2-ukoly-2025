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
std::string getFileContent(std::string filename)
{

    std::ifstream vstupniSoubor(filename);
    if (!vstupniSoubor.is_open())
    {
        return "";
    }

    std::string content, radek;

    // pridava postupne v cyklu radky do content
    while (std::getline(vstupniSoubor, radek))
    {
        content += radek;
        // pokud neni konec souboru, prida konec radku
        if (!vstupniSoubor.eof())
            content = content + '\n';
    }
    return content;
}

/**
 * @brief Spočítá počet všech znaků v textu.
 * @param content Text k analýze.
 * @return Počet znaků.
 */
int countCharacters(std::string content)
{
    // TODO: Doplňte kód pro spočítání znaků.

    if (content.empty())
    {
        return 0;
    }
    // vyuzijem funkci length()
    int pocet = content.length();

    return pocet;
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
    if (content.empty())
    {
        return 0;
    }
    // 1, viz. komentar vyse
    int pocRadku = 1;
    for (char c : content)
    {
        // pokud je konec radku, pripoctem do promenne
        if (c == '\n')
        {
            pocRadku++;
        }
    }

    return pocRadku;
}

/**
 * @brief Spočítá počet slov v textu.
 * @param content Text k analýze.
 * @return Počet slov.
 */
int countWords(std::string content)
{
    if (content.empty())
    {
        return 0;
    }
    // Použijeme stringstream pro rozdělení textu na slova.
    std::stringstream strstr(content);
    std::string slovo;
    int pocSlov = 0;

    // Cyklus cte slova oddelena mezerami
    while (strstr >> slovo)
    {
        pocSlov++;
    }

    return pocSlov;
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
    if (content.empty())
    {
        return 0;
    }

    int pocSamohlasek = 0;

    for (char c : content)
    {
        // male pismenko musime ulozit do nove promenne
        char maly = tolower(c);
        if (maly == 'a' || maly == 'e' || maly == 'i' || maly == 'o' || maly == 'u')
        {
            pocSamohlasek++;
        }
    }
    return pocSamohlasek;
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
