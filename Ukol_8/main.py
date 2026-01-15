import re

def read_logs(file_path):

    try:
        with open(file_path, 'r') as file:
            for radek in file:
                yield radek.strip()
        pass
    except FileNotFoundError:
        print(f"Chyba: Soubor '{file_path}' nebyl nalezen.")

def process_line(line):
    """
    Zpracuje řádek logu pomocí regexu.
    Vrátí slovník {'timestamp': ..., 'level': ..., 'message': ..., 'email': ...}
    nebo None, pokud řádek neodpovídá formátu.
    
    Očekávaný formát: [DATUM] LEVEL: Zpráva - User: email"
""" 
    pattern = "^\[(.*?)\] (\w+): (.*) - User: (\S+)"
    match = re.match(pattern, line)
    if not match:
        return None
    else:
        return {'timestamp': match.group(1), 'level': match.group(2), 'message': match.group(3), 'email': match.group(4)}

def analyze_logs(input_file, output_file):
    """
    Načte logy, vyfiltruje ERROR záznamy a zapíše je do výstupního souboru.
    """
    count = 0
    # TODO: Otevřít output_file pro zápis
    with open(output_file, 'w') as f_out:
        for radek in read_logs(input_file):
            rozsekat = process_line(radek)
            if rozsekat and rozsekat["level"] == 'ERROR':
                f_out.write(f"{rozsekat['timestamp']}, {rozsekat['level']}, {rozsekat['message']}, {rozsekat['email']}")
                count = count + 1

    
    print(f"Zpracování dokončeno. Nalezeno {count} chyb.")

if __name__ == "__main__":
    # Pro účely testování vytvořte soubor data.log, pokud neexistuje, nebo jej stáhněte
    analyze_logs("sample_data.txt", "filtered_errors.txt")
