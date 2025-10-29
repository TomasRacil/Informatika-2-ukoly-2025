#include <iostream>
#include <string>

class Obdelnik
{
    private:
    int a=10;
    int b=12;
    
    public:
    void tisk()
    {
        std::cout<< "Strana a: "<< a << ", Strana b: "<< b <<std::endl;
        std::cout<<"Obvod: "<<obvod()<<", Obsah: "<<obsah()<<std::endl;
    }

    void zmen_a(int a)
    {
        this->a=a;
    }

    void zmen_b(int b)
    {
        this->b=b;
    }

    int obvod()
    {
        return 2*(a+b);
    }

    int obsah()
    {
        return a*b;
    }
};

int main()
{
    Obdelnik obdelnik1;  
    obdelnik1.tisk();
    obdelnik1.zmen_a(5);
    obdelnik1.zmen_b(8);
    obdelnik1.tisk();
    return 0;
}
