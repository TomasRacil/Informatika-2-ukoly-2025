#include <iostream>
#include <limits>
#include <string>

using namespace std;

double computeBMI(double weightKg, double heightM) {
	return weightKg / (heightM * heightM);
}

string bmiCategory(double bmi) {
	if (bmi < 18.5) return "Podváha";
	else if (bmi < 25.0) return "Normální váha";
	else if (bmi < 30.0) return "Nadváha";
	else return "Obezita";
}

double computeBMR(char sex, double weightKg, double heightM, int ageYears) {
	// Harris-Benedict (revised) formula expects height in cm
	double heightCm = heightM * 100.0;
	if (sex == 'm' || sex == 'M') {
		return 88.362 + (13.397 * weightKg) + (4.799 * heightCm) - (5.677 * ageYears);
	} else {
		// treat any non-m as female (expected: 'z' or 'Z')
		return 447.593 + (9.247 * weightKg) + (3.098 * heightCm) - (4.330 * ageYears);
	}
}

// Helpers to read validated input
void clearCin() {
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

double readDouble(const string &prompt) {
	double x;
	while (true) {
		cout << prompt;
		if (cin >> x) {
			if (x > 0) return x;
			cout << "Zadejte kladne cislo.\n";
		} else {
			cout << "Neplatny vstup. Zadejte cislo.\n";
			clearCin();
		}
	}
}

int readInt(const string &prompt) {
	int x;
	while (true) {
		cout << prompt;
		if (cin >> x) {
			if (x > 0) return x;
			cout << "Zadejte kladne cele cislo.\n";
		} else {
			cout << "Neplatny vstup. Zadejte cele cislo.\n";
			clearCin();
		}
	}
}

char readSex(const string &prompt) {
	string s;
	while (true) {
		cout << prompt;
		if (cin >> s && !s.empty()) {
			char c = s[0];
			if (c=='m' || c=='M' || c=='z' || c=='Z') return c;
			cout << "Neplatna volba pohlavi. Zadejte 'm' pro muze nebo 'z' pro zeny.\n";
		} else {
			cout << "Neplatny vstup.\n";
			clearCin();
		}
	}
}

int main() {
	int volba = 0;
	do {
		cout << "\n--- Fitness Kalkulacka ---\n";
		cout << "1. Spocitat BMI\n";
		cout << "2. Spocitat BMR\n";
		cout << "3. Konec\n";
		cout << "Vase volba: ";
		if (!(cin >> volba)) {
			cout << "Neplatny vstup. Zadejte cislo 1-3.\n";
			clearCin();
			volba = 0;
			continue;
		}

		switch (volba) {
			case 1: {
				double vaha = readDouble("Zadejte vahu v kg: ");
				double vyska = readDouble("Zadejte vysku v metrech (napr. 1.75): ");
				double bmi = computeBMI(vaha, vyska);
				cout.setf(std::ios::fixed); cout.precision(2);
				cout << "Vase BMI: " << bmi << "\n";
				cout << "Kategorie: " << bmiCategory(bmi) << "\n";
				break;
			}
			case 2: {
				double vaha = readDouble("Zadejte vahu v kg: ");
				double vyska = readDouble("Zadejte vysku v metrech (napr. 1.75): ");
				int vek = readInt("Zadejte vek v letech: ");
				char pohlavi = readSex("Zadejte pohlavi ('m' pro muze, 'z' pro zeny): ");
				double bmr = computeBMR(pohlavi, vaha, vyska, vek);
				cout.setf(std::ios::fixed); cout.precision(2);
				cout << "Vas odhad bazalniho metabolickeho vydeje (BMR): " << bmr << " kcal/den\n";
				break;
			}
			case 3:
				cout << "Dekuji za pouziti a nashledanou.\n";
				break;
			default:
				cout << "Neplatna volba, zadejte prosim cislo 1-3.\n";
				break;
		}

		// flush any leftover newline
		clearCin();

	} while (volba != 3);

	return 0;
}
