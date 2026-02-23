import re
from os.path import dirname, realpath, join

def read_logs(file_path):
    """
    Generátor, který načítá soubor řádek po řádku.
    Ošetřete FileNotFoundError.
    """
    path = join(dirname(realpath(__file__)), file_path)

    try:
        with open(path, "r", encoding="utf-8") as f:
            for line in f:
                yield line.rstrip("\n")
    except FileNotFoundError:
        print(f"Chyba: Soubor '{file_path}' nebyl nalezen.")

def process_line(line):
    """
    Zpracuje řádek logu pomocí regexu.
    Vrátí slovník {'timestamp': ..., 'level': ..., 'message': ..., 'email': ...}
    nebo None, pokud řádek neodpovídá formátu.
    
    Očekávaný formát: [DATUM] LEVEL: Zpráva - User: email
    """
    LOG_PATTERN = re.compile(
        r"\[(\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2})\]\s+"
        r"(INFO|DEBUG|WARN|ERROR):\s+"
        r"(.+?)\s+-\s+User:\s+"
        r"([\w.+-]+@[\w.-]+\.\w+)"
    )

    match = LOG_PATTERN.match(line)

    if not match:
        return None

    timestamp, level, message, email = match.groups()

    return {
        "timestamp": timestamp,
        "level": level,
        "message": message,
        "email": email
    }

def analyze_logs(input_file, output_file):
    """
    Načte logy, vyfiltruje ERROR záznamy a zapíše je do výstupního souboru.
    """
    count = 0
    # TODO: Otevřít output_file pro zápis
    with open(output_file, "w") as f_out:
        for line in read_logs(input_file):
            parsed = process_line(line)

            if parsed is None:
                continue

            if parsed["level"] == "ERROR":
                f_out.write(line + "\n")
                count += 1
    
    print(f"Zpracování dokončeno. Nalezeno {count} chyb.")

if __name__ == "__main__":
    # Pro účely testování vytvořte soubor data.log, pokud neexistuje, nebo jej stáhněte
    analyze_logs("sample_data.txt", "filtered_errors.txt")
