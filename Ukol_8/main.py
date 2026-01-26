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
        # TODO: Otevřít soubor a yieldovat řádky
        pass
    except FileNotFoundError:
        print(f"Chyba: Soubor '{file_path}' nebyl nalezen.")

def process_line(line):
    """
    Zpracuje řádek logu pomocí regexu.
    Vrátí slovník {'timestamp': ..., 'level': ..., 'message': ..., 'email': ...}
    nebo None, pokud řádek neodpovídá formátu.
    
    Očekávaný formát: [DATUM] LEVEL: Zpráva - User: email
    """
    # TODO: Definovat regex pattern
    # pattern = r"..."
    pattern = r"^\[(.*?)\]\s+(\w+):\s+(.*?)\s+-\s+User:\s+([^\s]+)$"
    
    # TODO: Použít re.search nebo re.match
    match = re.match(pattern, line)
    
    # TODO: Pokud match, vrátit dict, jinak None
    if match:
        return {
            'timestamp': match.group(1),
            'level': match.group(2),
            'message': match.group(3),
            'email': match.group(4)
        }
    return None

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
    with open(output_file, 'w', encoding='utf-8') as f_out:
        for line in read_logs(input_file):
            result = process_line(line)  
            if result and result['level'] == 'ERROR':
                f_out.write(line + '\n')
                count += 1  
    
    print(f"Zpracování dokončeno. Nalezeno {count} chyb.")

if __name__ == "__main__":
    # Pro účely testování vytvořte soubor data.log, pokud neexistuje, nebo jej stáhněte
    analyze_logs("sample_data.txt", "filtered_errors.txt")
