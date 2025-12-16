#include <iostream>
#include <string>

struct A {
    int value;
};

std::string operator*(char a, A b) {
    std::string test = "";
    for (int i = 0; i < b.value; i++) {
        test += a; 
    }
    return test;
};

std::string vynasob(char a, int b) {
    std::string test = "";
    for (int i = 0; i < b; i++) {
        test += a; 
    }
    return test;
};

std::string vynasob(std::string a, int b) {
    std::string test = "";
    for (int i = 0; i < b; i++) {
        test += a; 
    }
    return test;
}


int main(){
    A a = {6};
    std::cout << 'a'*a << std::endl;
    std::cout << vynasob('a', 6) << std::endl;
    std::cout << vynasob("a", 6) << std::endl;
}