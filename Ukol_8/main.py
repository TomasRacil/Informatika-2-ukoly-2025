import re


def read_logs(file_path):
    """
    Generátor, který načítá soubor řádek po řádku.
    Ošetřete FileNotFoundError.
    """
    try:
        with open(file_path, 'r', encoding='utf-8') as fh:
            for line in fh:
                yield line.rstrip('\n')
    except FileNotFoundError:
        print(f"Chyba: Soubor '{file_path}' nebyl nalezen.")


def process_line(line):
    """
    Zpracuje řádek logu pomocí regexu.
    Vrátí slovník {'timestamp': ..., 'level': ..., 'message': ..., 'email': ...}
    nebo None, pokud řádek neodpovídá formátu.

    Očekávaný formát: [DATUM] LEVEL: Zpráva - User: email
    """
    # pattern: [DATUM] LEVEL: Zpráva - User: email
    # allow '+' and '%' in local part and require at least one dot in domain part
    pattern = r"\[([^\]]+)\]\s+(INFO|WARN|ERROR|DEBUG):\s+(.*?)\s+-\s+User:\s+([A-Za-z0-9._%+\-]+@[A-Za-z0-9.\-]+\.[A-Za-z]{2,})"
    match = re.search(pattern, line)
    if not match:
        return None

    timestamp = match.group(1).strip()
    level = match.group(2).strip()
    message = match.group(3).strip()
    email = match.group(4).strip()

    return {'timestamp': timestamp, 'level': level, 'message': message, 'email': email}


def analyze_logs(input_file, output_file):
    """
    Načte logy, vyfiltruje ERROR záznamy a zapíše je do výstupního souboru.
    """
    count = 0
    try:
        with open(output_file, 'w', encoding='utf-8') as f_out:
            # volitelně zapíšeme CSV hlavičku
            f_out.write('timestamp,email,message\n')
            for line in read_logs(input_file):
                parsed = process_line(line)
                if parsed and parsed.get('level') == 'ERROR':
                    # escape simple commas in message
                    msg = parsed.get('message', '').replace(
                        '\n', ' ').replace(',', ' ')
                    f_out.write(
                        f"{parsed.get('timestamp')},{parsed.get('email')},{msg}\n")
                    count += 1
    except Exception as e:
        print(f"Chyba při zpracování: {e}")

    print(f"Zpracování dokončeno. Nalezeno {count} chyb.")


if __name__ == "__main__":
    # Pro účely testování vytvořte soubor data.log, pokud neexistuje, nebo jej stáhněte
    analyze_logs("sample_data.txt", "filtered_errors.txt")
