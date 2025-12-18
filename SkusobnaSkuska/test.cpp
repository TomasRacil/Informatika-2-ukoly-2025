#include <gtest/gtest.h>
#include <fstream>
#include <string>
#include <regex>
#include <cstdio> 

#include "logger.h"

const std::string TEST_LOG = "test_server.log";

class LoggerTest : public ::testing::Test {
protected:
    void SetUp() override {
        std::remove(TEST_LOG.c_str()); 
    }
};

int count_lines(const std::string& filename) {
    std::ifstream file(filename);
    int count = 0;
    std::string line;
    while (std::getline(file, line)) count++;
    return count;
}

TEST_F(LoggerTest, FileCreatedAndWritable) {
    Logger logger(TEST_LOG);
    logger.log("INFO", "System", "Start process");

    std::ifstream file(TEST_LOG);
    ASSERT_TRUE(file.is_open());
}

TEST_F(LoggerTest, CorrectLogFormat) {
    Logger logger(TEST_LOG);
    logger.log("ERROR", "Database", "Connection failed");

    std::ifstream file(TEST_LOG);
    std::string line;
    std::getline(file, line);

    std::regex pattern(R"(\[\d+\] ERROR: Database - Connection failed)");
    EXPECT_TRUE(std::regex_match(line, pattern));
}

TEST_F(LoggerTest, MultipleLinesAppended) {
    Logger logger(TEST_LOG);
    logger.log("INFO", "System", "Start process");
    logger.log("WARNING", "Server", "High response");
    logger.log("ERROR", "Database", "Disk full");

    EXPECT_EQ(count_lines(TEST_LOG), 3);
}

TEST_F(LoggerTest, HandlesEmptyMessage) {
    Logger logger(TEST_LOG);
    logger.log("INFO", "System", "");
    
    std::ifstream file(TEST_LOG);
    std::string line;
    std::getline(file, line);

    std::regex pattern(R"(\[\d+\] INFO: System - )");
    EXPECT_TRUE(std::regex_match(line, pattern));
}

TEST_F(LoggerTest, HandlesMultipleWritesSequentially) {
    Logger logger(TEST_LOG);
    for(int i=0; i<10; ++i)
        logger.log("INFO", "System", "Test " + std::to_string(i));

    EXPECT_EQ(count_lines(TEST_LOG), 10);
}
