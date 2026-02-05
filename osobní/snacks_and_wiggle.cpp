// Zde vždycky napsat všechny knihovny co chci použít v projektu: #include <>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#ifdef _WIN32
#include <windows.h>
#endif

// Je dobré do knihoven připsat i using namespace std;, to dělá to že vše co vyžaduje napsání std, například std::cout tak nyní nemusím psát, stačí napsat cout << a jedem
using namespace std;

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
// Barevne pisma
    // Barevné kódy ANSI
    const std::string RED = "\033[31m";
    const std::string GREEN = "\033[32m";
    const std::string BLUE = "\033[34m";
    const std::string BOLD = "\033[1m";
    const std::string RESET = "\033[0m";
    // Další barvy
    const std::string WHITE = "\033[37m";
    const std::string BLACK = "\033[30m";
    const std::string YELLOW = "\033[33m";
    const std::string MAGENTA = "\033[35m";
    const std::string CYAN = "\033[36m";
    
    // Jasné varianty barev
    const std::string BRIGHT_RED = "\033[91m";
    const std::string BRIGHT_GREEN = "\033[92m";
    const std::string BRIGHT_YELLOW = "\033[93m";
    const std::string BRIGHT_BLUE = "\033[94m";
    const std::string BRIGHT_MAGENTA = "\033[95m";
    const std::string BRIGHT_CYAN = "\033[96m";
    const std::string BRIGHT_WHITE = "\033[97m";
    
    // Pozadí
    const std::string BG_RED = "\033[41m";
    const std::string BG_GREEN = "\033[42m";
    const std::string BG_YELLOW = "\033[43m";
    const std::string BG_BLUE = "\033[44m";
    const std::string BG_MAGENTA = "\033[45m";
    const std::string BG_CYAN = "\033[46m";
    const std::string BG_WHITE = "\033[47m";

// Pokud chceme zde si přidáme int, double, float, void atp
void rules();
void creators();
void postavy();
void utok();
void obrana();
void game();
void inventory();
void questgiver();

// Globalni promenne
string char_name;
string choose_class;

// Rozdělení classes
string warrior = YELLOW + "Warrior" + RESET; // slabší útok, ale větší hp
string mage = MAGENTA + "Mage" + RESET; // větší útok, ale menší hp
string archer = BRIGHT_GREEN + "Archer" + RESET; // střední útok a střední hp

// Atributy
int hp;
int damage;
int level = 1;

// Itemy
int potion_heal = 0; // pridava hp
int potion_mana = 0; // pridava manu
int potion_dmg_boost = 0; // boostuju damage
int bread = 1; // take pridava hp ale mene nez potion a je levnejsi
int water = 1; // pridava manu mene nez potion_mana a je levnejsi
//měna
int gold = 100; // začínající zlaté
int gems = 5; // začínající drahokamy
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

// Přidáno pouze pro krásu textu, dělá to animaci jakoby psaní textu. Text s touto animaci pridame: typeText("text", 30) - tech 30 je doba co se bude text vypisovat
void typeText(const string& text, int speed = 30) {
    for (char c : text) {
        cout << c << flush;

this_thread::sleep_for(chrono::milliseconds(speed));
    }
}

// Helper to safely spend gold. Returns true if purchase succeeded.
bool spendGold(int price) {
    if (gold >= price) {
        gold -= price;
        return true;
    } else {
        typeText("You don't have enough coins for that purchase!\n", 30);
        return false;
    }
}



// Zde zacina nas main kde bezi hlavni cast program, vyvolava vse mozne a vyuziva vse. Cokoliv co je kolem je neco jako podprogram co funguje jen kdyz je zvolan mainem
int main () {
    
    while (true)  // Hlavní smyčka pro návrat do menu
    {
        cout << ("--------------" + BRIGHT_CYAN + BOLD + "Snacks" + RESET + WHITE + BOLD + " & " + BRIGHT_MAGENTA + BOLD + "Wiggle" + RESET + "--------------" + RESET);

        typeText("\n1. Rules\n", 20);
        typeText("2. Creators\n", 20);
        typeText("3. Play Game\n", 20);
        typeText("4. Exit\n", 20);

        int choose;
        typeText("Choose an option: ", 20);
        cin >> choose;

        if (choose == 1) 
        {
            rules();
            // Po skončení rules() se vrátí sem a smyčka se opakuje
        } 

        else if (choose == 2) 
        {
            creators();
            // Po skončení creators() se vrátí sem a smyčka se opakuje
        } 

        else if (choose == 3) 
        {
            postavy();
            // Po skončení postavy() se vrátí sem a smyčka se opakuje
        } 

        else if (choose == 4)
        {
            typeText("\nThanks for playing! Goodbye!\n", 20);
            return 0;  // Ukončení programu
        }

        else 
        {
            typeText("Wrong input. Try again.\n\n", 20);
            continue;
            // Smyčka se opakuje
        }

    }

    return 0;
}

// Zde si vypisuju vsechny voidy, neboli vedlejsi programy at to necpu vse do mainu a je to prehlednejsi, jeste lepsi to bude udfelat na dalsi stranky napriklad utok.cpp a pak to pospojovat, ale takhle to je taky ok.
void rules() 
{
    cout << "\n--------------" + MAGENTA + BOLD + "RULES" + RESET + "--------------\n";
    typeText("1. The game is turn-based; players take turns performing actions.\n", 20);
    typeText("2. Each player selects a character with unique abilities.\n", 20);
    typeText("3. The objective is to defeat all enemies or complete specific quests.\n", 20);
    typeText("4. Players can attack, defend, or use special abilities.\n", 20);
    typeText("5. The game ends when one player achieves victory or all others are defeated.\n", 20);
    typeText("6. Enjoy the game and have fun!\n", 20);

    typeText("\nPress ENTER to get back to the main menu.\n", 30);
    cin.ignore();  // Vyčistí buffer od předchozího cin
    cin.get();     // Čeká na Enter

}
///////////////////////////////////////////
///////////////////////////////////////////
void creators() 
{
    cout << "\n--------------" + WHITE + BOLD + "Creators of the game" + RESET + "--------------\n";
    typeText("1. Developer - Tomas Rataj\n", 30);
    typeText("2. Designer - Tomas Rataj\n", 30);
    typeText("3. Support - Tomas Rataj\n", 30);

    typeText("\nPress ENTER to get back to the main menu.\n", 30);
    cin.ignore();  // Vyčistí buffer od předchozího cin
    cin.get();     // Čeká na Enter
}
///////////////////////////////////////////
///////////////////////////////////////////
void postavy() 
{

    cout << "\n--------------" + GREEN + BOLD + "Character Creation" + RESET + "--------------\n";
    typeText("Choose your character class:\n", 20);
    typeText(WHITE + "1." + RESET + YELLOW + " Warrior\n", 20);
    typeText(WHITE + "2." + RESET + MAGENTA + " Mage\n", 20);
    typeText(WHITE + "3." + RESET + BRIGHT_GREEN + " Archer\n" + RESET, 20);
    int choose1;
    typeText("So? What is your choice? ", 20);
    cin >> choose1;

    while (true) 
    {
        if (choose1 == 1)
        {
            cout << "\n------" + BOLD + YELLOW + "Warrior" + RESET + "------\n";
            typeText("This class have more hp then anyone else, that is why we call them tanks! Very good choice!\n", 30);
            typeText("\n------STATS------\n", 30);
            typeText("HP: 150\nDamage: 20\n", 30);
            choose_class = warrior;
            hp = 150;
            damage = 20;

            typeText("\n------NAME YOUR CHARACTER------\n", 30);
            typeText("Write your character's name: ", 30);
            cin >> char_name;
            game();
        } 

        else if (choose1 == 2)
        {
            cout << "\n------" + BOLD + MAGENTA + "Mage" + RESET + "------\n";
            typeText("This class have bigger damage but lower health, so play it smart, and you will be the best!\n", 30);
            typeText("\n------STATS------\n", 30);
            typeText("HP: 80\nDamage: 40\n", 30);
            choose_class = mage;
            hp = 80;
            damage = 40;

            typeText("\n------NAME YOUR CHARACTER------\n", 30);
            typeText("Write your character's name: ", 30);
            cin >> char_name;
            game();
        } 
        
        else if (choose1 == 3)
        {
            cout << "\n------" + BOLD + BRIGHT_GREEN + "Archer" + RESET + "------\n";
            typeText("This class is perfect for players who prefer ranged attacks and balanced stats.\n", 30);
            typeText("\n------STATS------\n", 30);
            typeText("HP: 100\nDamage: 30\n", 30);
            choose_class = archer;
            hp = 100;
            damage = 30;

            typeText("\n------NAME YOUR CHARACTER------\n", 30);
            typeText("Write your character's name: ", 30);
            cin >> char_name;
            game();
        } 
        
        else {
            typeText("\nInvalid choice. Please choose 1, 2, or 3.\n", 20);
            cin >> choose1;
            continue;
        }
        break;
    }

}
////////////////////////////////////////////
////////////////////////////////////////////
void inventory()
{
    cout << "\n--------------" + BOLD + WHITE + "INVENTORY" + RESET + "--------------";
    typeText("\n" + to_string(gold) + " Coins 🪙\n", 30);
    typeText(to_string(gems) + " Gems 💎\n", 30);
    typeText(to_string(potion_heal) + " Heal Potions ❤️\n", 30);
    typeText(to_string(potion_mana) + " Mana Potions 💠\n", 30);
    typeText(to_string(potion_dmg_boost) + " Damage Boost Potions ⚔️\n", 30);
    typeText(to_string(bread) + " Breads 🍞\n", 30);
    typeText(to_string(water) + " Waters 🫗\n", 30);

    typeText("\nPress ENTER to get back to the main menu.\n", 30);
    cin.ignore();  // Vyčistí buffer od předchozího cin
    cin.get();     // Čeká na Enter
}
////////////////////////////////////////////
////////////////////////////////////////////
void questgiver()
{
    if (level == 1)
    {
        cout << "\n--------------" + BOLD + WHITE + "QUEST GIVER" + RESET + "--------------\n";
        typeText(BRIGHT_YELLOW + "Elder:" + RESET + WHITE + " Hello " + BOLD + char_name + RESET + WHITE + ", we need your help to defend our village from the evil Globet!\n", 50);
        typeText(WHITE + "Can you help us by defeating 3 of his minions lurking around our village?\n", 50);
        typeText(BRIGHT_BLUE + BOLD + char_name + RESET + WHITE + ": Yes, I will help you!\n", 50);
        typeText(BRIGHT_YELLOW + "Elder:" + RESET + WHITE + " Great! Return to me once you have defeated them.\n", 50);

        typeText(MAGENTA + "\nRewards:" + RESET + WHITE + "\n100 🪙\n1x Heal Potion.\n", 50);

        typeText("\nPress ENTER to continue.", 30);
        cin.ignore();  // Vyčistí buffer od předchozího cin
        cin.get();     // Čeká na Enter    

        // Simulace dokončení úkolu
        typeText("\nYou have defeated 3 minions!\n", 30);
        level = 2; // Postup na další úroveň
        typeText(BRIGHT_YELLOW + "Elder:" + RESET + WHITE + " Thank you, " + BOLD + char_name + RESET + WHITE + "! Here is your reward: 100 Coins and a Heal Potion.\n", 50);
        gold += 100;
        potion_heal += 1;

        typeText("\nPress ENTER to get back to the main menu.\n", 30);
        cin.ignore();  // Vyčistí buffer od předchozího cin
        cin.get();     // Čeká na Enter
    }

    else if (level == 2)
    {
        cout << "\n--------------" + BOLD + WHITE + "QUEST GIVER" + RESET + "--------------\n";
        typeText(BRIGHT_YELLOW + "Elder:" + RESET + WHITE + " Welcome back " + BOLD + char_name + RESET + WHITE + "! We have another task for you.\n", 50);
        typeText(WHITE + "Globet's lieutenants are gathering strength. We need you to defeat 2 of them to weaken his forces.\n", 50);
        typeText(BRIGHT_BLUE + BOLD + char_name + RESET + WHITE + ": I will take care of it!\n", 50);
        typeText(BRIGHT_YELLOW + "Elder:" + RESET + WHITE + " Thank you! Return to me once you have defeated them.\n", 50);

        typeText(MAGENTA + "\nRewards:" + RESET + WHITE + "\n150 🪙\n1x Damage Boost Potion.\n", 50);

        typeText("\nPress ENTER to continue.", 30);
        cin.ignore();  // Vyčistí buffer od předchozího cin
        cin.get();     // Čeká na Enter    

        // Simulace dokončení úkolu
        typeText("\nYou have defeated 2 lieutenants!\n", 30);
        level = 3; // Postup na další úroveň
        typeText(BRIGHT_YELLOW + "Elder:" + RESET + WHITE + " Excellent work, " + BOLD + char_name + RESET + WHITE + "! Here is your reward: 150 Coins and a Damage Boost Potion.\n", 50);
        gold += 150;
        potion_dmg_boost += 1;

        typeText("\nPress ENTER to get back to the main menu.\n", 30);
        cin.ignore();  // Vyčistí buffer od předchozího cin
        cin.get();     // Čeká na Enter
    }

    else
    {
        typeText("\nYou have no new quests at the moment. Please check back later.\n", 30);
        typeText("\nPress ENTER to get back to the main menu.\n", 30);
        cin.ignore();  // Vyčistí buffer od předchozího cin
        cin.get();     // Čeká na Enter
    }
}
////////////////////////////////////////////
////////////////////////////////////////////
void game()
{
    cout << "\n--------------" + BRIGHT_CYAN + BOLD + "LORE" + RESET + "--------------\n";
    typeText(BRIGHT_GREEN + BOLD + "Villager:" + RESET + WHITE + " Welcome " + BOLD + char_name + RESET + WHITE + " we are very glad that you came to save us!\n", 50);
    typeText(WHITE + "We live in the dark times now. A guy called " + RED + "Globet" + RESET + WHITE + " is our nightmare for last months...\n", 50);
    typeText(WHITE + "Will you help us to defend our homes?\n", 50);
    typeText(BRIGHT_BLUE + BOLD + char_name + RESET + WHITE + ": Yes, I will defend you at all cost!\n", 50);
    typeText("\nPress ENTER to continue.", 30);
    cin.ignore();  // Vyčistí buffer od předchozího cin
    cin.get();     // Čeká na Enter    

    while (true)
    {

        cout << ("\n--------------" + BRIGHT_CYAN + BOLD + "Snacks" + RESET + WHITE + BOLD + " & " + BRIGHT_MAGENTA + BOLD + "Wiggle" + RESET + "--------------\n" + RESET);
        typeText("1. Character Stats\n", 30);
        typeText("2. Inventory\n", 30);
        typeText("3. Tavern\n", 30);
        typeText("4. Main Menu " + BRIGHT_RED + "(Will delete your char!)\n" + RESET, 30);
        int choose;
        typeText("Choose an option: ", 30);
        cin >> choose;

        if (choose == 1)
        {
            cout << "\n--------------" + BOLD + WHITE + "CHARACTER STATS" + RESET + "--------------\n";
            typeText("Name: " + BRIGHT_BLUE + char_name + RESET + "\n", 30);
            typeText("Level: " + BRIGHT_YELLOW + to_string(level) +  RESET + "\n", 30);
            typeText("Class: " + choose_class + "\n", 30);
            typeText("HP: " + BRIGHT_GREEN + to_string(hp) +  RESET + "\n", 30);
            typeText("Damage: " + CYAN + to_string(damage) + RESET + "\n", 30);

            typeText("\nPress ENTER to get back to the main menu.\n", 30);
            cin.ignore();  // Vyčistí buffer od předchozího cin
            cin.get();     // Čeká na Enter
        }

        else if (choose == 2)
        {
            inventory();
        }

        else if (choose == 3)
        {
            cout << "\n--------------" + BOLD + WHITE + "TAVERN" + RESET + "--------------\n";
            typeText("1. Shopkeeper\n", 30);
            typeText("2. Quest Giver\n", 30);
            typeText("3. Go Back\n", 30);
            int tavernChoice;
            typeText("Who do you want to talk to? ", 30);
            cin >> tavernChoice;

            if (tavernChoice == 1)
            {
                // Open shop loop so player can buy multiple items before exiting the shop
                while (true) {
                    cout << "\n--------------" + BOLD + WHITE + "SHOPKEEPER" + RESET + "--------------\n";
                    typeText(MAGENTA + "Jinxy: " + RESET + "Welcome to my shop! What do you want to buy?\n", 30);
                    typeText("1. Heal Potion (50) 🪙\n", 30);
                    typeText("2. Mana Potion (50) 🪙\n", 30);
                    typeText("3. Damage Boost Potion (75) 🪙\n", 30);
                    typeText("4. Bread (20) 🪙\n", 30);
                    typeText("5. Water (20) 🪙\n", 30);
                    typeText("6. Exit Shop\n", 30);

                    int shopChoice;
                    typeText("What is your choice? ", 30);
                    cin >> shopChoice;

                    if (shopChoice == 1)
                    {
                        if (spendGold(50)) {
                            potion_heal++;
                            typeText("You bought a Heal Potion.\n", 30);
                        }
                    }
                    else if (shopChoice == 2)
                    {
                        if (spendGold(50)) {
                            potion_mana++;
                            typeText("You bought a Mana Potion.\n", 30);
                        }
                    }
                    else if (shopChoice == 3)
                    {
                        if (spendGold(75)) {
                            potion_dmg_boost++;
                            typeText("You bought a Damage Boost Potion.\n", 30);
                        }
                    }
                    else if (shopChoice == 4)
                    {
                        if (spendGold(20)) {
                            bread++;
                            typeText("You bought Bread.\n", 30);
                        }
                    }
                    else if (shopChoice == 5)
                    {
                        if (spendGold(20)) {
                            water++;
                            typeText("You bought Water.\n", 30);
                        }
                    }
                    else if (shopChoice == 6)
                    {
                        // Exit shop and return to tavern menu
                        break;
                    }
                    else 
                    {
                        typeText("Wrong input. Try again.\n", 20);
                    }
                }
            }

            else if (tavernChoice == 2)
            {
                questgiver();
            }

            else if (tavernChoice == 3)
            {
                // Go back to main game menu
                continue;
            }

            else 
            {
                typeText("Wrong input. Try again.\n", 20);
            }

            
        }

        else if (choose == 4)
        {
            typeText("Okay, see ya later!\n\n", 20);
            return;
        }

        else
        {
            typeText("Wrong input. Try again.\n", 20);
            continue;
        }
    }

}

// Soubojovy system na kola a asi jako to bylo u pokemonu kazde kolo na vyber z nekolika utoku, pouzit inventar na heal, manu atp
// Funkce pro itemy v inventari
// Dodelat ukoly
// Dodelat utok a obranu, celkova logika. Mozna graficky?
// Mozna pridat levely a zacit od 1. levelu a podle toho se budou odvijet ukoly po kazdem dokoncenem ukolu dostanu novy level a lepsi staty