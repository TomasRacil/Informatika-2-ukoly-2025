#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>

class Lod
{
private:
    int x = 0;   // ship east(+)/west(-)
    int y = 0;   // ship north(+)/south(-)
    int wx = 10; // waypoint relative east
    int wy = 1;  // waypoint relative north
    std::string filename;

    void rotate_waypoint_right(int degrees)
    {
        degrees = ((degrees % 360) + 360) % 360;
        int nx, ny;
        switch (degrees)
        {
        case 0:
            return;
        case 90:
            nx = wy;
            ny = -wx;
            wx = nx;
            wy = ny;
            return;
        case 180:
            wx = -wx;
            wy = -wy;
            return;
        case 270:
            nx = -wy;
            ny = wx;
            wx = nx;
            wy = ny;
            return;
        default:
            return;
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
            return;
        }

        while (soubor >> radek)
        {
            if (radek.empty()) continue;
            char prikaz = radek[0];
            int hodnota = std::stoi(radek.substr(1));

            if (prikaz == 'F')
            {
                x += wx * hodnota;
                y += wy * hodnota;
            }
            else if (prikaz == 'L')
            {
                rotate_waypoint_right(360 - (hodnota % 360));
            }
            else if (prikaz == 'R')
            {
                rotate_waypoint_right(hodnota);
            }
            else
            {
                switch (prikaz)
                {
                case 'N':
                    wy += hodnota;
                    break;
                case 'S':
                    wy -= hodnota;
                    break;
                case 'E':
                    wx += hodnota;
                    break;
                case 'W':
                    wx -= hodnota;
                    break;
                default:
                    break;
                }
            }
        }
        soubor.close();
    }

    void vypis_pozici()
    {
        std::cout << "Pozice x: " << x << ", pozice y: " << y
                  << ", waypoint (wx,wy): (" << wx << "," << wy << ")"
                  << ", manhatnovska vzdalenost: " << std::abs(x) + std::abs(y) << std::endl;
    }
};

int main()
{
    Lod lod("data.txt");
    lod.navigace();
    lod.vypis_pozici();
    return 0;
}