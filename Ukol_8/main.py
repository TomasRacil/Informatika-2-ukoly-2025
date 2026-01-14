import re

def read_logs(file_path):
    try:
        with open(file_path, 'r', encoding='utf-8') as f:
            for line in f:
                yield line.strip()
        
    except FileNotFoundError:
        print(f"Chyba Soubor {file_path} nebyl nalezen")

def process_line(line):
    
    pattern = r"\[(?P<timestamp>.*?)\]\s(?P<level>\w+):\s(?P<message>.*?)\s-\sUser:\s(?P<email>[\w\.\-\+]+@[\w\.-]+)"
    
    match = re.match(pattern, line)
    if match:
        return match.groupdict()
    
    return None

def analyze_logs(input_file, output_file):
    count = 0
    try:
        with open(output_file, 'w', encoding='utf-8') as f_out:
            for line in read_logs(input_file):
                processed = process_line(line)
                
                if processed and processed['level'] == 'ERROR':
                    f_out.write(f"{processed['timestamp']} - {processed['message']} - {processed['email']}\n")
                    count += 1    
        
        print(f"Zpracovani dokonceno Nalezeno {count} chyb")
        
    except Exception as e:
        print(f"Nastala neocekavana chyba pri zapisu {e}")

if __name__ == "__main__":
    analyze_logs("sample_data.txt", "filtered_errors.txt")