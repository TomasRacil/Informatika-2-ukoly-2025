#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <ctime>
#include <chrono>   // <-- přidáno pro std::chrono používané při inicializaci rng
#include <algorithm>
#include <set>
#include <fstream>
#include <cctype>

// Upravit seznam slov zde (pro ty, co budou hrát) nebo pridat soubor "words.txt" vedle programu (kazdy radek = jedno slovo)
static std::vector<std::string> BUILT_IN_WORDS = {
    "jablko", "programovani", "python", "informatika", "skola", "stromecek", "auto", "knihovna"
};

static const std::vector<std::string> HANGMAN_PICS = {
    // 0 wrong
    "  +---+\n  |   |\n      |\n      |\n      |\n      |\n=========\n",
    // 1 wrong
    "  +---+\n  |   |\n  O   |\n      |\n      |\n      |\n=========\n",
    // 2 wrong
    "  +---+\n  |   |\n  O   |\n  |   |\n      |\n      |\n=========\n",
    // 3 wrong
    "  +---+\n  |   |\n  O   |\n /|   |\n      |\n      |\n=========\n",
    // 4 wrong
    "  +---+\n  |   |\n  O   |\n /|\\  |\n      |\n      |\n=========\n",
    // 5 wrong
    "  +---+\n  |   |\n  O   |\n /|\\  |\n /    |\n      |\n=========\n",
    // 6 wrong (final)
    "  +---+\n  |   |\n  O   |\n /|\\  |\n / \\  |\n      |\n=========\n"
};

static std::string trim(const std::string& s) {
    size_t a = 0;
    while (a < s.size() && std::isspace((unsigned char)s[a])) ++a;
    size_t b = s.size();
    while (b > a && std::isspace((unsigned char)s[b-1])) --b;
    return s.substr(a, b-a);
}

static std::string to_lower_ascii(const std::string& s) {
    std::string out;
    out.reserve(s.size());
    for (unsigned char c : s) out.push_back(std::tolower(c));
    return out;
}

std::string choose_word(std::mt19937 &rng) {
    // nacteme soubor words.txt pokud existuje ( kazdy radek jedno slovo )
    std::vector<std::string> words = BUILT_IN_WORDS;
    std::ifstream f("words.txt");
    if (f) {
        std::string line;
        while (std::getline(f, line)) {
            line = trim(line);
            if (!line.empty()) words.push_back(line);
        }
    }
    if (words.empty()) return "nic";
    std::uniform_int_distribution<size_t> dist(0, words.size()-1);
    return to_lower_ascii(words[dist(rng)]);
}

void draw_state(const std::string& secret, const std::set<char>& guessed, int wrong) {
    std::cout << HANGMAN_PICS[std::min(wrong, (int)HANGMAN_PICS.size()-1)] << "\n";
    // zobrazeni slova s podtrzitky
    for (char c : secret) {
        if (std::isalpha((unsigned char)c)) {
            if (guessed.count(c)) std::cout << c << ' ';
            else std::cout << "_ ";
        } else {
            // neznamkove znaky (pomlcka atd.) zobrazime
            std::cout << c << ' ';
        }
    }
    std::cout << "\n\n";
    std::cout << "Pismena: ";
    for (char c : guessed) std::cout << c << ' ';
    std::cout << "\n\n";
}

int main() {
    std::mt19937 rng((unsigned)std::chrono::high_resolution_clock::now().time_since_epoch().count());
    std::cout << "=== Šibenice ===\n";
    std::cout << "Pravidla: Maximalne je 5 chyb. Uhadni slovo postupně pismeny nebo celym slovem.\n";
    

    while (true) {
        std::string secret = choose_word(rng);
        // zajistime jen male pismena ascii
        secret = to_lower_ascii(secret);

        std::set<char> guessed;
        int wrong = 0;
        const int max_wrong = (int)HANGMAN_PICS.size() - 1;
        bool won = false;

        while (wrong <= max_wrong) {
            draw_state(secret, guessed, wrong);
            std::cout << "Zadejte pismeno nebo cele slovo (q = konec): ";
            std::string input;
            if (!(std::cin >> input)) return 0;
            input = to_lower_ascii(trim(input));
            if (input.empty()) continue;
            if (input == "q" || input == "quit" || input == "exit") return 0;

            if (input.size() == 1) {
                char ch = input[0];
                if (!std::isalpha((unsigned char)ch)) {
                    std::cout << "Zadejte platne pismeno.\n";
                    continue;
                }
                if (guessed.count(ch)) {
                    std::cout << "Uz jste toto pismeno zkouseli.\n";
                    continue;
                }
                guessed.insert(ch);
                if (secret.find(ch) == std::string::npos) {
                    ++wrong;
                    std::cout << "Spatne!\n";
                } else {
                    std::cout << "Spravne!\n";
                }
            } else {
                // pokus o uhadnuti celeho slova
                if (input == secret) {
                    won = true;
                    break;
                } else {
                    ++wrong;
                    std::cout << "To neni ono.\n";
                }
            }

            // kontrola vyhry
            bool all = true;
            for (char c : secret) {
                if (std::isalpha((unsigned char)c) && !guessed.count(c)) { all = false; break; }
            }
            if (all) { won = true; break; }

            if (wrong > max_wrong) break;
        }

        draw_state(secret, guessed, wrong);
        if (won) {
            std::cout << "Vyhral jste! Slovo bylo: " << secret << "\n";
        } else {
            std::cout << "Prohral jste. Slovo bylo: " << secret << "\n";
        }

        std::cout << "Hrát znovu? (a/n): ";
        std::string ans;
        if (!(std::cin >> ans)) break;
        ans = to_lower_ascii(trim(ans));
        if (ans.empty() || ans[0] != 'a' && ans[0] != 'y') break;
        std::cout << "\n\n";
    }

    return 0;
}