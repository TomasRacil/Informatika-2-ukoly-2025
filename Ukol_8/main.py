import re
from os.path import dirname, join 

current_dir = dirname(__file__)

def read_logs(file_path):
    """
    Generátor, který načítá soubor řádek po řádku.
    Ošetřete FileNotFoundError.
    """
    try:
        # TODO: Otevřít soubor a yieldovat řádky
        with open(file_path, "r", encoding="utf-8") as file:
            for line in file.readlines():
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

    pattern_uni = r'\[(.*)\]\s([a-zA-Z]+): (.*) - [a-zA-Z]+: ([a-zA-Z-\d]*@*.*)'
    pattern_re = re.search(pattern_uni, line)

    to_return = {'timestamp': None, 'level': None, 'message': None, 'email': None}

    for idx, index in enumerate(to_return.keys()):
        if (not pattern_re):
            continue

        to_return[index] = pattern_re.group(idx + 1)

    return to_return if pattern_re else None

def analyze_logs(input_file, output_file):
    """
    Načte logy, vyfiltruje ERROR záznamy a zapíše je do výstupního souboru.
    """
    count = 0
    output_file_path = join(current_dir, output_file)
    input_file_path = join(current_dir, input_file)
    logs = read_logs(input_file_path)

    with open(output_file_path, "w") as file_out:
        for line in logs:
            if (not line):
                continue

            data_from_line = process_line(line)

            if (not data_from_line):
                continue

            if (data_from_line["level"] == "ERROR"):
                count += 1

                text_to_output = f"{' '.join([f'{str(index)}: {str(value)}' for index, value in data_from_line.items()])}\n"

                file_out.write(text_to_output)
                
    print(f"Zpracování dokončeno. Nalezeno {count} chyb.")

if __name__ == "__main__":
    # Pro účely testování vytvořte soubor data.log, pokud neexistuje, nebo jej stáhněte
    analyze_logs("sample_data.txt", "filtered_errors.txt")
