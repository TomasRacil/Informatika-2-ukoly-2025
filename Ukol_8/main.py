import re

def read_logs(file_path):
    """
    Generátor, který načítá soubor řádek po řádku.
    Ošetřete FileNotFoundError.
    """
    try:
        with open(file_path, 'r', encoding='utf-8') as file:
            for line in file:
                yield line.strip()  # .strip() odstraní \n na konci řádku
    except FileNotFoundError:
        print(f"Chyba: Soubor '{file_path}' nebyl nalezen.")

def process_line(line):
    """
    Zpracuje řádek logu pomocí regexu.
    Vrátí slovník {'timestamp': ..., 'level': ..., 'message': ..., 'email': ...}
    nebo None, pokud řádek neodpovídá formátu.
    
    Očekávaný formát: [DATUM] LEVEL: Zpráva - User: email
    """
    pattern = r"\[(.*?)\]\s(\w+):\s(.*?)\s-\sUser:\s([\w\.-]+@[\w\.-]+)"
    
    match = re.search(pattern, line)
    
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
log_generator = read_logs(input_file)
    
    # Pokud soubor neexistuje, generátor nic nevrátí (vyřešeno v read_logs)
    if log_generator is None:
        return

    with open(output_file, 'w', encoding='utf-8') as f_out:
        # Hlavička pro výstupní soubor (volitelné, ale užitečné)
        f_out.write("timestamp,email,message\n")
        
        for line in log_generator:
            data = process_line(line)
            
            # Filtrujeme pouze záznamy, které jsou ERROR
            if data and data['level'] == 'ERROR':
                # Zápis do souboru ve formátu CSV
                f_out.write(f"{data['timestamp']},{data['email']},{data['message']}\n")
                count += 1
    
    print(f"Zpracování dokončeno. Nalezeno {count} chyb.")

if __name__ == "__main__":
    # Pro účely testování vytvořte soubor data.log, pokud neexistuje, nebo jej stáhněte
    analyze_logs("sample_data.txt", "filtered_errors.txt")
