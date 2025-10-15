#include <iostream>
#include <string>
#include <limits>
#include <climits>
#include <cmath>
#include <cctype>


using namespace std;



double promptDouble(const string &prompt, double minVal = -INFINITY, double maxVal = INFINITY) {
	double x;
	while (true) {
		cout << prompt;
		if (!(cin >> x)) {
			cout << "Neplatny vstup, prosim cislo." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}
		if (x < minVal || x > maxVal) {
			cout << "Hodnota mimo povoleny rozsah";
			if (minVal != -INFINITY) cout << " (min=" << minVal << ")";
			if (maxVal != INFINITY) cout << " (max=" << maxVal << ")";
			cout << ". Skus znovu." << endl;
			continue;
		}
		return x;
	}
}
char promptSex() {
	string s;
	while (true) {
		cout << "Pohlavi (M/F): ";
		if (!(cin >> s)) return 'M';
		if (s.empty()) continue;
		char c = toupper((unsigned char)s[0]);
		if (c == 'M' || c == 'F') return c;
		cout << "Prosim napiste pohlavi: M nebo F." << endl;
	}
}

double calcBMI(double weight, double height) {
	double h = height / 100.0;
	if (h <= 0) return 0.0;
	return weight / (h * h);
}

double calcBMR(double weight, double height, int age, char sex) {
	double bmr = 10.0 * weight + 6.25 * height - 5.0 * age;
	if (sex == 'M') bmr += 5.0;
	else bmr -= 161.0;
	return bmr;
}




int main() {
	auto promptInt = [](const string &prompt, int minVal = INT_MIN, int maxVal = INT_MAX) {
		int x;
		while (true) {
			cout << prompt;
			if (!(cin >> x)) {
				cout << "Neplatny vstup, prosim cele cislo." << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				continue;
			}
			if (x < minVal || x > maxVal) {
				cout << "Hodnota mimo povoleny rozsah";
				if (minVal != INT_MIN) cout << " (min=" << minVal << ")";
				if (maxVal != INT_MAX) cout << " (max=" << maxVal << ")";
				cout << ". Skus znovu." << endl;
				continue;
			}
			return x;
		}
	};

	cout << "Vitejte ve Fitness kalkulacke" << endl;

	while (true) {
		cout << "\nVyberte moznost:\n";
		cout << "  1) Vypocitat BMI\n";
		cout << "  2) Vypocitat BMR\n";
		cout << "  3) Exit\n";

		int choice = promptInt("Vyber (1-3): ", 1, 3);

		if (choice == 1) {
			double weight = promptDouble("Zadejte vasi hmotnost v kg: ", 10.0, 500.0);
			double height = promptDouble("Zadejte vasi vysku v cm: ", 50.0, 300.0);
			double bmi = calcBMI(weight, height);
			cout << "\nVysledky BMI:\n";
			cout << "BMI: " << bmi << " kg/m^2";
			if (bmi < 18.5) cout << "  (podvaha)";
			else if (bmi < 25.0) cout << "  (normalni hmotnost)";
			else if (bmi < 30.0) cout << "  (nadvaha)";
			else cout << "  (extremne obezni)";
			cout << "\n";
		} else if (choice == 2) {
			double weight = promptDouble("Zadejte vasi hmotnost v kg: ", 10.0, 500.0);
			double height = promptDouble("Zadejte vasi vysku v cm: ", 50.0, 300.0);
			int age = promptInt("Zadejte vas vek v letech: ", 1, 120);
			char sex = promptSex();
			double bmr = calcBMR(weight, height, age, sex);
			cout << "\nVysledky BMR:\n";
			cout << "BMR: " << bmr << " kcal/den\n";
		} else {
			cout << "\nDekuji za pouziti fitness kalkulacky" << endl;
			break;
		}
	}

	return 0;

}
