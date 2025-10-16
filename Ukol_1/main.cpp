#include <iostream>   //výpis na obrazovku
#include <fstream>    //pro čtení ze souboru
#include <string>     //pro práci s textem
#include <sstream>    //pro rozdělení textu na slova
#include <cctype>     //pro převod písmen na malá

using namespace std;  // abych nemusel psát std::

// řetězec do jednoho souboru
string getFileContent(const string& filename) {
    ifstream file(filename);        // otevře soubor
    if (!file.is_open()) {          
        return "";                  // vrátí se mi prázdný text
    }
    stringstream buffer;            
    buffer << file.rdbuf();         // načte celý soubor
    return buffer.str();            // vrátí obsah jako tet
}

// spočítá mi všechny znaky
int countCharacters(const string& content) {
    return content.size();          // dá mi počet znaků
}

// spočítá počet řádků v textu
int countLines(const string& content) {
    if (content.empty()) return 0;  //když je prázdný
    int lines = 0;                  
    for (char c : content) {        // každý znak v textu
        if (c == '\n') lines++;     // když najde znak
    }
    if (content.back() != '\n') {   
        lines++;                    
    }
    return lines;                   // vrátí počet řádků
}

// spočítá počet slov
int countWords(const string& content) {
    stringstream ss(content);       
    string word;                    // jedno slovo
    int count = 0;                  // počítá slova
    while (ss >> word) {            //mezera mezi slovy
        count++;                    
    }
    return count;                   // dá mi počet slov
}

// spočítá počet samohlásek (a, e, i, o, u)
int countVowels(const string& content) {
    int vowels = 0;                 // psamohlásky
    for (char ch : content) {       // projde znaky
        ch = tolower(ch);           // znaky na malá písmena
        if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') {
            vowels++;               // když samohláska, tak + 1
        }
    }
    return vowels;                  // dá počet samohlásek
}

// main
#ifndef __TEST__
int main() {
    string filename = "text_k_analyze.txt"; // jméno souboru
    string content = getFileContent(filename); // obsah

    if (content.empty()) {                   // prázdný
        cerr << "Chyba: soubor se nepodařilo otevřít." << endl;
        return 1;                            // ukončí program s chybou
    }

    // zavolá mi funkce a uloží výsledky
    int pocetZnaku = countCharacters(content);
    int pocetRadku = countLines(content);
    int pocetSlov = countWords(content);
    int pocetSamohlasek = countVowels(content);

    // vypíše výsledky
    cout << "--- Výsledky analýzy ---" << endl;
    cout << "Počet znaků: " << pocetZnaku << endl;
    cout << "Počet řádků: " << pocetRadku << endl;
    cout << "Počet slov: " << pocetSlov << endl;
    cout << "Počet samohlásek: " << pocetSamohlasek << endl;

    return 0; // konec programu
}
#endif


