#include <iostream>
#include <cstdlib>
#include <ctime>
#include "logger.h"

class Server {
private:
    Logger& logger;

public:
    Server(Logger& logger) : logger(logger) {
        std::srand(static_cast<unsigned>(std::time(nullptr)));
    }

    void run(int pocetUdalosti) {
        const std::string levels[] = {"INFO", "WARNING", "ERROR"};
        const std::string objects[] = {"Databáze", "Server", "System"};

        const std::string infoMsgs[] = {
            "Start procesu", "Uživatel přihlášen", "Záloha dokončena"
        };
        const std::string warningMsgs[] = {
            "Vysoká odezva", "Nízká paměť", "Neznámý požadavek"
        };
        const std::string errorMsgs[] = {
            "Spojení selhalo", "Segfault", "Disk plný"
        };

        for (int i = 0; i < pocetUdalosti; ++i) {
            int lvl = std::rand() % 3;
            int obj = std::rand() % 3;

            std::string message;
            if (levels[lvl] == "INFO")
                message = infoMsgs[std::rand() % 3];
            else if (levels[lvl] == "WARNING")
                message = warningMsgs[std::rand() % 3];
            else
                message = errorMsgs[std::rand() % 3];

            logger.log(levels[lvl], objects[obj], message);
        }
    }
};

int main() {
    Logger logger("server.log");
    Server server(logger);

    server.run(50);
    return 0;
}
