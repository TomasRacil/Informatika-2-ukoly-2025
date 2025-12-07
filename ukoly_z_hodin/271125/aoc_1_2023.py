from os.path import join, realpath, dirname

cesta = join(dirname(realpath(__file__)), "data.txt")

def parse_input():
    digits = []
    numbers_in_words = {1: "one", 2: "two", 3: "three", 4: "four",
                        5: "five", 6: "six", 7: "seven", 8: "eight", 9: "nine"}
    
    with open(cesta, "r", encoding="utf-8") as f: 
        for line in f:
            current_digits = []
            new_line = line

            num_words = [k for k,v in numbers_in_words.items() if v in line]

            for k,v in numbers_in_words.items():
                if (num_words[0] == k or num_words[-1] == k):
                    new_line = new_line.replace(v, str(k))

            print(f"Old line: {line} || New line: {new_line}")
            for znak in new_line:
                if (znak.isdigit()):
                    current_digits.append(znak)

            digits.append(int(current_digits[0] + current_digits[-1]))
            print(f"= Extracted digits: {current_digits}, Combined: {current_digits[0] + current_digits[-1]}")
            print("-----")
    return digits

def sum_digits(digits):
    return sum(digits)

print(sum_digits(parse_input()))