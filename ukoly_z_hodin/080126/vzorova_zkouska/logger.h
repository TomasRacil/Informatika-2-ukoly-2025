#pragma once
#include <iostream>

using namespace std;

class Logger
{
private:
    string nazev_souboru = "server.log";
    int pocet_operaci = 0;

public:
    void log(string uroven, string objekt, string zprava);
};

class Server
{
private:
public:

    void run(int pocetUdalosti);
};