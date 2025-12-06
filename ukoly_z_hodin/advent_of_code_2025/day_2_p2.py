from os.path import dirname, join, realpath
import re, math

soubor = join(dirname(realpath(__file__)), "day_2_data.txt")

def main():
    with open(soubor, "r") as f:
        data = f.read().split(",")

        invalid_numbers = 0
        for i in data:
            number_range = i.split("-")

            first_number = int(number_range[0])
            second_number = int(number_range[1])

            for number in range(first_number, second_number + 1):
                list_converted = list(str(number))
                
                for i in range(1, len(list_converted) + 1):
                    group = list_converted[:i]

                    pattern = r"(?=(" + "".join(group) + r"))"   # build regex
                    text = "".join(list_converted)

                    matches = re.findall(pattern, text)

                    if (len(matches) > 1 and int(number) == int("".join(matches))):
                        print("invalidni cislo:", number)
                        invalid_numbers += number

                        continue
        
        print(f"Soucet nevalidnich cisel: {invalid_numbers}")

main()