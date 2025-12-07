from os.path import dirname, join, realpath
import math

soubor = join(dirname(realpath(__file__)), "day_3_data.txt")

def main():
    with (open(soubor, "r") as f):
        data = f.read().split("\n")

        total_jolts = 0

        for bank in data:
            digits = [int(d) for d in bank]

            max_1 = 0
            max_1_index = None
            max_2 = 0

            for index in range(len(digits)):
                d = digits[index]
                if (d > max_1 and index != (len(digits) - 1)):
                    max_1 = d
                    max_1_index = index

            for index in range(max_1_index + 1, len(digits)):
                d = digits[index]
                if (d > max_2):
                    max_2 = d

            current_joltage = int(str(max_1) + str(max_2))

            print(current_joltage)
            total_jolts += current_joltage
            
        print(total_jolts)
                
main()