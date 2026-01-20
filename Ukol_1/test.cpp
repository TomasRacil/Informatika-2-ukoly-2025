#include "gtest/gtest.h"
#include "main.cpp"

// Test Fixture pro sdílení dat mezi testy
class AnalysisTest : public ::testing::Test {
protected:
    // Tato metoda se zavolá před každým testem v této sadě
    void SetUp() override {
        fileContent = getFileContent("../text_k_analyze.txt");
    }

    std::string fileContent;
};

// Testy pro soubor s obsahem
TEST_F(AnalysisTest, characterCount) {
    EXPECT_EQ(countCharacters(fileContent), 262);
}

TEST_F(AnalysisTest, lineCount) {
    EXPECT_EQ(countLines(fileContent), 6);
}

TEST_F(AnalysisTest, wordCount) {
    EXPECT_EQ(countWords(fileContent), 44);
}

TEST_F(AnalysisTest, vowelCount) {
    EXPECT_EQ(countVowels(fileContent), 73);
}

// Samostatná sada testů pro prázdný vstup
TEST(EmptyContentTest, allCountsZero) {
    std::string emptyContent = "";
    EXPECT_EQ(countCharacters(emptyContent), 0);
    EXPECT_EQ(countLines(emptyContent), 0);
    EXPECT_EQ(countWords(emptyContent), 0);
    EXPECT_EQ(countVowels(emptyContent), 0);
}
