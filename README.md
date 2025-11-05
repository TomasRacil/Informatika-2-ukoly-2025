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
<<<<<<< HEAD
**Dodržujte termíny odevzdání!** Pokud by se vám z jakéhokoli důvodu nedařilo vytvořit pull request včas, samotné vytvoření commitu na vašem forknutém repozitáři bude sloužit jako důkaz, že jste úkol vyřešili v termínu.
=======
**Dodržujte termíny odevzdání!** Pokud by se vám z jakéhokoli důvodu nedařilo vytvořit pull request včas, samotné vytvoření commitu na vašem forknutém repozitáři bude sloužit jako důkaz, že jste úkol vyřešili v termínu.

-----

## Lokální testování bez Devcontaineru

Ačkoliv je devcontainer doporučený způsob, můžete si prostředí zprovoznit i lokálně. Pro spuštění C++ testů (např. Úkol 1, 2, 3) budete potřebovat tři hlavní součásti:

1.  **C++ Kompilátor:** (např. `g++` na Linuxu, `clang` na macOS, nebo MSVC na Windows)
2.  **CMake:** Nástroj pro konfiguraci a sestavení projektu.
3.  **Google Test (gtest):** Knihovna pro testování (konkrétně `libgtest-dev` nebo ekvivalent).

Níže jsou pokyny pro jednotlivé operační systémy.

### Instalace na Linuxu (Debian/Ubuntu)

Prostředí na Linuxu nainstalujete jedním příkazem, který je totožný s tím v našich GitHub Actions:

```shell
sudo apt-get update && sudo apt-get install -y cmake g++ libgtest-dev
```

Poté můžete spustit testy standardním příkazem (např. pro Úkol 1):

```shell
cd Ukol_1 && mkdir -p build && cd build && cmake .. && make && ./mytests
```

### Instalace na macOS

Nejjednodušší cesta je použít [Homebrew](https://brew.sh/).

1.  Nainstalujte Xcode Command Line Tools (pokud je nemáte):
    ```shell
    xcode-select --install
    ```
2.  Nainstalujte Homebrew (pokud ho nemáte) a poté `cmake` a `googletest`:
    ```shell
    brew install cmake googletest
    ```
3.  Spusťte testy (příkaz je stejný jako pro Linux):
    ```shell
    cd Ukol_1 && mkdir -p build && cd build && cmake .. && make && ./mytests
    ```

### Instalace na Windows

Instalace na Windows je komplexnější. Doporučujeme použít [Visual Studio 2022](https://visualstudio.microsoft.com/cs/vs/community/) s [vcpkg](https://vcpkg.io/).

1.  **Instalace Visual Studia:** Stáhněte si Visual Studio 2022 Community. Během instalace zaškrtněte komponentu **"Vývoj desktopových aplikací pomocí C++"**. Tím se nainstaluje C++ kompilátor, Windows SDK a také CMake.

2.  **Instalace `gtest` pomocí `vcpkg`:**

      * Otevřete PowerShell a nainstalujte `vcpkg` (např. do `C:\vcpkg`):
        ```powershell
        cd C:\
        git clone https://github.com/microsoft/vcpkg.git
        .\vcpkg\bootstrap-vcpkg.bat
        ```
      * Nainstalujte `gtest`:
        ```powershell
        .\vcpkg\vcpkg.exe install gtest
        ```

3.  **Sestavení projektu:**

      * Otevřete "Developer Command Prompt for VS 2022" (najdete v nabídce Start).
      * Přejděte do složky s úkolem (např. `Ukol_1`).
      * Při spouštění `cmake` musíte odkázat na `vcpkg` toolchain soubor, aby `find_package(GTest REQUIRED)` fungovalo. Nahraďte `C:\vcpkg` cestou, kam jste `vcpkg` nainstalovali.
        ```shell
        cd Ukol_1
        mkdir build && cd build
        cmake .. -DCMAKE_TOOLCHAIN_FILE=C:\vcpkg\scripts\buildsystems\vcpkg.cmake
        cmake --build .
        ```

4.  **Spuštění testů:**

      * Testovací soubor se ve Windows jmenuje `mytests.exe` a bude umístěn ve složce `build/Debug` (nebo `build/Release`).
      * Spusťte testy (příkaz `mytests` je definován v `CMakeLists.txt`):
        ```shell
        .\Debug\mytests.exe
        ```