#include "logger.h"
#include <fstream>

Logger::Logger(const std::string& fileName)
    : fileName(fileName), timeCounter(0) {}

void Logger::log(const std::string& uroven,
                 const std::string& objekt,
                 const std::string& zprava) {
    std::ofstream file(fileName, std::ios::app);
    if (file.is_open()) {
        timeCounter++;
        file << "[" << timeCounter << "] "
             << uroven << ": "
             << objekt << " - "
             << zprava << std::endl;
        file.close();
    }
}
