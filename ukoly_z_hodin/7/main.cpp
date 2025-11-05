#include <iostream>
#include <string>
#include <fstream>

// NEDOKONCENO NESTIHAL JSEM A CHYBI TOHO HODNE V KODU

class Lod 
{
    private:
        int x = 0;
        int y = 0;
        int smer;
        std::string filename;

    public:
        Lod(std::string filename){
            this->filename=filename;

        }
        void navigace()
        {

        
            void zmen_smer(char smer, int stupne)
            {
                switch (smer)
                {
                    case 'P':
                        this->stupne=(this->stupne+stupne)%360;
                        break;
                    case 'L':
                        this->stupne=(this->stupne-stupne)%360;
                        if (this->stupne<0) this->stupne+=360;
                        break;
                    default:
                        break;
                }
            }
            void posun_dopredu(int kroky)
            {

            }
            void posun_smerem(char smer, int kroky)
            {
                switch (smer)
                {
                    case 'N':
                        y+=kroky;
                        break;
                    case 'S':
                        y-=kroky;
                        break;
                    case 'E':
                        x+=kroky;
                        break;
                    case 'W':
                        x-=kroky;
                        break;
                    defailt:
                        break;
                }
            }
            void vypis_pozici()
            {
                std::cout << "Pozice x: " << x << ", Pozice y: " << y << ", smer: " << smer << std::endl;
            }
    }
};
int main() 
{

    Lod lod("test.txt");
    //lod.navigace();
    lod.vypis_pozici();
    lod.zmen_smer('L', 180);
    lod.zmen_smer('L', 270);
    lod.zmen_smer('L', 90);
    lod.vypis_pozici();
    return 0;
}