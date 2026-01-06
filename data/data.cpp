#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {

    int number;
    int sum = 0;
    int numberCount = 0;

    ifstream File("data.txt");

    while (File >> number)
    {
        sum += number;
        numberCount++;
    }

    File.close();

    if (numberCount == 0) {
        cout << "File is empty." << endl;
        return 0;
    }

    double average = static_cast<double>(sum) / numberCount;

    cout << "Total numbers read from file: " << numberCount << endl;
    cout << "Sum: " << sum << endl;
    cout << "Average: " << average << endl;

    return 0;
}
