import re

def read_logs(file_path):
    """
    Generátor, který načítá soubor řádek po řádku.
    Ošetřete FileNotFoundError.
    """
    try:
        with open(file_path, 'r', encoding='utf-8') as f: 
            for line in f:
                yield line.strip()
        # TODO: Otevřít soubor a yieldovat řádky
    
    except FileNotFoundError:
        print(f"Chyba: Soubor '{file_path}' nebyl nalezen.")

def process_line(line):
    """
    Zpracuje řádek logu pomocí regexu.
    Vrátí slovník {'timestamp': ..., 'level': ..., 'message': ..., 'email': ...}
    nebo None, pokud řádek neodpovídá formátu.
    
    Očekávaný formát: [DATUM] LEVEL: Zpráva - User: email
    """
    pattern = r"\[(?P<timestamp>.*?)\]\s+(?P<level>[A-Z]+):\s+(?P<message>.*?)\s+-\s+User:\s+(?P<email>\S+)"
    match = re.match(pattern, line)
    if not match:
        return None
    
    return {
        "timestamp": match.group(1),
        "level": match.group(2),
        "message": match.group(3),
        "email": match.group(4)
    }
    # TODO: Definovat regex pattern
    # pattern = r"..."
    
    # TODO: Použít re.search nebo re.match
    # match = ...
    
    # TODO: Pokud match, vrátit dict, jinak None

def analyze_logs(input_file, output_file):
    """
    Načte logy, vyfiltruje ERROR záznamy a zapíše je do výstupního souboru.
    """
    count = 0

    try:   
        with open(output_file, 'w', encoding='utf-8') as f_out:
            f_out.write("timestamp,message,email\n")

            for line in read_logs(input_file):
                data = process_line(line)
                if data and data['level'] == 'ERROR':
                    csv_line = f"{data['timestamp']},{data['email']},{data['message']}\n"
                    f_out.write(csv_line)
                    count += 1
    # TODO: Otevřít output_file pro zápis
    # with open(output_file, 'w') as f_out:
        # TODO: Iterovat přes read_logs(input_file)
        # TODO: Zpracovat řádek přes process_line
        # TODO: Pokud je level == 'ERROR', zapsat do souboru
        # pass
    except IOError as e:
        print(f"Chyba při zápisu do souboru: {e}")    

if __name__ == "__main__":
    # Pro účely testování vytvořte soubor data.log, pokud neexistuje, nebo jej stáhněte
    analyze_logs("sample_data.txt", "filtered_errors.txt")
    