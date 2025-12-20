#include <iostream>

class Obdelnik{
    private:
        int a = 7;
        int b = 5;
    public:
        void tisk(){
            std::cout<<"Strana a: "<<a<<", Strana b: "<<b<<std::endl;
        }
    public:
    void zmenA(int a){
        this ->a = a;
    }
    void zmenB(int b){
        this ->b = b;
    }
    /*void vypocitejObvod(){
        int obvod = 2 * (a + b);
        std::cout<<"Obvod je: "<<obvod<<std::endl;
    }
    void vypocitejObsah(){
        int obsah = a * b;
        std::cout<<"Obsah je: "<<obsah<<std::endl;
    }*/
   int obvod(){
        return 2 * (a + b);
    }
    int obsah(){
        return a * b;
    }
    Obdelnik(int a, int b){
        this ->a = a;
        this ->b = b;
        std::cout<<"Byl vytvoren obdelnik se stranami a: "<<a<<", b: "<<b<<std::endl;
    }
    ~Obdelnik(){
        std::cout<<"Byl zrusen obdelnik se stranami a: "<<a<<", b: "<<b<<std::endl;
    }
};

int main() {
    Obdelnik obdelnik1(7, 5);
    obdelnik1.tisk();
    obdelnik1.zmenA(5);
    obdelnik1.zmenB(10);
    obdelnik1.tisk();
    /*obdelnik1.vypocitejObvod();
    obdelnik1.vypocitejObsah();*/
    std::cout<<"Obvod je: "<<obdelnik1.obvod()<<std::endl;
    std::cout<<"Obsah je: "<<obdelnik1.obsah()<<std::endl;
    return 0;
}