import re


def read_logs(file_path):
    """
    Generátor, který načítá soubor řádek po řádku.
    Ošetřete FileNotFoundError.
    """
    try:
        with open(file_path, 'r', encoding='utf-8') as f:
            for line in f:
                yield line
    except FileNotFoundError:
        print(f"Chyba: Soubor '{file_path}' nebyl nalezen.")


def process_line(line):
    """
    Zpracuje řádek logu pomocí regexu.
    Vrátí slovník {'timestamp': ..., 'level': ..., 'message': ..., 'email': ...}
    nebo None, pokud řádek neodpovídá formátu.

    Očekávaný formát: [DATUM] LEVEL: Zpráva - User: email
    """
    pattern = r"\[(?P<timestamp>.*?)\] (?P<level>\w+): (?P<message>.*?) - User: (?P<email>[\w\. \+-]+@[\w\.-]+)"

    match = re.search(pattern, line)

    if match:
        return match.groupdict()
    return None


def analyze_logs(input_file, output_file):
    """
    Načte logy, vyfiltruje ERROR záznamy a zapíše je do výstupního souboru.
    """
    count = 0

    with open(output_file, 'w', encoding='utf-8') as f_out:
        for line in read_logs(input_file):
            data = process_line(line)
            if data and data['level'] == 'ERROR':
                f_out.write(
                    f"[{data['timestamp']}] ERROR: {data['message']} - User: {data['email']}\n")
                count += 1

    print(f"Zpracování dokončeno. Nalezeno {count} chyb.")


if __name__ == "__main__":
    # Pro účely testování vytvořte soubor data.log, pokud neexistuje, nebo jej stáhněte
    analyze_logs("Ukol_8/sample_data.txt", "Ukol_8/filtered_errors.txt")
