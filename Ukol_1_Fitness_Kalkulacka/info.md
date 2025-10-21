Praktické programování - Fitness Kalkulačka

Vytvořte konzolovou aplikaci "Fitness Kalkulačka", která uživateli nabídne menu s různými výpočty a bude se opakovaně zobrazovat, dokud ji uživatel neukončí.
 
Zadání:
Aplikace bude mít následující funkce:
 
Výpočet BMI: Načte váhu a výšku, spočítá BMI a vypíše slovní hodnocení.
Výpočet BMR (Bazální metabolický výdej): Načte váhu, výšku, věk a pohlaví, a spočítá BMR podle Harris-Benedictova vzorce.
Konec: Ukončí program.
 
Prvně to zkuste samostatně pokud nebudete vědět jak, tak tady je návod k řešení (Algoritmus):
Doporučuji postupovat podle následujících kroků. Pro přehlednost je ideální rozdělit logiku do samostatných funkcí.
 
Vytvořte hlavní smyčku programu:
Použijte do-while cyklus, který poběží, dokud uživatel nezvolí možnost ukončení.
Uvnitř cyklu si vytvořte proměnnou pro volbu uživatele (např. int volba).
Zobrazte menu a načtěte vstup:
Uvnitř cyklu vypište uživateli menu:
1. Spocitat BMI
2. Spocitat BMR
3. Konec
Vase volba:
Načtěte číslo volby do připravené proměnné (std::cin >> volba;).
Zpracujte volbu uživatele:
Použijte příkaz switch (volba) pro zpracování zadané hodnoty.
Implementujte jednotlivé case bloky:
case 1: (BMI)
Vytvořte si proměnné pro váhu (double vaha) a výšku (double vyska).
Vypište výzvy a načtěte od uživatele obě hodnoty.
Spočítejte BMI: double bmi = vaha / (vyska * vyska);.
Vypište výsledek.
Použijte vnořenou if-else if-else strukturu pro slovní hodnocení na základě hodnoty bmi.
Nezapomeňte na break; na konci case.
case 2: (BMR)
Vytvořte si proměnné pro váhu, výšku, věk a pohlaví (char pohlavi).
Načtěte od uživatele všechny potřebné hodnoty.
Pomocí if (pohlavi == 'm') a else if (pohlavi == 'z') vyberte správný vzorec pro výpočet.
Spočítejte BMR a uložte jej do proměnné (double bmr).
Vypište výsledek.
Nezapomeňte na break;.
case 3: (Konec)
Vypište rozloučení (např. "Dekuji za pouziti a nashledanou.").
break;.
default:
Pro případ, že uživatel zadá neplatnou volbu, vypište chybovou hlášku (např. "Neplatna volba, zadejte prosim cislo 1-3.").
break;.
Podmínka do-while cyklu:
Cyklus se bude opakovat, dokud platí podmínka volba != 3.