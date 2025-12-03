#ifdef __TEST__

#include <gtest/gtest.h>
#include "valecnik.h"
#include "mag.h"

TEST(RPGTest, PostavaZivoty) {
    Postava p("Dummy", 100, 10);
    p.prijmiUtok(30);
    EXPECT_EQ(p.getZivoty(), 70);
    
    p.prijmiUtok(100);
    EXPECT_EQ(p.getZivoty(), 0) << "Zivoty by nemely klesnout pod 0";
    EXPECT_FALSE(p.jeZiva());
}

TEST(RPGTest, ValecnikArmor) {
    Valecnik v("Tank", 100, 10, 5); // 5 Armor
    
    // Útok za 20 -> Brnění 5 -> Výsledek 15 dmg
    v.prijmiUtok(20);
    EXPECT_EQ(v.getZivoty(), 85);

    // Útok za 4 -> Brnění 5 -> Výsledek 0 dmg
    v.prijmiUtok(4);
    EXPECT_EQ(v.getZivoty(), 85);
}

TEST(RPGTest, ValecnikZurivost) {
    Valecnik v("Barbar", 200, 10, 0);
    
    v.prijmiUtok(150); 
    
    Valecnik cil("Terč", 100, 0, 0);

    v.utok(cil);

    EXPECT_EQ(cil.getZivoty(), 85) << "Valecnik pod 30% Max HP by mel davat 1.5x poskozeni!";
}

TEST(RPGTest, MagManaMechanika) {
    Mag m("Gandalf", 100, 10, 10);
    Valecnik cil("Terč", 1000, 0, 0);

    // 1. Útok: Má manu -> Fireball (2x síla = 20 dmg)
    m.utok(cil);
    EXPECT_EQ(cil.getZivoty(), 980);
    
    // 2. Útok: Došla mana (má 0) -> Hůl (0.5x síla = 5 dmg)
    m.utok(cil);
    EXPECT_EQ(cil.getZivoty(), 975);

    // Mág by měl zregenerovat 5 many. Další útok stále holí (potřebuje 10).
    m.utok(cil);
    EXPECT_EQ(cil.getZivoty(), 970);
}

TEST(RPGTest, Polymorfismus) {
    // Test ověřuje, zda používáte 'virtual' a 'override'.
    Postava* p = new Mag("Merlin", 100, 10, 50);
    Valecnik cil("Terč", 100, 0, 0);
    
    // Voláme utok() přes ukazatel na Postavu.
    p->utok(cil); 
    
    EXPECT_EQ(cil.getZivoty(), 80) << "Polymorfismus nefunguje! Volá se metoda předka místo potomka.";

    delete p;
}

#endif 