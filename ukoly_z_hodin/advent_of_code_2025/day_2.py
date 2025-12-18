from os.path import dirname, join, realpath

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
                half_of_number = str(number)[len(str(number)) // 2 :]
                first_half = str(number)[0 : len(str(number)) // 2]

                if first_half == half_of_number:
                    print(f"Najdene cislo: {number}")

                    invalid_numbers += number
        
        print(f"Soucet nevalidnich cisel: {invalid_numbers}")


main()