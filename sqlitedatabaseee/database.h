#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <string>

class Database {
public:
    Database(const std::string& path);
    ~Database();

    bool executeSQL(const std::string& sql);
    void printUsers();

private:
    sqlite3* db;
};

#endif // DATABASE_H
