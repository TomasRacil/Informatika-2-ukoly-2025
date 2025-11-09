#include "database.h"
#include <iostream>
#include <fstream>

Database::Database(const std::string& path) : db(nullptr) {
    if (sqlite3_open(path.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        if (db) sqlite3_close(db);
        db = nullptr;
    }
}

Database::~Database() {
    if (db) sqlite3_close(db);
}

bool Database::executeSQL(const std::string& sql) {
    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}

void Database::printUsers() {
    if (!db) return;

    const char* sql = "SELECT username, level, xp FROM users;";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const char* username = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        int level = sqlite3_column_int(stmt, 1);
        int xp = sqlite3_column_int(stmt, 2);
        std::cout << username << " | Level: " << level << " | XP: " << xp << std::endl;
    }

    sqlite3_finalize(stmt);
}
