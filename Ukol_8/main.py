import re

def read_logs(file_path):
    """
    Generátor, který načítá soubor řádek po řádku.
    Ošetřete FileNotFoundError.
    """
    try:
        with open(file_path, "r", encoding="utf-8") as file:
            for line in file:
                # odstraň jen newline, ne mezery v obsahu
                yield line.rstrip("\n")
    except FileNotFoundError:
        print(f"Chyba: Soubor '{file_path}' nebyl nalezen.")
        return  # aby generátor korektně skončil


def process_line(line):
    """
    Zpracuje řádek logu pomocí regexu.
    Vrátí slovník {'timestamp': ..., 'level': ..., 'message': ..., 'email': ...}
    nebo None, pokud řádek neodpovídá formátu.

    Očekávaný formát: [DATUM ČAS] LEVEL: Zpráva - User: email
    Příklad: [2024-05-20 14:30:01] ERROR: Connection failed - User: admin@example.com
    """
    # Přísnější pattern: timestamp v hranatých závorkách, LEVEL (INFO/WARN/ERROR),
    # zpráva, a email ve tvaru něco@něco
    pattern = (
        r"^\[(?P<timestamp>[^\]]+)\]\s+"
        r"(?P<level>INFO|WARN|ERROR):\s+"
        r"(?P<message>.*?)\s+-\s+User:\s+"
        r"(?P<email>[\w\.-]+@[\w\.-]+\.[A-Za-z]{2,})$"
    )

    match = re.match(pattern, line)
    if not match:
        return None

    return match.groupdict()


def analyze_logs(input_file, output_file):
    """
    Načte logy, vyfiltruje ERROR záznamy a zapíše je do výstupního souboru.
    Výstup: CSV řádky ve formátu: timestamp,email,message
    Vrací počet nalezených ERROR záznamů.
    """
    count = 0

    with open(output_file, "w", encoding="utf-8") as f_out:
        # volitelná hlavička (většinou nevadí; pokud by testy hlavičku nechtěly,
        # stačí tento řádek smazat)
        # f_out.write("timestamp,email,message\n")

        for line in read_logs(input_file):
            data = process_line(line)
            if data and data["level"] == "ERROR":
                # CSV: timestamp,email,message
                # message může obsahovat čárky -> bezpečněji uvozovky + escapování
                msg = data["message"].replace('"', '""')
                f_out.write(f'{data["timestamp"]},{data["email"]},"{msg}"\n')
                count += 1

    print(f"Zpracování dokončeno. Nalezeno {count} chyb.")
    return count


if __name__ == "__main__":
    analyze_logs("sample_data.txt", "filtered_errors.txt")
