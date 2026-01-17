from os.path import dirname, join, realpath
import re

soubor = join(dirname(realpath(__file__)), "day_6_data.txt")

def safe_get (l, idx, default):
  try:
    return l[idx]
  except IndexError:
    return default
  
def main():
    with open(soubor, "r") as f:
        data = f.read().splitlines()

        operators = [operator for operator in data[len(data) - 1].split(" ") if operator.strip() != ""]

        number_lines = []

        new_number_lines = {}
        horizontal_string_lines = []
        horizontal_number_lines = []

        for num_line in data[0:len(data) - 1]:
            horizontal_line = [num for num in num_line.split(" ") if num.strip()]

            horizontal_number_lines.append(horizontal_line)
            horizontal_string_lines.append(num_line.replace(" ", "_"))

            for index, line_value in enumerate(horizontal_line):
                new_num_line = []

                try:
                    new_num_line = new_number_lines[index]
                except KeyError:
                    new_number_lines[index] = []

                new_num_line.append(line_value)

                new_number_lines[index] = new_num_line

        # reverse because we are going from right to left
        new_number_lines = dict(reversed(list(new_number_lines.items())))    

        horizontal_character_lines = []

        for index, h_numbers in enumerate(horizontal_number_lines):
           start_index = len(horizontal_string_lines[index])
           horizontal_string_line = horizontal_string_lines[index]

           for key, v_numbers in new_number_lines.items():
              highest_num = max([int(num) for num in v_numbers])
              max_index = len(str(highest_num))
              
              start_index -= max_index + 1

              if (start_index < 0):
                 break

              horizontal_string_line = list(horizontal_string_line)
              horizontal_string_line[start_index] = "x"

              horizontal_string_line = "".join(horizontal_string_line)
    
           horizontal_character_lines.append(horizontal_string_line.split("x"))

        final_vertical = {}
        for h_chars in horizontal_character_lines:
           for index, h_char in enumerate(h_chars):
              try:
                 final_vertical[index].append(h_char)
              except KeyError:
                 final_vertical[index] = []
                 final_vertical[index].append(h_char)

        final_vertical = dict(reversed(list(final_vertical.items())))
        result = 0

        for key, v_numbers in final_vertical.items():
           positions = {}
           operator = list(reversed(operators))[len(operators) - 1 - key]

           for v_number in v_numbers:
               for pos, digit in enumerate(list(str(v_number))):
                    # print(f"position: {pos}, digit: {digit}")

                    try:
                        positions[pos] += str(digit)
                    except KeyError:
                        positions[pos] = str(digit)
           regular_numbers = list(reversed([int(v.replace("_","")) for k, v in positions.items()]))
           result_number = 0
    
           for index, number in enumerate(regular_numbers):
                print("Current number:", result_number)
                if operator == "+":
                    result_number += number
                elif operator == "*":
                    if result_number == 0:
                        result_number = 1
                    result_number *= number
              
           result += result_number
        print("Final result:", result)
main()