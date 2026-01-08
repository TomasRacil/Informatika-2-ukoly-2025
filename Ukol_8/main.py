import re

def read_logs(file_path):
    """
    Generátor, který načítá soubor řádek po řádku.
    Ošetřete FileNotFoundError.
    """
    try:
        with open(file_path, "r", encoding="utf-8") as f:
            for line in f:
                yield line.strip()
    except FileNotFoundError:
        print(f"Chyba: Soubor '{file_path}' nebyl nalezen.")

def process_line(line):
    """
    Zpracuje řádek logu pomocí regexu.
    Vrátí slovník {'timestamp': ..., 'level': ..., 'message': ..., 'email': ...}
    nebo None, pokud řádek neodpovídá formátu.
    
    Očekávaný formát: [DATUM] LEVEL: Zpráva - User: email
    """
    regex = r"\[(.*?)\]\s+(INFO|WARN|ERROR):\s+(.*?)\s+-\s+User:\s+([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})" #regex_generator pouzit: https://regex-generator.olafneumann.org/

    match = re.match(regex, line)
    if not match:
        return None

    return {
        "datetime": match.group(1),
        "level": match.group(2),
        "message": match.group(3),
        "email": match.group(4),
    }

def analyze_logs(input_file, output_file):
    """
    Načte logy, vyfiltruje ERROR záznamy a zapíše je do výstupního souboru.
    """
    try:
        with open(output_file, "w", encoding="utf-8") as out:
            out.write("datetime,email,message\n")

            for line in read_logs(input_file):
                result = process_line(line)
                if result and result["level"] == "ERROR":
                    out.write(
                        f'{result["datetime"]},{result["email"]},{result["message"]}\n'
                    )
    except IOError as e:
        print(f"Chyba při zápisu do souboru: {e}")

if __name__ == "__main__":
    # Pro účely testování vytvořte soubor data.log, pokud neexistuje, nebo jej stáhněte
    analyze_logs("sample_data.txt", "filtered_errors.txt")
