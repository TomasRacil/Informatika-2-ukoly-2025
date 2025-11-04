#include <string>
#include <fstream>
#include <iostream>

class Lod
{
private:
    int x = 0;
    int y = 0;
    int stupne = 90;
    std::string filename;
    char stupne_na_smer()
    {
        switch (stupne)
        {
        case 0:
            return 'N';
        case 90:
            return 'E';
        case 180:
            return 'S';
        case 270:
            return 'W';
        }
    }

public:
    Lod(std::string filename)
    {
        this->filename = filename;
    }
    void navigace()
    {
        std::string radek;
        std::ifstream soubor(filename);
        if (!soubor.is_open())
        {
            std::cerr << "Chyba: Soubor '" << filename << "' se nepodařilo otevřít!" << std::endl;
        }

        while (soubor >> radek)
        {
            if (!radek.empty())
            {
                char prikaz = radek[0];
                int hodnota = std::stoi(radek.substr(1));
                if (prikaz == 'F')
                {
                    posun_dopredu(hodnota);
                }
                else if (prikaz == 'L' || prikaz == 'R')
                {
                    zmen_smer(prikaz, hodnota);
                }
                else
                {
                    posun_smerem(prikaz, hodnota);
                }
            }
        }
        soubor.close();
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
    void posun_dopredu(int kroky)
    {
        posun_smerem(stupne_na_smer(), kroky);
    }
    
    void posun_smerem(char smer, int kroky)
    {
        switch (smer)
        {
        case 'N':
            y += kroky;
            break;
        case 'S':
            y -= kroky;
            break;
        case 'E':
            x += kroky;
            break;
        case 'W':
            x -= kroky;
            break;
        default:
            break;
        }
    }
    void vypis_pozici()
    {
        std::cout << "Pozice x: " << x << ", pozice y: " << y << ", smer: " 
        << stupne << ", manhatnovska vzdalenost: " << abs(x) + abs(y) << std::endl;
    }
};

int main()
{
    Lod lod("data.txt");
    lod.navigace();
    lod.vypis_pozici();
    return 0;
}