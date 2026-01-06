#include <iostream>
#include <limits>
using namespace std;

int discipline = 5;
int reputation = 5;
int performance = 5;


// úvod
void introduction() {
    cout << "\n";
    cout << "Vitej ve hre Dusanova kariera — psychologickem unikovem dobrodruzstvi.\n\n";
    cout << "V teto hre se stanes Dusanem, clovekem stojicim na krizovatce sveho zivota.\n";
    cout << "Kazde tve rozhodnuti ovlivni jeho cestu — jeho motivaci, uspech i cestu na vrchol.\n\n";
    cout << "Na kazdem kroku te cekaji tri moznosti.\n";
    cout << "Rozhoduj se s rozvahou... protoze tve ciny urci, zda Dusan dosahne velikosti — nebo vse ztrati.\n\n";
    cout << "Stiskni ENTER pro zahajeni sve cesty.\n";

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // vycisteni bufferu pro jistotu
    cin.get();
}


// ==
void line () {
    cout << "==============================================\n";
}

void showStats() {
    cout << "\n--- STATY HRÁČE ---\n";
    cout << "Disciplína: " << discipline << endl;
    cout << "Reputace:   " << reputation << endl;
    cout << "Výkon:      " << performance << endl;
    cout << "--------------------\n\n";
}


void pauseMenu() {
    cout << "\n(Stiskni ENTER pro pokracovani nebo 'S' pro statistiky)\n";

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string input;
    getline(cin, input);

    if (input == "s" || input == "S") {
        showStats();
        cout << "Stiskni ENTER pro navrat...\n";
        cin.get();
    }
}


// funkce co cte volby
int ctiVolbu(int minimum, int maximum) {
    int cislo;

    while (true) {
        cout << "> ";
        cin >> cislo;

        // pokud nekdo napise pismeno nebo blbost
        if (!cin) {
            cout << "Zadej cislo!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        // kontrola rozsahu
        if (cislo >= minimum && cislo <= maximum) {
            return cislo;
        }

        cout << "Zadej cislo " << minimum << "-" << maximum << endl;
    }
}

// SCENA 1  JEDNANI S AGENTEM 
void scena1() {
    int volba;

    cout << endl;
    cout << "SCENA 1 - Jednani s agentem" << endl;

    // 1
    line();
    cout << "1) Vaclav: \"Dusane, mam tu nabidku z FC Drakonia.\"\n";
    cout << "Trileta smlouva, 85 tisic mesicne a premie za goly. Co myslis?\n";
    cout << "1) \"Podepis to, chci hrat!\"\n";
    cout << "2) \"Zkus vyjednat vic.\"\n";
    cout << "3) \"Neni to malo?\"\n";
    volba = ctiVolbu(1, 3);
    if (volba == 1) {
        cout << "Vaclav: \"Beru to. Zitra tiskovka.\"\n";
        discipline += 1;
    } else if (volba == 2) {
        cout << "Vaclav: \"Ok, zkusim zatlacit. Zitra to potvrdime.\"\n";
        reputation += 1;
    } else {
        cout << "Vaclav: \"Hele, Drakonia je dobra sance. Promysli to.\"\n";
        performance -= 1;
    }

    // 2
    line();
    cout << "2) Vaclav: \"Dobre, ale vis, ze tlak bude obrovsky. Jsi pripraven?\"\n";
    cout << "1) \"Narodil jsem se pro tlak.\"\n";
    cout << "2) \"Snad to zvladnu.\"\n";
    cout << "3) \"Nevim, nikdy jsem to nezazil.\"\n";
    volba = ctiVolbu(1, 3);
    if (volba == 1) {
        cout << "Vaclav: \"Tak to chci slyset.\"\n";
        discipline += 1;
    } else if (volba == 2) {
        cout << "Vaclav: \"Strach je normalni, hlavne ho prekonej.\"\n";
        performance += 1;
    } else {
        cout << "Vaclav: \"Tak to bude tvoje prvni velka zkouska.\"\n";
        discipline -= 1;
    }

    // 3
    line();
    cout << "3) Vaclav: \"Jake cislo chces na dres?\"\n";
    cout << "1) \"Desitku. Jako kapitan.\"\n";
    cout << "2) \"Cokoliv, jsem tu novy.\"\n";
    cout << "3) \"Sedmicku, ta mi prinasi stesti.\"\n";
    volba = ctiVolbu(1, 3);
    if (volba == 1) {
        cout << "Vaclav: \"Desitka? Odvazny vyber.\"\n";
        reputation += 1;
    } else if (volba == 2) {
        cout << "Vaclav: \"Skromnost se ceni.\"\n";
    } else {
        cout << "Vaclav: \"Sedmicka ti muze sednout.\"\n";
        performance += 1;
    }

    // 4
    line();
    cout << "4) Vaclav: \"Mam ti tam pripsat i bonus za goly?\"\n";
    cout << "1) \"Jasne, budu je potrebovat.\"\n";
    cout << "2) \"Hlavne at hraju.\"\n";
    cout << "3) \"Nech to byt, neresim prachy.\"\n";
    volba = ctiVolbu(1, 3);
    if (volba == 1) {
        cout << "Vaclav: \"Tak jo, bonusy tam dam.\"\n";
        performance += 1;
    } else if (volba == 2) {
        cout << "Vaclav: \"To rad slysim, minuta je vic nez penize.\"\n";
        discipline += 1;
    } else {
        cout << "Vaclav: \"Takovy pristup dneska nema skoro nikdo.\"\n";
        reputation += 1;
    }

    // 5
    line();
    cout << "5) Vaclav: \"Novinari uz o tobe pisou. Mam to komentovat?\"\n";
    cout << "1) \"Jo, ukaz jim, ze prichazi hvezda.\"\n";
    cout << "2) \"Nech to byt, chci klid.\"\n";
    cout << "3) \"Rekni jim, ze jdu makat.\"\n";
    volba = ctiVolbu(1, 3);
    if (volba == 1) {
        cout << "Vaclav: \"Dobře, udelam z tebe velke jmeno.\"\n";
        reputation += 1;
    } else if (volba == 2) {
        cout << "Vaclav: \"Jasne, drzime se mimo svetla reflektoru.\"\n";
        discipline += 1;
    } else {
        cout << "Vaclav: \"Skromnost, ale ambice. To se libi.\"\n";
        performance += 1;
    }

    // 6
    line();
    cout << "6) Vaclav: \"Zitra mas podpis v klubu. Trener Honza nesnasi opozdilce.\"\n";
    cout << "1) \"Budu tam prvni.\"\n";
    cout << "2) \"V pohode, stihnu to.\"\n";
    cout << "3) \"A co, jeden den se nic nestane.\"\n";
    volba = ctiVolbu(1, 3);
    if (volba == 1) {
        cout << "Vaclav: \"Vyborne, prvni dojem je klicovy.\"\n";
        discipline += 1;
    } else if (volba == 2) {
        cout << "Vaclav: \"Hlavne to nezasp.\"\n";
    } else {
        cout << "Vaclav: \"Takovy pristup se trenerovi libit nebude.\"\n";
        discipline -= 1;
    }

    // 7
    line();
    cout << "7) Vaclav: \"Kazda volba muze zmenit tvuj zivot. Uvedomujes si to?\"\n";
    cout << "1) \"Jasne, davam si pozor.\"\n";
    cout << "2) \"Uvidime, jak to dopadne.\"\n";
    cout << "3) \"Zivot je hra.\"\n";
    volba = ctiVolbu(1, 3);
    if (volba == 1) {
        cout << "Vaclav: \"Rozumne.\"\n";
        discipline += 1;
    } else if (volba == 2) {
        cout << "Vaclav: \"Tak doufej, ze mas stesti.\"\n";
    } else {
        cout << "Vaclav: \"Tak hraj chytre.\"\n";
        performance += 1;
    }

    // 8
    line();
    cout << "8) Vaclav: \"Takze... potvrzuju prestup?\"\n";
    cout << "1) \"Ano, podepisuj.\"\n";
    cout << "2) \"Pockej, premyslim.\"\n";
    cout << "3) \"Podepis, ale pod podminkami.\"\n";
    volba = ctiVolbu(1, 3);
    if (volba == 1) {
        cout << "Vaclav: \"Hotovo. Od zitra jsi hrac Drakonie.\"\n";
        discipline += 1;performance += 1;
    } else if (volba == 2) {
        cout << "Vaclav: \"Ok, necham ti cas.\"\n";
    } else {
        cout << "Vaclav: \"Zkusim vyjednat co pujde.\"\n";
        reputation += 1;
    }

    cout << endl << "[Konec sceny 1]" << endl;
}


// SCENA 2 – PODPIS V KLUBU 
void scena2() {
    int volba;

    line();
    cout << "SCENA 2 - Podpis v klubu" << endl;
    line();

    // 9
    line();
    cout << "9) Honza: \"Vitej v Drakonii. U me plati dve veci: makat a byt vcas.\"\n";
    cout << "1) \"Rozumim, trenere.\"\n";
    cout << "2) \"Jasne, jen zadny stres.\"\n";
    cout << "3) \"Tak to mame spolecne.\"\n";
    volba = ctiVolbu(1, 3);

    // 10
    line();
    cout << "10) Honza: \"Zitra trenink v 7:00. Prijdes?\"\n";
    cout << "1) \"Budu tam driv.\"\n";
    cout << "2) \"Zkusim to stihnout.\"\n";
    cout << "3) \"Sedm? To je vrazda.\"\n";
    volba = ctiVolbu(1, 3);

    // 11
    line();
    cout << "11) Honza: \"Jak se citis po podpisu?\"\n";
    cout << "1) \"Motivovane.\"\n";
    cout << "2) \"Jsem nervozni.\"\n";
    cout << "3) \"V klidu, mam to pod kontrolou.\"\n";
    volba = ctiVolbu(1, 3);

    // 12
    line();
    cout << "12) Honza: \"Mas velky potencial, ale i ego. Co prevazi?\"\n";
    cout << "1) \"Pokora.\"\n";
    cout << "2) \"Ego me zene kupredu.\"\n";
    cout << "3) \"Zalezi na dni.\"\n";
    volba = ctiVolbu(1, 3);

    // 13
    line();
    cout << "13) Lukas: \"Hele kamo, vecer hospoda. Zapijem to, ne?\"\n";
    cout << "1) \"Jasne!\"\n";
    cout << "2) \"Ne, chci byt fit.\"\n";
    cout << "3) \"Jedno pivo a domu.\"\n";
    volba = ctiVolbu(1, 3);

    // 14
    line();
    cout << "14) Honza (k Dusanovi): \"Takhle to zacina. Jeden drink, a pak to jde z kopce.\"\n";
    cout << "1) \"Nebojte, vim, co delam.\"\n";
    cout << "2) \"Mate pravdu.\"\n";
    cout << "3) \"Jednou se to prece musi oslavit.\"\n";
    volba = ctiVolbu(1, 3);

    // 15
    line();
    cout << "15) Vaclav (vola): \"Pamatuj, Honza te sleduje. Nepokaz to prvni den.\"\n";
    cout << "1) \"Neboj, dam si pozor.\"\n";
    cout << "2) \"Zvladnu to i s pivem.\"\n";
    cout << "3) \"To je jen trenink, ne valka.\"\n";
    volba = ctiVolbu(1, 3);

    cout << endl << "[Konec sceny 2]" << endl;
}

// SCENA 3 - HOSPODA NEBO DOMOW
void scena3() {
    int volba;

    line();
    cout << "SCENA 3 - Hospoda nebo domov" << endl;
    line();

    // 16
    line();
    cout << "16) Lukas: \"Na Dusana! Novy hrac Drakonie!\"\n";
    cout << "1) \"Na zdravi!\"\n";
    cout << "2) \"Diky, ale jen jedno.\"\n";
    cout << "3) \"Nepiju, kamo.\"\n";
    volba = ctiVolbu(1, 3);

    // 17
    line();
    cout << "17) Lukas: \"Tak povidej, jake to je podepsat profik?\"\n";
    cout << "1) \"Uzasny pocit.\"\n";
    cout << "2) \"Uprimne? Citim tlak.\"\n";
    cout << "3) \"Je to jen smlouva, klid.\"\n";
    volba = ctiVolbu(1, 3);

    // 18
    line();
    cout << "18) Lukas: \"Dej si jeste jedno, nekaz partu.\"\n";
    cout << "1) \"Dobre, ale posledni.\"\n";
    cout << "2) \"Ani nahodou.\"\n";
    cout << "3) \"At zije Drakonia!\"\n";
    volba = ctiVolbu(1, 3);

    // 19
    line();
    cout << "19) Lukas: \"Vis, ze trener tohle nesnasi?\"\n";
    cout << "1) \"Nevi, neboli.\"\n";
    cout << "2) \"Tak radsi pujdu.\"\n";
    cout << "3) \"Jedno pivo nikomu neublizi.\"\n";
    volba = ctiVolbu(1, 3);

    // 20
    line();
    cout << "20) Vaclav (vola): \"Jsi v hospode? Trener to zjisti.\"\n";
    cout << "1) \"Ne, jen voda!\"\n";
    cout << "2) \"Jen chvilku, slibuju.\"\n";
    cout << "3) \"Klid, Venco, mam to pod kontrolou.\"\n";
    volba = ctiVolbu(1, 3);

    // 21
    line();
    cout << "21) Rano – trenink: \"Dusane, proc mas kruhy pod ocima?\"\n";
    cout << "1) \"Spatne jsem spal.\"\n";
    cout << "2) \"Byl jsem venku.\"\n";
    cout << "3) \"To je alergie.\"\n";
    volba = ctiVolbu(1, 3);

    // 22
    line();
    cout << "22) Honza: \"Takhle to zacina. Mas talent, ale zadnou vuli.\"\n";
    cout << "1) \"Omlouvam se.\"\n";
    cout << "2) \"To se uz nestane.\"\n";
    cout << "3) \"To prehanite.\"\n";
    volba = ctiVolbu(1, 3);

    // 23
    line();
    cout << "23) Lukas: \"Neber to vazne, trener ma vzdycky kecy.\"\n";
    cout << "1) \"Ma pravdu.\"\n";
    cout << "2) \"Nekdy jo.\"\n";
    cout << "3) \"Kaslu na nej.\"\n";
    volba = ctiVolbu(1, 3);

    cout << endl << "[Konec sceny 3]" << endl;
}

// SCENA 4 - PRVNI ZAPAS
void scena4() {
    int volba;

    line();
    cout << "SCENA 4 - Prvni zapas" << endl;
    line();

    // 24
    line();
    cout << "24) Honza: \"Jdes na hriste. Mas 15 minut. Co udelas?\"\n";
    cout << "1) \"Makam naplno.\"\n";
    cout << "2) \"To je malo casu.\"\n";
    cout << "3) \"Dam gol.\"\n";
    volba = ctiVolbu(1, 3);

    // 25
    line();
    cout << "25) Na hristi: \"Balon mas u nohy.\"\n";
    cout << "1) \"Prihravam spoluhraci.\"\n";
    cout << "2) \"Strilim!\"\n";
    cout << "3) \"Zpanikarim.\"\n";
    volba = ctiVolbu(1, 3);

    // 26
    line();
    cout << "26) Fanousci buci:\n";
    cout << "1) \"Soustredim se dal.\"\n";
    cout << "2) \"Rozciluje me to.\"\n";
    cout << "3) \"Mavnu na ne.\"\n";
    volba = ctiVolbu(1, 3);

    // 27
    line();
    cout << "27) Po zapase Honza: \"Nebyl to spatny debut.\"\n";
    cout << "1) \"Diky, trenere.\"\n";
    cout << "2) \"Chtel jsem dat vic.\"\n";
    cout << "3) \"Bylo to v pohode.\"\n";
    volba = ctiVolbu(1, 3);

    // 28
    line();
    cout << "28) Vaclav: \"Dobra prace, mam nove nabidky.\"\n";
    cout << "1) \"Jeste jsem nic nedokazal.\"\n";
    cout << "2) \"To zni skvele!\"\n";
    cout << "3) \"Kolik za to?\"\n";
    volba = ctiVolbu(1, 3);

    // 29
    line();
    cout << "29) Lukas: \"Slavime, jsi hvezda!\"\n";
    cout << "1) \"Ne, jdu regenerovat.\"\n";
    cout << "2) \"Jedno pivo.\"\n";
    cout << "3) \"Celou noc!\"\n";
    volba = ctiVolbu(1, 3);

    // 30
    line();
    cout << "30) Rano: \"Zaspal jsi trenink.\"\n";
    cout << "1) \"Promin.\"\n";
    cout << "2) \"Nestalo se nic.\"\n";
    cout << "3) \"Byl jsem hvezda, ne?\"\n";
    volba = ctiVolbu(1, 3);

    cout << endl << "[Konec sceny 4]" << endl;
}

// SCENA 5 – FINALE 
void scena5() {
    int volba;

    line();
    cout << "SCENA 5 - Finale" << endl;
    line();

    // 31
    line();
    cout << "31) Honza: \"Tak, konci sezona. Jsem na tebe pysny – nebo zklamany?\"\n";
    cout << "1) \"Dekuji za duveru.\"\n";
    cout << "2) \"Delal jsem, co slo.\"\n";
    cout << "3) \"Muzu za to alkohol.\"\n";
    volba = ctiVolbu(1, 3);

    // 32
    line();
    cout << "32) Vaclav: \"Z Italie prisla nabidka. Chces prestoupit?\"\n";
    cout << "1) \"Ano, jsem pripraven.\"\n";
    cout << "2) \"Nevim, jsem unaveny.\"\n";
    cout << "3) \"Kolik plati?\"\n";
    volba = ctiVolbu(1, 3);

    // 33
    line();
    cout << "33) Lukas: \"Jdem to zapit, bracho.\"\n";
    cout << "1) \"Ne, musim letet na trenink.\"\n";
    cout << "2) \"Jedno na rozloucenou.\"\n";
    cout << "3) \"Nalej mi dvakrat.\"\n";
    volba = ctiVolbu(1, 3);

    // 34
    line();
    cout << "34) Honza: \"Mas posledni slovo. Kdo jsi, Dusane?\"\n";
    cout << "1) \"Profesional.\"\n";
    cout << "2) \"Ztraceny talent.\"\n";
    cout << "3) \"Clovek, co zil naplno.\"\n";
    volba = ctiVolbu(1, 3);

    // 35
    line();
    cout << "35) Vaclav: \"Dobre, synku. Tak tohle je tvuj pribeh.\"\n";
    cout << "1) \"Hvezda sezony.\"\n";
    cout << "2) \"Alkoholik.\"\n";
    cout << "3) \"Nekde mezi.\"\n";
    volba = ctiVolbu(1, 3);

    cout << endl << "[Konec sceny 5]" << endl;
}

int main() {
    
    line();
    cout << "  Vitejte v pribehove hre - Dusanova kariera.\n";
    line ();

    introduction();

    scena1();
    pauseMenu();

    scena2();
    pauseMenu();
    
    scena3();
    pauseMenu();
    
    scena4();
    pauseMenu();
    scena5();
    pauseMenu();


    cout << endl << "Diky za hrani" << endl;
    return 0;
}

