# **Zkouška z Informatiky – Varianta T: Analýza Serverových Logů**

Čas: 90 minut  
Povolené pomůcky: Offline dokumentace, studijní materiály.  
Odevzdání: Soubory `logger.h`, `logger.cpp`, `main.cpp`, `analyza.py`.

## **Část 1: C++ (Generátor logů) – 20 bodů**

Vaším úkolem je vytvořit C++ aplikaci, která simuluje činnost serveru a zapisuje události do textového souboru.

### **Zadání:**

1. **Vytvořte třídu `Logger`:**  
   * Atribut: název souboru (např. `server.log`).  
   * Metoda: `void log(std::string uroven, std::string objekt, std::string zprava)`.  
   * Metoda otevře soubor (režim append), zapíše řádek ve formátu `[CAS] LEVEL: Objekt - Zprava` a soubor zavře.  
     * Příklad: `[17001] ERROR: Databáze - Connection failed`  
   * Čas simulujte jednoduše (např. pořadové číslo operace).  
2. **Vytvořte třídu `Server`:**  
   * Metoda `run(int pocetUdalosti)`: V cyklu vygeneruje `pocetUdalosti` náhodných logů.  
   * V každém kroku náhodně vyberte:  
     1. **Úroveň:** `INFO`, `WARNING`, `ERROR`.  
     2. **Objekt:** `Databáze`, `Server`, `System`.  
     3. **Zprávu:** Vyberte vhodnou zprávu ze seznamu níže (náhodně).

   **Doporučené zprávy pro generování:**

   * *Pro `INFO`:* "Start procesu", "Uživatel přihlášen", "Záloha dokončena".  
   * *Pro `WARNING`:* "Vysoká odezva", "Nízká paměť", "Neznámý požadavek".  
   * *Pro `ERROR`:* "Spojení selhalo", "Segfault", "Disk plný".  
3. **Organizace kódu:**  
   * Rozdělte kód do `.h` a `.cpp`.  
   * V souboru `main.cpp` vytvořte instanci `Logger` a `Server`. Spusťte generování alespoň **50 logů**.

### **Bodování C++:**

| Kritérium | Body |
| :---- | :---- |
| Správná implementace třídy `Logger` (otevření, zápis, zavření) | 8 bodů |
| Správný formát výstupu (`[CAS] LEVEL: Objekt - Zprava`) | 4 bodů |
| Rozdělení do hlavičkového a zdrojového souboru (`.h`/`.cpp`) | 4 bodů |
| Třída `Server` a náhodný výběr objektů a zpráv | 4 bodů |

## **Část 2: Python (Analýza logů s pamětí) – 30 bodů**

Napište skript, který zpracuje vygenerovaný soubor `server.log` a **agreguje** statistiky s předchozími běhy programu.

### **Zadání:**

1. **Generator `read_logs(filename)`:**  
   * Funkce, která načítá soubor řádek po řádku.  
   * Pro plný počet bodů použijte klíčové slovo **`yield`**.  
2. **Třída `LogStat`:**  
   * **Persistence (Ukládání stavu):**  
     * Třída si musí pamatovat celkové počty chyb i z minulých spuštění.  
     * Při inicializaci se pokusí načíst stav ze souboru `stats_history.txt` (pokud existuje).  
     * Při ukončení (nebo po zpracování) uloží aktualizované statistiky zpět do `stats_history.txt`.  
   * **Struktura dat:** Statistiky pro jednotlivé objekty (`Databáze`, `Server`, `System`) rozdělené podle úrovní.  
   * Metoda `process_line(line)`: Rozparsuje řádek pomocí **regexu** a aktualizuje počítadla.  
   * Metoda `__str__`: Vypíše aktuální statistiky (včetně historie).  
3. **Hlavní skript:**  
   * Vytvořte instanci `LogStat` (ta si načte historii).  
   * Projděte soubor `server.log` a zpracujte nové řádky.  
   * Vypište celkové statistiky.  
   * Uložte nový stav.

### **Bodování Python:**

| Kritérium | Body |
| :---- | :---- |
| **Persistence:** Načítání a ukládání historie do souboru | 10 bodů |
| Použití generátoru `yield` | 5 bodů |
| Použití regulárních výrazů (`re`) | 5 bodů |
| OOP struktura a ošetření výjimek (např. neexistující soubor) | 10 bodů |

## **Referenční výstupy**

### **Scénář testování persistence**

1. **První spuštění:** `server.log` obsahuje 10 chyb. Python vypíše "Celkem chyb: 10". Vytvoří se `stats_history.txt`.  
2. **C++ generátor:** Spustí se znovu a přidá dalších 10 chyb do `server.log` (nebo ho přepíše novými).  
3. **Druhé spuštění Pythonu:** Načte historii (10) + zpracuje nové (10). Výpis: "Celkem chyb: 20".

### **Očekávaný formát souboru `server.log`**

Váš C++ program by měl vygenerovat soubor s podobným obsahem:

```log
[1700000001] INFO: System - Start procesu
[1700000002] WARNING: Server - Vysoká odezva
[1700000003] ERROR: Databáze - Spojení selhalo
[1700000004] INFO: Databáze - Záloha dokončena
...
```

### **Příklad výstupu `analyza.py`**

Váš Python skript by měl do terminálu vypsat následující informace (čísla se budou lišit dle náhody):

```shell
Načítám historii... OK (nalezeno 15 záznamů).  
Zpracovávám server.log... OK (přidáno 50 záznamů).

--- Celkové Statistiky (Historie + Nyní) ---  
Databáze:  
  INFO    : 10  
  WARNING : 5  
  ERROR   : 8  
Server  
  INFO    : 15  
  WARNING : 2  
  ERROR   : 3  
...  
--------------------------------------------  
Stav uložen do stats_history.txt  
```