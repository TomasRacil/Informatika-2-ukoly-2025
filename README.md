# Informatika 2 - Úkoly 2025

Vítejte v repozitáři pro předmět Informatika 2. Tento repozitář slouží jako centrální místo pro zadávání a odevzdávání vašich úkolů. Postupně zde budou přidávány nové úkoly, proto sledujte repozitář pro aktuální informace.

---

## Postup pro odevzdávání úkolů

Pro úspěšné odevzdání úkolů postupujte podle následujících kroků. Pečlivé dodržení postupu je klíčové pro správné a včasné hodnocení.

### 1. Forkování repozitáře
Nejprve si vytvořte vlastní kopii tohoto repozitáře kliknutím na tlačítko **Fork** v pravém horním rohu.

* **Repository name:** Pojmenujte si svůj forknutý repozitář tak, abyste ho snadno identifikovali, například `Informatika-2-ukoly-2025-VaseJmeno`.
* Při vytváření forku ponechte zaškrtnutou volbu **Copy the `master` branch only**.

### 2. Práce na úkolech
* **Devcontainer (Doporučeno):** Pro usnadnění práce a testování doporučujeme spustit si vývojové prostředí v devcontaineru. Tím zajistíte, že budete mít k dispozici všechny potřebné nástroje a závislosti.
* **Implementace:** Upravte kód v příslušných souborech tak, aby splňoval zadání a procházel všemi připravenými testy.

### 3. Testování
Před odevzdáním si vždy lokálně otestujte funkčnost vašeho řešení. Testy můžete spustit pomocí následujících příkazů v terminálu. Příkazy naleznete také v souborech `.github/workflows/testUkol*.yml`.

* **Spuštění Python testů:**
    ```shell
    cd Ukol_0/python && python3 -m unittest discover
    ```
* **Spuštění C++ testů:**
    ```shell
    cd Ukol_0/cpp && mkdir -p build && cd build && cmake .. && make && ./mytests
    ```
*(Poznámka: Číslo úkolu v cestě se může lišit v závislosti na konkrétním úkolu.)*

### 4. Commit a Push
Jakmile jsou vaše úpravy hotové a testy procházejí, vytvořte **commit** a nahrajte ho na váš forknutý repozitář pomocí příkazu **push**.

### 5. Vytvoření Pull Requestu
Po nahrání změn na váš repozitář se vám obvykle zobrazí výzva k vytvoření pull requestu. Pokud ne, přejděte na záložku **Pull requests** ve vašem forknutém repozitáři a klikněte na **New pull request**.

* **Název pull requestu:** Pojmenujte pull request tak, aby obsahoval vaše jméno a název úkolu, například `Odevzdani Ukol 0 - Josef Novak`.
* **Cílová větev:** Cílovou větví by měla být větev s **vaším jménem** v mém původním repozitáři.
* Ponechte zaškrtnutou volbu **Allow edits by maintainers**.
* Po vytvoření pull requestu se automaticky spustí testy. U prvního odevzdání bude potřeba mé schválení pro spuštění testů, u dalších úkolů to již nebude nutné.

### 6. Kontrola a hodnocení
* Stav testů a svůj pull request naleznete v záložce **Pull requests** v **mém původním repozitáři**.
* Pokud všechny testy projdou, úkol je považován za splněný a já následně váš pull request schválím a začlením (mergnu).
* Pokud některý z testů selže, zkontrolujte svůj kód, opravte chyby a nahrajte novou verzi (další commit a push). Pokud si s opravou nebudete vědět rady, dejte mi vědět.

---

### Důležité upozornění
**Dodržujte termíny odevzdání!** Pokud by se vám z jakéhokoli důvodu nedařilo vytvořit pull request včas, samotné vytvoření commitu na vašem forknutém repozitáři bude sloužit jako důkaz, že jste úkol vyřešili v termínu.

@TomasRacil
