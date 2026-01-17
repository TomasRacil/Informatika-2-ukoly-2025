#include <iostream>
#include <string>

using namespace std;

class Obdelnik
{
private:
    int a = 10;
    int b = 12;

public:
    void tisk()
    {
        cout << "Strana a: " << a << ", strana b: " << b << endl;
        cout << "Obvod: " << obvod() << "cm, obsah: " << obsah() << "cm2" << endl;
    }
    void zmena_a(int a)
    {
        this->a = a;
    }
    void zmena_b(int b)
    {
        this->b = b;
    }
    int obvod(){
        return 2 * (a + b);
    }
    int obsah(){
        return a * b;
    }
    Obdelnik(int a, int b) {
        this->a = a;
        this->b = b;

        cout << "Obdelnik vytvoren!" << endl;
    }
    ~Obdelnik() {
        // 
    }
};

int main()
{
    Obdelnik novy_obdelnik(10, 15);
    Obdelnik* pobdelnik1 = &novy_obdelnik;

    novy_obdelnik.tisk();
    novy_obdelnik.zmena_a(5);
    novy_obdelnik.zmena_b(8);
    novy_obdelnik.tisk();

    return 0;
}