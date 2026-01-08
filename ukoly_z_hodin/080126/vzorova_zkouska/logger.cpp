#include "logger.h"
#include <iostream>
#include <fstream>
#include <random>

using namespace std;

void Logger::log(string uroven, string objekt, string zprava)
{
    ofstream log_file(nazev_souboru, ios::app);

    if (log_file.is_open())
    {
        pocet_operaci++;

        int cas = time(0);
        log_file << "[" << cas << "|" << pocet_operaci << "] " << uroven << ": " << objekt << " - " << zprava << endl;
        log_file.close();
    }
}

string urovne[3] = {"INFO", "WARNING", "ERROR"};
string objekty[3] = {"Databáze", "Server", "System"};
string zpravy_info[3] = {"Start procesu", "Uživatel přihlášen", "Záloha dokončena"};
string zpravy_warning[3] = {"Vysoká odezva", "Nízká paměť", "Neznámý požadavek"};
string zpravy_error[3] = {"Spojení selhalo", "Segfault", "Disk plný"};

void Server::run(int pocetUdalosti)
{
    Logger udalost = Logger();

    int c = 0;

    for (int i = 0; i < pocetUdalosti; i++)
    {
        int rng = rand() % 3;
        int rng_objekt = rand() % 3;
        int rng_zprava = rand() % 3;

        string uroven = urovne[rng];
        string objekt = objekty[rng_objekt];
        string zprava = "";

        if (uroven == "INFO")
        {
            zprava = zpravy_info[rng_zprava];
        }
        else if (uroven == "WARNING")
        {
            zprava = zpravy_warning[rng_zprava];
        }
        else if (uroven == "ERROR")
        {
            zprava = zpravy_error[rng_zprava];
        }

        udalost.log(uroven, objekt, zprava);
    }
}

int main()
{
    Server new_server = Server();
    int POCET_UDALOSTI = 50;

    new_server.run(POCET_UDALOSTI);
}