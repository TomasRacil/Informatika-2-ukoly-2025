#ifndef LOGGER_H
#define LOGGER_H

#include <string>

class Logger {
private:
    std::string fileName;
    int timeCounter;

public:
    Logger(const std::string& fileName);
    void log(const std::string& uroven,
             const std::string& objekt,
             const std::string& zprava);
};

#endif
