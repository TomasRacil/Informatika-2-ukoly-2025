#include <iostream>
#include <fstream>
#include <string>

using namespace std;



int main() {
    string soub;
    ifstream nactiStudentyZeSouboru("text.txt");
    while (getline(nactiStudentyZeSouboru, soub)) {
		cout << soub << endl;
    }
	
    nactiStudentyZeSouboru.close();
}