#include <iostream>
#include <fstream>

using namespace std;

class Lod{
    private:
    int x = 0;
    int y = 0;
    int stupne = 90;
    string filename;

    public:

    Lod(string filename)
    {
        this->filename = filename;
    }

    void posun_dopredu(int kroky)
    {
        kroky;
    }
};


class Waypoint{
    private:
        int x = 0;
        int y = 0;
        int stupne = 90;
    public:


    void zmeny_smeru(){        
        string radek;
        ifstream soubor(filename);
        if (!soubor.is_open())
        {
            cerr << "Chyba: Soubor '" << filename << "' se nepodařilo otevřít!" << endl;
        }

        while (soubor >> radek)
        {
            if (!radek.empty()){            }
        }
        soubor.close();
    }

    void rotateRight() {  
        int tmp = x;
        x = y;
        y = -tmp;
    }
    
    void zmen_smer(char smer, int stupne)
    {
        switch (smer)
        {
        case 'R':
            this->stupne = (this->stupne + stupne) % 360;
            break;
        case 'L':
            this->stupne = (this->stupne - stupne) % 360;
            if (this->stupne < 0)
                this->stupne += 360;
            break;
        default:
            break;
        }
    }
};

int main(){}