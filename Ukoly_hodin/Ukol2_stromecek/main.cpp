#include <iostream>

using namespace std;

int main() 
{
    int pocetp = 0;
    chyba1:
    cout << "Napis pocet pater stromecku: ";
    try
    {
        cin >> pocetp;
    }
    catch(const std::exception& e)
    {
        cout << "Zkus to znova: ";
        goto chyba1;
    }

    for(int i =0; i< pocetp; i++)
    {
        
            int x = pocetp-i;
            for(int a =0;a<x;a++)
            {
                cout << " ";
            }
             if(i == 0)
            {
                cout << "-";
            }
            for(int b =0;b<i*2;b++)
            {
                cout << "-";
            }
            for(int c=0;c<x;c++)
            {
                cout << " ";
            }
        cout << '\n';
    }

}