import re
import types

def read_logs(file_path):
    """
    Generátor, který načítá soubor řádek po řádku.
    """
    try:
        with open(file_path, 'r', encoding='utf-8') as f:
            for line in f:
                yield line.strip()
    except FileNotFoundError:
        # Důležité: Generátor i při chybě musí zůstat generátorem, 
        # jen prostě nic nevynechá (prázdná iterace).
        return

def process_line(line):
    """
    Zpracuje řádek logu pomocí robustního regexu.
    Očekávaný formát: [DATUM] LEVEL: Zpráva - User: email
    """
    # Upravený regex: 
    # [^\]]+ zachytí vše uvnitř závorek
    # .+? je líný kvantifikátor pro zprávu, aby se nezastavil až na konci řádku
    pattern = r"\[(?P<timestamp>[^\]]+)\]\s+(?P<level>\w+):\s+(?P<message>.+?)\s+-\s+User:\s+(?P<email>\S+)"
    
    match = re.search(pattern, line)
    if match:
        return match.groupdict()
    return None

def analyze_logs(input_file, output_file):
    """
    Načte logy, vyfiltruje ERROR záznamy a zapíše je do výstupního souboru.
    """
    count = 0
    # Otevíráme soubor pro zápis hned na začátku, aby soubor existoval i v případě 0 chyb
    with open(output_file, 'w', encoding='utf-8') as f_out:
        for line in read_logs(input_file):
            log_data = process_line(line)
            
            if log_data and log_data.get('level') == 'ERROR':
                f_out.write(f"[{log_data['timestamp']}] ERROR: {log_data['message']} - User: {log_data['email']}\n")
                count += 1
    
    print(f"Zpracování dokončeno. Nalezeno {count} chyb.")

if __name__ == "__main__":
    # Testovací volání
    analyze_logs("sample_data.txt", "filtered_errors.txt")