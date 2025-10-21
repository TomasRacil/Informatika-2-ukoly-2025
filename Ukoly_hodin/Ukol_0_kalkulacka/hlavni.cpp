#include <iostream>

std::string ZiskejH()
{
    try
    {
        std::string hodnota;
        std::getline(std::cin, hodnota); //std::cin >> name;
        return hodnota;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return "0";
    }
    
}

void VypisH(std::string hodnota)
{
    std::cout << hodnota;
}


int main() {
    int cislo;
    do
    {
        VypisH("1-BMI");
        VypisH("2-BMR");
        VypisH("3-Konec");
        std::cin >> cislo;
        if(cislo==1)
        {

        }
        else if(cislo==2)
        {

        }
        else if(cislo==3)
        {

        }
        else
        {
            std::cout << "Zkus to znova";
            continue;
        }
    }while(cislo==3);
    

    return 0;
}