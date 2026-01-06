from os.path import dirname, join, realpath
import math

soubor = join(dirname(realpath(__file__)), "day_3_data.txt")

def main():
    with (open(soubor, "r") as f):
        data = f.read().split("\n")

        total_jolts = 0
        range_of_maxes = 12

        for bank in data:
            digits = [int(d) for d in bank]
            maxes = [-1] * range_of_maxes
            max_index = -1

            for r in range(range_of_maxes):

                for index, d in enumerate(digits):
                    current_max_d = maxes[r]
                    allowed_index = len(digits) - (range_of_maxes - r)

                    if (d > current_max_d and index <= allowed_index and index > max_index):
                        print(f"[{r} - PASSED] New max found: {d} at index {index}")
                        maxes[r] = d
                        max_index = index

            current_joltage = "".join([str(m) for m in maxes])
            total_jolts += int(current_joltage)
            
        print(f"Total jolts: {total_jolts}")
                
main()