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
    // TODO: Doplňte kód pro načtení souboru.
    // Nápověda: Použijte std::ifstream a std::stringstream.
    // V případě, že se soubor nepodaří otevřít, vraťte prázdný řetězec "".

    std::ifstream file(filename);
    if (file.is_open())
    {
        std::stringstream buffer;
        buffer << file.rdbuf();
        file.close();
        return buffer.str();
    }
    return "";
}

/**
 * @brief Spočítá počet všech znaků v textu.
 * @param content Text k analýze.
 * @return Počet znaků.
 */
int countCharacters(std::string content)
{
    // TODO: Doplňte kód pro spočítání znaků.
    return content.length();
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
    int lines = 1;
    if (content.empty())
    {
        return 0;
    }
    for (char c : content)
    {
        if (c == '\n')
        {
            lines++;
        }
    }
    std::cout << "Lines: " << lines << std::endl;
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
    int words = 1;
    if (content.empty())
    {
        return 0;
    }

    for (int i = 0; i < content.length(); i++)
    {
        if (isspace(content[i]) && !isspace(content[i - 1]))
        {
            words++;
        }
    }

    return words;
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
    int vowels = 0;
    for (char c : content)
    {
        char cl = tolower(c);
        if (cl == 'a' || cl == 'e' || cl == 'i' || cl == 'o' || cl == 'u')
        {
            vowels++;
        }
    }
    return vowels;
};

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
