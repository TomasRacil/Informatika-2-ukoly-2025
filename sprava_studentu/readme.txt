Navrhněte Datové Struktury:
Vytvořte strukturu Student, která bude obsahovat minimálně:
int id
std::string jmeno (celé jméno)
double prumer (studijní průměr)
Vytvořte strukturu Uzel (Node) pro spojový seznam. Každý uzel bude obsahovat:
Data typu Student.
Ukazatel (Uzel*) na následující uzel.
Implementujte Funkce: Navrhněte a implementujte následující funkce:
parsujRadek(const std::string& radek):
Vstup: Řetězec radek ve formátu "ID,Jmeno Prijmeni,Prumer" (např. "101, Jan Novak, 1.8").
Výstup: Objekt Student naplněný daty z řádku.
Doporučení: Použijte std::stringstream nebo metody string::find a string::substr pro rozdělení řádku. Použijte std::stoi a std::stod pro konverzi. Ošetřete možné chyby formátu (např. pomocí try-catch).
pridejStudentaNaKonec(Uzel pHead, Student data):**
Dynamicky alokuje nový Uzel.
Přidá uzel obsahující data studenta na konec spojového seznamu, na který ukazuje *pHead.
Správně ošetřete případ prázdného seznamu.
Pozor na ukazatel na ukazatel pHead!
nactiStudentyZeSouboru(const std::string& nazevSouboru, Uzel pHead):**
Otevře textový soubor nazevSouboru.
Čte soubor řádek po řádku.
Pro každý platný řádek zavolá parsujRadek a výsledek přidá do seznamu pomocí pridejStudentaNaKonec.
Ignorujte prázdné řádky a řádky začínající # (komentáře). Ošetřete chyby při parsování řádků.
vypisSeznam(Uzel head):*
Projdi spojový seznam od začátku (head) a vypiš data všech studentů v přehledném formátu. Můžete si pomoci přetížením operator<< pro struct Student.
setridSeznamPodlePrumeru(Uzel head):*
Implementujte třídicí algoritmus (např. Bubble Sort nebo Selection Sort), který seřadí studenty ve spojovém seznamu vzestupně podle jejich prumer.
Tip: Může být jednodušší prohazovat pouze data mezi uzly než měnit ukazatele dalsi. Budete potřebovat pomocnou funkci pro prohození (swap).
ulozStudentyDoSouboru(const std::string& nazevSouboru, Uzel head):*
Otevře textový soubor nazevSouboru pro zápis (přepíše existující soubor).
Projdi spojový seznam od začátku (head).
Pro každý uzel zapiš data studenta (id, jmeno, prumer) do souboru ve stejném formátu CSV jako vstupní soubor (oddělené čárkou). Každý student bude na novém řádku.
Nezapomeňte na kontrolu, zda se soubor podařilo otevřít pro zápis (std::ofstream).
zrusSeznam(Uzel pHead):**
Projdi celý spojový seznam a korektně uvolni paměť (delete) všech alokovaných uzlů.
Na konci nastav *pHead na nullptr.
Vytvořte main funkci:
Deklarujte ukazatel na hlavu seznamu (Uzel* head = nullptr;).
Definujte názvy vstupního (studenti.txt) a výstupního souboru (např. studenti_serazeno.txt).
Zavolejte nactiStudentyZeSouboru pro načtení dat z vstupního souboru.
Vytiskněte nenačtený seznam pomocí vypisSeznam.
Přidejte nějaký záznam do seznamu.
Zavolejte setridSeznamPodlePrumeru.
Vytiskněte seřazený seznam pomocí vypisSeznam.
Zavolejte ulozStudentyDoSouboru pro uložení seřazeného seznamu do výstupního souboru.
Nezapomeňte na konci programu zavolat zrusSeznam pro uvolnění veškeré alokované paměti!
Vstupní data: Použijte soubor studenti.txt.