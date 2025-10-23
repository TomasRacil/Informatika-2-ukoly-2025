#include <iostream>
#include <string>
#include <fstream>

using namespace std;

ifstream soubor("text.txt");
string radek;
int vysledek =0;

int main() {
    if(!soubor.is_open())
    {
        cout << "Nelze otevrit soubor";
    }
    else
    {
        while(getline(soubor, radek))
        {
            string cislice;
            for(char c : radek)
            {
                if(isdigit(c))
                {
                cislice += c;
                break;
                }
            }
            for(int i=radek.size()-1;i>0;i--)
            {
                if(isdigit(radek[i]))
                {
                cislice += radek[i];
                break;
                }
            }
            vysledek += (int)stoi(cislice);
        }
        cout << vysledek;
    }

}