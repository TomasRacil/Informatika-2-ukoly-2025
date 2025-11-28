from os.path import join
from posixpath import dirname, realpath

"""filename = join(dirname(realpath(__file__)), "input.txt")
file = open(filename, "r")
lines = file.readlines()

valid_num_strings = {"one":"1", "two":"2", "three":"3", "four":"4", "five":"5",
                     "six":"6", "seven":"7","eight":"8", "nine":"9"}


new_lines = []

for line in lines:
    for key in valid_num_strings:
        if key in line:
            line = line.replace(key,valid_num_strings[key])
    new_lines.append(line)
    
    
def get_first_number(line: str):
    for i in range(len(line)):
        if line[i].isnumeric():
            return line[i]


def get_last_number(line: str):
    for i in reversed(range(len(line))):
        if line[i].isnumeric():
            return line[i]

def add_two_str_numbers(a: str,  b: str) -> int:
    return int(a+b)



number_list = []

for line in new_lines:
    first_num = get_first_number(line)
    last_num = get_last_number(line)
    two_digits_num = add_two_str_numbers(first_num,last_num)
    number_list.append(two_digits_num)

total = sum(number_list)

print("The sum of your puzzle is:", total)"""

cesta = join(dirname(realpath(__file__)),"input.txt")

sum = 0

with open(cesta, "r", encoding="utf-8") as f:  
    for c, radek in enumerate(f):
        # print(c,line)
        cisla = [znak for znak in radek if znak.isdigit()]
        sum+=int(cisla[0]+cisla[-1])
        # for znak in radek:
        #     if znak.isdigit(): print(znak, end=", ")
        #print(cisla)
print(sum)
