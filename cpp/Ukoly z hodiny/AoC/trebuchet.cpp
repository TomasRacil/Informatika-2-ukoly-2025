#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(){
    string radek;
    int suma = 0;
    ifstream soubor("data.txt");
    if (!soubor.is_open()) {
        cout << "neotevrel se" << endl;    
    }
    else{
        while (getline(soubor, radek))
        {
            string cislo;
            //cout << radek << endl;
            for(char znak:radek){
                if (isdigit(znak))
                {
                   // cout << znak << endl; //proč vypisuje výsledek 149 když má být 58
                    cislo += znak;
                    break;
                }
            }
            for(int i = radek.length()-1; i>=0; i--){
                if(isdigit(radek[i])){
                    //cout << radek[i];
                    cislo += radek[i];
                    break; //chybel ti tento radek
                          //ukoncoval ti pripocitavani cisel z 2. radku
                }
            }
            suma += stoi(cislo);
        }
    }
    //chyba je v tom že sečte ta první čísla a pak připíše 5
    //na prvnim radku jsou cisla 1 a 3
    //na druhem 4, 3 a 5
    //on v druhem radku udela cislo 43 a pak za ne pripise 5
    cout << "toto je suma:     "<< suma;

    return 0;
}