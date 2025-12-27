#include "database.h"
#include <iostream>
#include <fstream>

int main() {
    Database db("/workspaces/Informatika-2-ukoly-2025-VaclavJelinek/sqlitedatabaseee/new12.db");

    // Load and execute SQL schema
    std::ifstream file("/workspaces/Informatika-2-ukoly-2025-VaclavJelinek/sqlitedatabaseee/new12.sql");
    if (file) {
        std::string sql((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());
        if (db.executeSQL(sql)) {
            std::cout << "Schema created successfully\n";
        }
    }

    // Print users
    std::cout << "Users in database:\n";
    db.printUsers();

    return 0;
}
