#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

 int main() {
 int volba;
    

    do {     cout << "Vitejte ve fitness kalkulacce!" << endl;
             cout << "-------------------------------" << endl;
             cout << "Zadejte 1 pro vypocet BMI" << endl;
             cout << "Zadejte 2 pro vypocet BMR" << endl;
             cout << "Zadejte 3 pro ukonceni" << endl;
             cout << "Vase volba: ";
             cin >> volba ;


    switch (volba) {
            case 1 : {
             double vyska, vaha;
             
             cout << "Zadejte vasi vysku v metrech: ";
             cin >> vyska;
             cout << "Zadejte vasi vahu v kilogramech: ";
             cin >> vaha;
             double bmi = vaha / (vyska * vyska);
             cout << "Vase BMI je : " << setprecision(4) <<  bmi << endl;
             if (bmi <= 18.5){
             cout << "Mate podvahu!" << endl << endl;
             }
             else if (bmi >= 18.6 && bmi < 24.9){
             cout << "Jste v norme! "  << endl << endl; 
             }
             else if (bmi >= 25 && bmi < 29.9){
             cout << "Mate nadvahu! " << endl << endl;
             }
             else  {
             cout << "Trpite obezitou! " << endl << endl;
             }
             break;
            }
      
            case 2 : {
             double vaha, vek, vyska;
             char pohlavi;
             double bmr;
             

             cout << "Zadejte vasi vahu v kilogramech: " ;
             cin >> vaha;
             cout << "Zadejte vas vek: " ;
             cin >> vek;
             cout << "Zadejte vasi vysku v metrech: " ;
             cin >> vyska;
             cout << "Zadejte vase pohlavi m/z: " ;
             cin >> pohlavi;
             if (pohlavi == 'm' || pohlavi == 'M'){
             bmr = 66.5  + (13.76 * vaha)  + (5.003 * vyska)  - (6.755 * vek);
             }
             else if (pohlavi == 'z' || pohlavi == 'Z'){
             bmr = 655 + (9.563 * vaha)  + (1.85 * 100 * vyska )  - (4.676 * vek);
             }
            else {
             cout << "Neplatne pohlavi" << endl << endl;
             break;
             }

             cout << "Vase BMR je: " << bmr << " kcal/den" << endl << endl;
             break;
            }

            case 3: 
             cout << "Dekuji za vyuziti kalkulacky a nashledanou!" << endl << endl;
             break;

            default: 
             cout << "Neplatna volba. Prosim, zadejte cislo 1-3: " << endl;
             break;
       

        }
   }
   while (volba != 3);

   return 0;
 }