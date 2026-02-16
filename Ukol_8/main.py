import re

def read_logs(file_path):
    """
    Generátor, který načítá soubor řádek po řádku.
    Ošetřete FileNotFoundError.
    """
    try:
        # TODO: Otevřít soubor a yieldovat řádky
        with open(file_path, 'r') as file:
            for line in file:
                yield line.strip()
    except FileNotFoundError:
        print(f"Chyba: Soubor '{file_path}' nebyl nalezen.")
    pass

def process_line(line):
    """
    Zpracuje řádek logu pomocí regexu.
    Vrátí slovník {'timestamp': ..., 'level': ..., 'message': ..., 'email': ...}
    nebo None, pokud řádek neodpovídá formátu.
    
    Očekávaný formát: [DATUM] LEVEL: Zpráva - User: email
    """
    # TODO: Definovat regex pattern
    # pattern = r"..."
    pattern = r"\[(?P<timestamp>.*?)\] (?P<level>\w+): (?P<message>.*?) - User: (?P<email>[\w\.\+\-]+@[\w\.\-]+)"

    # TODO: Použít re.search nebo re.match
    # match = ...
    match = re.match(pattern, line)
    
    # TODO: Pokud match, vrátit dict, jinak None
    if match:
        return match.groupdict()
    else:
        return None
    pass

def analyze_logs(input_file, output_file):
    """
    Načte logy, vyfiltruje ERROR záznamy a zapíše je do výstupního souboru.
    """
    count = 0
    # TODO: Otevřít output_file pro zápis
    # with open(output_file, 'w') as f_out:
        # TODO: Iterovat přes read_logs(input_file)
        # TODO: Zpracovat řádek přes process_line
        # TODO: Pokud je level == 'ERROR', zapsat do souboru
        # pass
    with open(output_file, 'w') as f_out:
        for line in read_logs(input_file):
            processed = process_line(line)
            if processed and processed['level'] == 'ERROR':
                f_out.write(f"{processed['timestamp']} - {processed['message']} - {processed['email']}\n")
                count += 1

    print(f"Zpracování dokončeno. Nalezeno {count} chyb.")
    pass

if __name__ == "__main__":
    # Pro účely testování vytvořte soubor data.log, pokud neexistuje, nebo jej stáhněte
    analyze_logs("sample_data.txt", "filtered_errors.txt")
