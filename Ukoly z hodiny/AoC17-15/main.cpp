#include <iostream>
#include <algorithm>
using namespace std;

string decToBinary(int n) {
    
    string bin = "";
    while (n > 0) {
        // checking the mod 
		int bit = n%2;
      	bin.push_back('0' + bit);
        n /= 2;
    }
    
    // reverse the string 
	reverse(bin.begin(), bin.end());
    return bin;
}

void generator(int a, int b){    
    // declare seed value as unsigned int
    unsigned int seed;
    // Ask user input for seed value
    cout << "Enter the Seed Value: ";
    cin >> seed;

    // Seed the random number generator with user-provided
    // value
    srand(seed);

    // Generate and print a sequence of pseudo-random
    // numbers
    for (int i = 0; i < 5; ++i) {
        int pocet_shodnych = 0;
        long long randomNum = rand();
        long long randomNum2 = rand();
        a = randomNum;
        b = randomNum2;
        cout << "Random Number a " << i + 1 << " "
             << randomNum << endl;
        cout << "tady je ten binar pro a:  " << decToBinary(a) << endl;

        cout << "Random Number b " << i + 1 << " "
             << randomNum2 << endl;
        cout << "tady je ten binar pro a:  " << decToBinary(b) << endl;

        if (compare_last_bits(a, b)){
            pocet_shodnych++;
        }
    }

}
bool compare_last_bits(long a, long b){
    return a == b;
}

int main() {
    long a = 0;
    long b = 0;
    int binar = 12;
    generator(a, b);
    //cout << "tady je ten binar:  " << decToBinary(binar);
    return 0;
}