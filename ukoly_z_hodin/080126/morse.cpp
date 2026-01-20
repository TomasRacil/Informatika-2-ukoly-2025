#include <iostream>
#include <map>
#include <vector>
using namespace std;

string morse[26] = {
    ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",
    "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",
    "..-", "...-", ".--", "-..-", "-.--", "--.."
};

char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
map<char, string> morse_codes;

vector<string> convert_to_morse(string input) {
    vector<string> new_code = {};

    for (char s : input) {
        string morse_conv = morse_codes[s];

        new_code.push_back(morse_conv);
    }

    return new_code;
}

int main() {
    for (int i = 0; i < sizeof(alphabet) - 1; i++) {
        char letter = alphabet[i];
        string morse_code = morse[i];

        morse_codes[letter] = morse_code;
    }

    string input = "";

    cout << "Add your word" << endl;
    cin >> input;

    vector<string> new_morse = convert_to_morse(input);

    string result = "";

    for (string m_code : new_morse) {
        result += " " + m_code;
    }

    cout << "Your result: " << result << endl;

    return 0;
}